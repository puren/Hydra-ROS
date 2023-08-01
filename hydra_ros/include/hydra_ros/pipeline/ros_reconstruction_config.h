/* -----------------------------------------------------------------------------
 * Copyright 2022 Massachusetts Institute of Technology.
 * All Rights Reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Research was sponsored by the United States Air Force Research Laboratory and
 * the United States Air Force Artificial Intelligence Accelerator and was
 * accomplished under Cooperative Agreement Number FA8750-19-2-1000. The views
 * and conclusions contained in this document are those of the authors and should
 * not be interpreted as representing the official policies, either expressed or
 * implied, of the United States Air Force or the U.S. Government. The U.S.
 * Government is authorized to reproduce and distribute reprints for Government
 * purposes notwithstanding any copyright notation herein.
 * -------------------------------------------------------------------------- */
#pragma once
#include <hydra/reconstruction/reconstruction_config.h>

#include "hydra_ros/config/ros_utilities.h"

namespace hydra {

enum class ExtrinsicsLookupMode { USE_KIMERA, USE_TF, USE_LOADED_PARAMS };

struct RosReconstructionConfig : public ReconstructionConfig {
  RosReconstructionConfig() : ReconstructionConfig() {}

  virtual ~RosReconstructionConfig() = default;

  bool use_image_receiver = false;
  bool publish_pointcloud = false;
  bool visualize_reconstruction = true;
  std::string topology_visualizer_ns = "~";
  bool publish_mesh = false;
  bool enable_output_queue = false;
  double pointcloud_separation_s = 0.1;
  double tf_wait_duration_s = 0.1;
  double tf_buffer_size_s = 30.0;
  ExtrinsicsLookupMode extrinsics_mode = ExtrinsicsLookupMode::USE_LOADED_PARAMS;
  std::string kimera_extrinsics_file = "";
  std::string sensor_frame = "";
  size_t image_queue_size = 10;
};

}  // namespace hydra

DECLARE_CONFIG_ENUM(hydra,
                    ExtrinsicsLookupMode,
                    {ExtrinsicsLookupMode::USE_KIMERA, "USE_KIMERA"},
                    {ExtrinsicsLookupMode::USE_TF, "USE_TF"},
                    {ExtrinsicsLookupMode::USE_LOADED_PARAMS, "USE_LOADED_PARAMS"})

namespace hydra {

template <typename Visitor>
void visit_config(const Visitor& v, RosReconstructionConfig& config) {
  config_parser::ConfigVisitor<ReconstructionConfig>::visit_base(v, config);
  v.visit("use_image_receiver", config.use_image_receiver);
  v.visit("publish_pointcloud", config.publish_pointcloud);
  v.visit("visualize_reconstruction", config.visualize_reconstruction);
  v.visit("topology_visualizer_ns", config.topology_visualizer_ns);
  v.visit("publish_reconstruction_mesh", config.publish_mesh);
  v.visit("enable_reconstruction_output_queue", config.enable_output_queue);
  v.visit("pointcloud_separation_s", config.pointcloud_separation_s);
  v.visit("tf_wait_duration_s", config.tf_wait_duration_s);
  v.visit("tf_buffer_size_s", config.tf_buffer_size_s);
  v.visit("image_queue_size", config.image_queue_size);
  v.visit("extrinsics_mode", config.extrinsics_mode);
  switch (config.extrinsics_mode) {
    case ExtrinsicsLookupMode::USE_KIMERA:
      v.visit("kimera_extrinsics_file", config.kimera_extrinsics_file);
      break;
    case ExtrinsicsLookupMode::USE_TF:
      v.visit("sensor_frame", config.sensor_frame);
      break;
    case ExtrinsicsLookupMode::USE_LOADED_PARAMS:
    default:
      break;
  }
}

bool loadReconstructionExtrinsics(RosReconstructionConfig& config);

}  // namespace hydra

DECLARE_CONFIG_OSTREAM_OPERATOR(hydra, RosReconstructionConfig);