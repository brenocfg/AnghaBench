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
typedef  int uint32_t ;
struct intel_encoder {int /*<<< orphan*/  (* get_hw_state ) (struct intel_encoder*,int*) ;} ;
struct TYPE_2__ {int connector_type; struct drm_device* dev; } ;
struct intel_connector {TYPE_1__ base; struct intel_encoder* encoder; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int DRM_MODE_CONNECTOR_DisplayPort ; 
 int DRM_MODE_CONNECTOR_HDMIA ; 
 int DRM_MODE_CONNECTOR_VGA ; 
 int DRM_MODE_CONNECTOR_eDP ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int PORT_A ; 
 int TRANSCODER_EDP ; 
 int /*<<< orphan*/  TRANS_DDI_FUNC_CTL (int) ; 
#define  TRANS_DDI_MODE_SELECT_DP_MST 132 
#define  TRANS_DDI_MODE_SELECT_DP_SST 131 
#define  TRANS_DDI_MODE_SELECT_DVI 130 
#define  TRANS_DDI_MODE_SELECT_FDI 129 
#define  TRANS_DDI_MODE_SELECT_HDMI 128 
 int TRANS_DDI_MODE_SELECT_MASK ; 
 int intel_ddi_get_encoder_port (struct intel_encoder*) ; 
 int /*<<< orphan*/  stub1 (struct intel_encoder*,int*) ; 

bool intel_ddi_connector_get_hw_state(struct intel_connector *intel_connector)
{
	struct drm_device *dev = intel_connector->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_encoder *intel_encoder = intel_connector->encoder;
	int type = intel_connector->base.connector_type;
	enum port port = intel_ddi_get_encoder_port(intel_encoder);
	enum pipe pipe = 0;
	enum transcoder cpu_transcoder;
	uint32_t tmp;

	if (!intel_encoder->get_hw_state(intel_encoder, &pipe))
		return false;

	if (port == PORT_A)
		cpu_transcoder = TRANSCODER_EDP;
	else
		cpu_transcoder = (enum transcoder) pipe;

	tmp = I915_READ(TRANS_DDI_FUNC_CTL(cpu_transcoder));

	switch (tmp & TRANS_DDI_MODE_SELECT_MASK) {
	case TRANS_DDI_MODE_SELECT_HDMI:
	case TRANS_DDI_MODE_SELECT_DVI:
		return (type == DRM_MODE_CONNECTOR_HDMIA);

	case TRANS_DDI_MODE_SELECT_DP_SST:
		if (type == DRM_MODE_CONNECTOR_eDP)
			return true;
	case TRANS_DDI_MODE_SELECT_DP_MST:
		return (type == DRM_MODE_CONNECTOR_DisplayPort);

	case TRANS_DDI_MODE_SELECT_FDI:
		return (type == DRM_MODE_CONNECTOR_VGA);

	default:
		return false;
	}
}