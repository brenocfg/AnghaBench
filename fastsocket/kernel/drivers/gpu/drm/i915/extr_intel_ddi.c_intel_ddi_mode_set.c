#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct intel_hdmi {int /*<<< orphan*/  (* set_infoframes ) (struct drm_encoder*,struct drm_display_mode*) ;scalar_t__ has_audio; } ;
struct intel_encoder {int type; } ;
struct intel_dp {int DP; int lane_count; scalar_t__ has_audio; } ;
struct intel_digital_port {int port_reversal; } ;
struct intel_crtc {int pipe; int eld_vld; } ;
struct drm_encoder {struct drm_crtc* crtc; } ;
struct drm_display_mode {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int DDI_BUF_CTL_ENABLE ; 
 int DDI_BUF_EMP_400MV_0DB_HSW ; 
 int DDI_PORT_WIDTH_X1 ; 
 int DDI_PORT_WIDTH_X2 ; 
 int DDI_PORT_WIDTH_X4 ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,...) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INTEL_OUTPUT_DISPLAYPORT ; 
 int INTEL_OUTPUT_EDP ; 
 int INTEL_OUTPUT_HDMI ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 struct intel_digital_port* enc_to_dig_port (struct drm_encoder*) ; 
 struct intel_dp* enc_to_intel_dp (struct drm_encoder*) ; 
 struct intel_hdmi* enc_to_intel_hdmi (struct drm_encoder*) ; 
 int intel_ddi_get_encoder_port (struct intel_encoder*) ; 
 int /*<<< orphan*/  intel_dp_init_link_config (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_write_eld (struct drm_encoder*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 int /*<<< orphan*/  port_name (int) ; 
 int /*<<< orphan*/  stub1 (struct drm_encoder*,struct drm_display_mode*) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 
 struct intel_encoder* to_intel_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void intel_ddi_mode_set(struct drm_encoder *encoder,
			       struct drm_display_mode *mode,
			       struct drm_display_mode *adjusted_mode)
{
	struct drm_crtc *crtc = encoder->crtc;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	struct intel_encoder *intel_encoder = to_intel_encoder(encoder);
	int port = intel_ddi_get_encoder_port(intel_encoder);
	int pipe = intel_crtc->pipe;
	int type = intel_encoder->type;

	DRM_DEBUG_KMS("Preparing DDI mode for Haswell on port %c, pipe %c\n",
		      port_name(port), pipe_name(pipe));

	intel_crtc->eld_vld = false;
	if (type == INTEL_OUTPUT_DISPLAYPORT || type == INTEL_OUTPUT_EDP) {
		struct intel_dp *intel_dp = enc_to_intel_dp(encoder);
		struct intel_digital_port *intel_dig_port =
			enc_to_dig_port(encoder);

		intel_dp->DP = intel_dig_port->port_reversal |
			       DDI_BUF_CTL_ENABLE | DDI_BUF_EMP_400MV_0DB_HSW;
		switch (intel_dp->lane_count) {
		case 1:
			intel_dp->DP |= DDI_PORT_WIDTH_X1;
			break;
		case 2:
			intel_dp->DP |= DDI_PORT_WIDTH_X2;
			break;
		case 4:
			intel_dp->DP |= DDI_PORT_WIDTH_X4;
			break;
		default:
			intel_dp->DP |= DDI_PORT_WIDTH_X4;
			WARN(1, "Unexpected DP lane count %d\n",
			     intel_dp->lane_count);
			break;
		}

		if (intel_dp->has_audio) {
			DRM_DEBUG_DRIVER("DP audio on pipe %c on DDI\n",
					 pipe_name(intel_crtc->pipe));

			/* write eld */
			DRM_DEBUG_DRIVER("DP audio: write eld information\n");
			intel_write_eld(encoder, adjusted_mode);
		}

		intel_dp_init_link_config(intel_dp);

	} else if (type == INTEL_OUTPUT_HDMI) {
		struct intel_hdmi *intel_hdmi = enc_to_intel_hdmi(encoder);

		if (intel_hdmi->has_audio) {
			/* Proper support for digital audio needs a new logic
			 * and a new set of registers, so we leave it for future
			 * patch bombing.
			 */
			DRM_DEBUG_DRIVER("HDMI audio on pipe %c on DDI\n",
					 pipe_name(intel_crtc->pipe));

			/* write eld */
			DRM_DEBUG_DRIVER("HDMI audio: write eld information\n");
			intel_write_eld(encoder, adjusted_mode);
		}

		intel_hdmi->set_infoframes(encoder, adjusted_mode);
	}
}