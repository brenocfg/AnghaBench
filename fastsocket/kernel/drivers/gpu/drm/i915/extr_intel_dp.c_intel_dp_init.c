#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_encoder {int dummy; } ;
struct intel_encoder {int crtc_mask; int cloneable; int /*<<< orphan*/  hot_plug; int /*<<< orphan*/  type; int /*<<< orphan*/  get_hw_state; int /*<<< orphan*/  post_disable; int /*<<< orphan*/  disable; int /*<<< orphan*/  pre_enable; int /*<<< orphan*/  enable; struct drm_encoder base; } ;
struct TYPE_2__ {int output_reg; } ;
struct intel_digital_port {int port; TYPE_1__ dp; struct intel_encoder base; } ;
struct intel_connector {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ENCODER_TMDS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INTEL_OUTPUT_DISPLAYPORT ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_disable_dp ; 
 int /*<<< orphan*/  intel_dp_enc_funcs ; 
 int /*<<< orphan*/  intel_dp_get_hw_state ; 
 int /*<<< orphan*/  intel_dp_helper_funcs ; 
 int /*<<< orphan*/  intel_dp_hot_plug ; 
 int /*<<< orphan*/  intel_dp_init_connector (struct intel_digital_port*,struct intel_connector*) ; 
 int /*<<< orphan*/  intel_enable_dp ; 
 int /*<<< orphan*/  intel_post_disable_dp ; 
 int /*<<< orphan*/  intel_pre_enable_dp ; 
 int /*<<< orphan*/  kfree (struct intel_digital_port*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

void
intel_dp_init(struct drm_device *dev, int output_reg, enum port port)
{
	struct intel_digital_port *intel_dig_port;
	struct intel_encoder *intel_encoder;
	struct drm_encoder *encoder;
	struct intel_connector *intel_connector;

	intel_dig_port = kzalloc(sizeof(struct intel_digital_port), GFP_KERNEL);
	if (!intel_dig_port)
		return;

	intel_connector = kzalloc(sizeof(struct intel_connector), GFP_KERNEL);
	if (!intel_connector) {
		kfree(intel_dig_port);
		return;
	}

	intel_encoder = &intel_dig_port->base;
	encoder = &intel_encoder->base;

	drm_encoder_init(dev, &intel_encoder->base, &intel_dp_enc_funcs,
			 DRM_MODE_ENCODER_TMDS);
	drm_encoder_helper_add(&intel_encoder->base, &intel_dp_helper_funcs);

	intel_encoder->enable = intel_enable_dp;
	intel_encoder->pre_enable = intel_pre_enable_dp;
	intel_encoder->disable = intel_disable_dp;
	intel_encoder->post_disable = intel_post_disable_dp;
	intel_encoder->get_hw_state = intel_dp_get_hw_state;

	intel_dig_port->port = port;
	intel_dig_port->dp.output_reg = output_reg;

	intel_encoder->type = INTEL_OUTPUT_DISPLAYPORT;
	intel_encoder->crtc_mask = (1 << 0) | (1 << 1) | (1 << 2);
	intel_encoder->cloneable = false;
	intel_encoder->hot_plug = intel_dp_hot_plug;

	intel_dp_init_connector(intel_dig_port, intel_connector);
}