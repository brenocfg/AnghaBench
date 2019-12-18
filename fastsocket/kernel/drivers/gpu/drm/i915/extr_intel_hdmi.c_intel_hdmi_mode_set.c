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
typedef  int /*<<< orphan*/  u32 ;
struct intel_hdmi {int /*<<< orphan*/  (* set_infoframes ) (struct drm_encoder*,struct drm_display_mode*) ;int /*<<< orphan*/  sdvox_reg; scalar_t__ has_audio; scalar_t__ has_hdmi_sink; int /*<<< orphan*/  color_range; } ;
struct intel_crtc {int bpp; scalar_t__ pipe; } ;
struct drm_i915_private {int dummy; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; struct drm_device* dev; } ;
struct drm_display_mode {int flags; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_FORMAT_12bpc ; 
 int /*<<< orphan*/  COLOR_FORMAT_8bpc ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 scalar_t__ HAS_PCH_CPT (struct drm_device*) ; 
 int /*<<< orphan*/  HAS_PCH_SPLIT (struct drm_device*) ; 
 int /*<<< orphan*/  HDMI_MODE_SELECT ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PIPE_B ; 
 int /*<<< orphan*/  PORT_TRANS_SEL_CPT (scalar_t__) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDVO_AUDIO_ENABLE ; 
 int /*<<< orphan*/  SDVO_ENCODING_HDMI ; 
 int /*<<< orphan*/  SDVO_HSYNC_ACTIVE_HIGH ; 
 int /*<<< orphan*/  SDVO_NULL_PACKETS_DURING_VSYNC ; 
 int /*<<< orphan*/  SDVO_PIPE_B_SELECT ; 
 int /*<<< orphan*/  SDVO_VSYNC_ACTIVE_HIGH ; 
 struct intel_hdmi* enc_to_intel_hdmi (struct drm_encoder*) ; 
 int /*<<< orphan*/  intel_write_eld (struct drm_encoder*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  pipe_name (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct drm_encoder*,struct drm_display_mode*) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_hdmi_mode_set(struct drm_encoder *encoder,
				struct drm_display_mode *mode,
				struct drm_display_mode *adjusted_mode)
{
	struct drm_device *dev = encoder->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(encoder->crtc);
	struct intel_hdmi *intel_hdmi = enc_to_intel_hdmi(encoder);
	u32 sdvox;

	sdvox = SDVO_ENCODING_HDMI;
	if (!HAS_PCH_SPLIT(dev))
		sdvox |= intel_hdmi->color_range;
	if (adjusted_mode->flags & DRM_MODE_FLAG_PVSYNC)
		sdvox |= SDVO_VSYNC_ACTIVE_HIGH;
	if (adjusted_mode->flags & DRM_MODE_FLAG_PHSYNC)
		sdvox |= SDVO_HSYNC_ACTIVE_HIGH;

	if (intel_crtc->bpp > 24)
		sdvox |= COLOR_FORMAT_12bpc;
	else
		sdvox |= COLOR_FORMAT_8bpc;

	/* Required on CPT */
	if (intel_hdmi->has_hdmi_sink && HAS_PCH_CPT(dev))
		sdvox |= HDMI_MODE_SELECT;

	if (intel_hdmi->has_audio) {
		DRM_DEBUG_DRIVER("Enabling HDMI audio on pipe %c\n",
				 pipe_name(intel_crtc->pipe));
		sdvox |= SDVO_AUDIO_ENABLE;
		sdvox |= SDVO_NULL_PACKETS_DURING_VSYNC;
		intel_write_eld(encoder, adjusted_mode);
	}

	if (HAS_PCH_CPT(dev))
		sdvox |= PORT_TRANS_SEL_CPT(intel_crtc->pipe);
	else if (intel_crtc->pipe == PIPE_B)
		sdvox |= SDVO_PIPE_B_SELECT;

	I915_WRITE(intel_hdmi->sdvox_reg, sdvox);
	POSTING_READ(intel_hdmi->sdvox_reg);

	intel_hdmi->set_infoframes(encoder, adjusted_mode);
}