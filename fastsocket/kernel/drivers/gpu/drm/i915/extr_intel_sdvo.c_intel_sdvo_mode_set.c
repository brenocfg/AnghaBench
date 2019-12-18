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
typedef  int u32 ;
struct intel_sdvo_in_out_map {scalar_t__ in1; int /*<<< orphan*/  in0; } ;
struct TYPE_3__ {int sdvo_flags; } ;
struct intel_sdvo_dtd {TYPE_1__ part2; } ;
struct intel_sdvo {int dtd_sdvo_flags; int color_range; int sdvo_reg; scalar_t__ has_hdmi_audio; scalar_t__ is_hdmi; scalar_t__ is_lvds; scalar_t__ is_tv; scalar_t__ has_hdmi_monitor; struct drm_display_mode* sdvo_lvds_fixed_mode; int /*<<< orphan*/  attached_output; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; } ;
struct drm_i915_private {int dummy; } ;
struct drm_encoder {struct drm_crtc* crtc; struct drm_device* dev; } ;
struct drm_display_mode {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct drm_crtc {int dummy; } ;
typedef  int /*<<< orphan*/  in_out ;
struct TYPE_4__ {int gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAS_PCH_SPLIT (struct drm_device*) ; 
 int I915_READ (int) ; 
 TYPE_2__* INTEL_INFO (struct drm_device*) ; 
 scalar_t__ INTEL_PCH_TYPE (struct drm_device*) ; 
 scalar_t__ IS_G33 (struct drm_device*) ; 
 scalar_t__ IS_I945G (struct drm_device*) ; 
 scalar_t__ IS_I945GM (struct drm_device*) ; 
 scalar_t__ PCH_CPT ; 
#define  SDVOB 129 
 int SDVOB_PRESERVE_MASK ; 
#define  SDVOC 128 
 int SDVOC_PRESERVE_MASK ; 
 int SDVO_AUDIO_ENABLE ; 
 int SDVO_BORDER_ENABLE ; 
 int SDVO_CLOCK_RATE_MULT_1X ; 
 int SDVO_CLOCK_RATE_MULT_2X ; 
 int SDVO_CLOCK_RATE_MULT_4X ; 
 int /*<<< orphan*/  SDVO_CMD_SET_IN_OUT_MAP ; 
 int /*<<< orphan*/  SDVO_COLORIMETRY_RGB256 ; 
 int /*<<< orphan*/  SDVO_ENCODE_DVI ; 
 int /*<<< orphan*/  SDVO_ENCODE_HDMI ; 
 int SDVO_HSYNC_ACTIVE_HIGH ; 
 int /*<<< orphan*/  SDVO_NAME (struct intel_sdvo*) ; 
 int SDVO_NEED_TO_STALL ; 
 int SDVO_PORT_MULTIPLY_SHIFT ; 
 int SDVO_STALL_SELECT ; 
 int SDVO_VSYNC_ACTIVE_HIGH ; 
 int TRANSCODER (int /*<<< orphan*/ ) ; 
 int TRANSCODER_CPT (int /*<<< orphan*/ ) ; 
 int intel_mode_get_pixel_multiplier (struct drm_display_mode*) ; 
 int /*<<< orphan*/  intel_sdvo_get_dtd_from_mode (struct intel_sdvo_dtd*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  intel_sdvo_set_avi_infoframe (struct intel_sdvo*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  intel_sdvo_set_clock_rate_mult (struct intel_sdvo*,int) ; 
 int /*<<< orphan*/  intel_sdvo_set_colorimetry (struct intel_sdvo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_sdvo_set_encode (struct intel_sdvo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_sdvo_set_input_timing (struct intel_sdvo*,struct intel_sdvo_dtd*) ; 
 int /*<<< orphan*/  intel_sdvo_set_output_timing (struct intel_sdvo*,struct intel_sdvo_dtd*) ; 
 int /*<<< orphan*/  intel_sdvo_set_target_input (struct intel_sdvo*) ; 
 int /*<<< orphan*/  intel_sdvo_set_target_output (struct intel_sdvo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_sdvo_set_tv_format (struct intel_sdvo*) ; 
 int /*<<< orphan*/  intel_sdvo_set_value (struct intel_sdvo*,int /*<<< orphan*/ ,struct intel_sdvo_in_out_map*,int) ; 
 int /*<<< orphan*/  intel_sdvo_write_sdvox (struct intel_sdvo*,int) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 
 struct intel_sdvo* to_intel_sdvo (struct drm_encoder*) ; 

__attribute__((used)) static void intel_sdvo_mode_set(struct drm_encoder *encoder,
				struct drm_display_mode *mode,
				struct drm_display_mode *adjusted_mode)
{
	struct drm_device *dev = encoder->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_crtc *crtc = encoder->crtc;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	struct intel_sdvo *intel_sdvo = to_intel_sdvo(encoder);
	u32 sdvox;
	struct intel_sdvo_in_out_map in_out;
	struct intel_sdvo_dtd input_dtd, output_dtd;
	int pixel_multiplier = intel_mode_get_pixel_multiplier(adjusted_mode);
	int rate;

	if (!mode)
		return;

	/* First, set the input mapping for the first input to our controlled
	 * output. This is only correct if we're a single-input device, in
	 * which case the first input is the output from the appropriate SDVO
	 * channel on the motherboard.  In a two-input device, the first input
	 * will be SDVOB and the second SDVOC.
	 */
	in_out.in0 = intel_sdvo->attached_output;
	in_out.in1 = 0;

	intel_sdvo_set_value(intel_sdvo,
			     SDVO_CMD_SET_IN_OUT_MAP,
			     &in_out, sizeof(in_out));

	/* Set the output timings to the screen */
	if (!intel_sdvo_set_target_output(intel_sdvo,
					  intel_sdvo->attached_output))
		return;

	/* lvds has a special fixed output timing. */
	if (intel_sdvo->is_lvds)
		intel_sdvo_get_dtd_from_mode(&output_dtd,
					     intel_sdvo->sdvo_lvds_fixed_mode);
	else
		intel_sdvo_get_dtd_from_mode(&output_dtd, mode);
	if (!intel_sdvo_set_output_timing(intel_sdvo, &output_dtd))
		DRM_INFO("Setting output timings on %s failed\n",
			 SDVO_NAME(intel_sdvo));

	/* Set the input timing to the screen. Assume always input 0. */
	if (!intel_sdvo_set_target_input(intel_sdvo))
		return;

	if (intel_sdvo->has_hdmi_monitor) {
		intel_sdvo_set_encode(intel_sdvo, SDVO_ENCODE_HDMI);
		intel_sdvo_set_colorimetry(intel_sdvo,
					   SDVO_COLORIMETRY_RGB256);
		intel_sdvo_set_avi_infoframe(intel_sdvo, adjusted_mode);
	} else
		intel_sdvo_set_encode(intel_sdvo, SDVO_ENCODE_DVI);

	if (intel_sdvo->is_tv &&
	    !intel_sdvo_set_tv_format(intel_sdvo))
		return;

	/* We have tried to get input timing in mode_fixup, and filled into
	 * adjusted_mode.
	 */
	intel_sdvo_get_dtd_from_mode(&input_dtd, adjusted_mode);
	if (intel_sdvo->is_tv || intel_sdvo->is_lvds)
		input_dtd.part2.sdvo_flags = intel_sdvo->dtd_sdvo_flags;
	if (!intel_sdvo_set_input_timing(intel_sdvo, &input_dtd))
		DRM_INFO("Setting input timings on %s failed\n",
			 SDVO_NAME(intel_sdvo));

	switch (pixel_multiplier) {
	default:
	case 1: rate = SDVO_CLOCK_RATE_MULT_1X; break;
	case 2: rate = SDVO_CLOCK_RATE_MULT_2X; break;
	case 4: rate = SDVO_CLOCK_RATE_MULT_4X; break;
	}
	if (!intel_sdvo_set_clock_rate_mult(intel_sdvo, rate))
		return;

	/* Set the SDVO control regs. */
	if (INTEL_INFO(dev)->gen >= 4) {
		/* The real mode polarity is set by the SDVO commands, using
		 * struct intel_sdvo_dtd. */
		sdvox = SDVO_VSYNC_ACTIVE_HIGH | SDVO_HSYNC_ACTIVE_HIGH;
		if (!HAS_PCH_SPLIT(dev) && intel_sdvo->is_hdmi)
			sdvox |= intel_sdvo->color_range;
		if (INTEL_INFO(dev)->gen < 5)
			sdvox |= SDVO_BORDER_ENABLE;
	} else {
		sdvox = I915_READ(intel_sdvo->sdvo_reg);
		switch (intel_sdvo->sdvo_reg) {
		case SDVOB:
			sdvox &= SDVOB_PRESERVE_MASK;
			break;
		case SDVOC:
			sdvox &= SDVOC_PRESERVE_MASK;
			break;
		}
		sdvox |= (9 << 19) | SDVO_BORDER_ENABLE;
	}

	if (INTEL_PCH_TYPE(dev) >= PCH_CPT)
		sdvox |= TRANSCODER_CPT(intel_crtc->pipe);
	else
		sdvox |= TRANSCODER(intel_crtc->pipe);

	if (intel_sdvo->has_hdmi_audio)
		sdvox |= SDVO_AUDIO_ENABLE;

	if (INTEL_INFO(dev)->gen >= 4) {
		/* done in crtc_mode_set as the dpll_md reg must be written early */
	} else if (IS_I945G(dev) || IS_I945GM(dev) || IS_G33(dev)) {
		/* done in crtc_mode_set as it lives inside the dpll register */
	} else {
		sdvox |= (pixel_multiplier - 1) << SDVO_PORT_MULTIPLY_SHIFT;
	}

	if (input_dtd.part2.sdvo_flags & SDVO_NEED_TO_STALL &&
	    INTEL_INFO(dev)->gen < 5)
		sdvox |= SDVO_STALL_SELECT;
	intel_sdvo_write_sdvox(intel_sdvo, sdvox);
}