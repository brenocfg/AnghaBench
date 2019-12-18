#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct intel_hdmi {scalar_t__ has_hdmi_sink; } ;
struct drm_encoder {int dummy; } ;
struct intel_encoder {int type; struct drm_encoder base; } ;
struct intel_dp {int lane_count; } ;
struct intel_crtc {int pipe; int cpu_transcoder; int bpp; int fdi_lanes; } ;
struct drm_i915_private {int /*<<< orphan*/  pch_pf_size; } ;
struct TYPE_4__ {int flags; } ;
struct drm_crtc {TYPE_2__ mode; TYPE_1__* dev; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_3__ {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_OUTPUT_ANALOG ; 
 int INTEL_OUTPUT_DISPLAYPORT ; 
 int INTEL_OUTPUT_EDP ; 
 int INTEL_OUTPUT_HDMI ; 
#define  PIPE_A 130 
#define  PIPE_B 129 
#define  PIPE_C 128 
 int TRANSCODER_EDP ; 
 int TRANS_DDI_BPC_10 ; 
 int TRANS_DDI_BPC_12 ; 
 int TRANS_DDI_BPC_6 ; 
 int TRANS_DDI_BPC_8 ; 
 int TRANS_DDI_EDP_INPUT_A_ON ; 
 int TRANS_DDI_EDP_INPUT_A_ONOFF ; 
 int TRANS_DDI_EDP_INPUT_B_ONOFF ; 
 int TRANS_DDI_EDP_INPUT_C_ONOFF ; 
 int /*<<< orphan*/  TRANS_DDI_FUNC_CTL (int) ; 
 int TRANS_DDI_FUNC_ENABLE ; 
 int TRANS_DDI_MODE_SELECT_DP_SST ; 
 int TRANS_DDI_MODE_SELECT_DVI ; 
 int TRANS_DDI_MODE_SELECT_FDI ; 
 int TRANS_DDI_MODE_SELECT_HDMI ; 
 int TRANS_DDI_PHSYNC ; 
 int TRANS_DDI_PORT_WIDTH_X1 ; 
 int TRANS_DDI_PORT_WIDTH_X2 ; 
 int TRANS_DDI_PORT_WIDTH_X4 ; 
 int TRANS_DDI_PVSYNC ; 
 int TRANS_DDI_SELECT_PORT (int) ; 
 int /*<<< orphan*/  WARN (int,char*,int,...) ; 
 struct intel_dp* enc_to_intel_dp (struct drm_encoder*) ; 
 struct intel_hdmi* enc_to_intel_hdmi (struct drm_encoder*) ; 
 struct intel_encoder* intel_ddi_get_crtc_encoder (struct drm_crtc*) ; 
 int intel_ddi_get_encoder_port (struct intel_encoder*) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

void intel_ddi_enable_pipe_func(struct drm_crtc *crtc)
{
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	struct intel_encoder *intel_encoder = intel_ddi_get_crtc_encoder(crtc);
	struct drm_encoder *encoder = &intel_encoder->base;
	struct drm_i915_private *dev_priv = crtc->dev->dev_private;
	enum pipe pipe = intel_crtc->pipe;
	enum transcoder cpu_transcoder = intel_crtc->cpu_transcoder;
	enum port port = intel_ddi_get_encoder_port(intel_encoder);
	int type = intel_encoder->type;
	uint32_t temp;

	/* Enable TRANS_DDI_FUNC_CTL for the pipe to work in HDMI mode */
	temp = TRANS_DDI_FUNC_ENABLE;
	temp |= TRANS_DDI_SELECT_PORT(port);

	switch (intel_crtc->bpp) {
	case 18:
		temp |= TRANS_DDI_BPC_6;
		break;
	case 24:
		temp |= TRANS_DDI_BPC_8;
		break;
	case 30:
		temp |= TRANS_DDI_BPC_10;
		break;
	case 36:
		temp |= TRANS_DDI_BPC_12;
		break;
	default:
		WARN(1, "%d bpp unsupported by transcoder DDI function\n",
		     intel_crtc->bpp);
	}

	if (crtc->mode.flags & DRM_MODE_FLAG_PVSYNC)
		temp |= TRANS_DDI_PVSYNC;
	if (crtc->mode.flags & DRM_MODE_FLAG_PHSYNC)
		temp |= TRANS_DDI_PHSYNC;

	if (cpu_transcoder == TRANSCODER_EDP) {
		switch (pipe) {
		case PIPE_A:
			/* Can only use the always-on power well for eDP when
			 * not using the panel fitter, and when not using motion
			  * blur mitigation (which we don't support). */
			if (dev_priv->pch_pf_size)
				temp |= TRANS_DDI_EDP_INPUT_A_ONOFF;
			else
				temp |= TRANS_DDI_EDP_INPUT_A_ON;
			break;
		case PIPE_B:
			temp |= TRANS_DDI_EDP_INPUT_B_ONOFF;
			break;
		case PIPE_C:
			temp |= TRANS_DDI_EDP_INPUT_C_ONOFF;
			break;
		default:
			BUG();
			break;
		}
	}

	if (type == INTEL_OUTPUT_HDMI) {
		struct intel_hdmi *intel_hdmi = enc_to_intel_hdmi(encoder);

		if (intel_hdmi->has_hdmi_sink)
			temp |= TRANS_DDI_MODE_SELECT_HDMI;
		else
			temp |= TRANS_DDI_MODE_SELECT_DVI;

	} else if (type == INTEL_OUTPUT_ANALOG) {
		temp |= TRANS_DDI_MODE_SELECT_FDI;
		temp |= (intel_crtc->fdi_lanes - 1) << 1;

	} else if (type == INTEL_OUTPUT_DISPLAYPORT ||
		   type == INTEL_OUTPUT_EDP) {
		struct intel_dp *intel_dp = enc_to_intel_dp(encoder);

		temp |= TRANS_DDI_MODE_SELECT_DP_SST;

		switch (intel_dp->lane_count) {
		case 1:
			temp |= TRANS_DDI_PORT_WIDTH_X1;
			break;
		case 2:
			temp |= TRANS_DDI_PORT_WIDTH_X2;
			break;
		case 4:
			temp |= TRANS_DDI_PORT_WIDTH_X4;
			break;
		default:
			temp |= TRANS_DDI_PORT_WIDTH_X4;
			WARN(1, "Unsupported lane count %d\n",
			     intel_dp->lane_count);
		}

	} else {
		WARN(1, "Invalid encoder type %d for pipe %d\n",
		     intel_encoder->type, pipe);
	}

	I915_WRITE(TRANS_DDI_FUNC_CTL(cpu_transcoder), temp);
}