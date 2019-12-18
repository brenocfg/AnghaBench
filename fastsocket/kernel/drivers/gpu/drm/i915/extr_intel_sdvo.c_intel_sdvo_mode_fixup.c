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
struct intel_sdvo {scalar_t__ color_range; scalar_t__ has_hdmi_monitor; scalar_t__ color_range_auto; struct drm_display_mode const* sdvo_lvds_fixed_mode; scalar_t__ is_lvds; scalar_t__ is_tv; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int /*<<< orphan*/  private_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_MODE_LIMITED_COLOR_RANGE ; 
 scalar_t__ SDVO_COLOR_RANGE_16_235 ; 
 int drm_match_cea_mode (struct drm_display_mode*) ; 
 int /*<<< orphan*/  intel_mode_set_pixel_multiplier (struct drm_display_mode*,int) ; 
 int intel_sdvo_get_pixel_multiplier (struct drm_display_mode*) ; 
 int /*<<< orphan*/  intel_sdvo_get_preferred_input_mode (struct intel_sdvo*,struct drm_display_mode const*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  intel_sdvo_set_output_timings_from_mode (struct intel_sdvo*,struct drm_display_mode const*) ; 
 struct intel_sdvo* to_intel_sdvo (struct drm_encoder*) ; 

__attribute__((used)) static bool intel_sdvo_mode_fixup(struct drm_encoder *encoder,
				  const struct drm_display_mode *mode,
				  struct drm_display_mode *adjusted_mode)
{
	struct intel_sdvo *intel_sdvo = to_intel_sdvo(encoder);
	int multiplier;

	/* We need to construct preferred input timings based on our
	 * output timings.  To do that, we have to set the output
	 * timings, even though this isn't really the right place in
	 * the sequence to do it. Oh well.
	 */
	if (intel_sdvo->is_tv) {
		if (!intel_sdvo_set_output_timings_from_mode(intel_sdvo, mode))
			return false;

		(void) intel_sdvo_get_preferred_input_mode(intel_sdvo,
							   mode,
							   adjusted_mode);
	} else if (intel_sdvo->is_lvds) {
		if (!intel_sdvo_set_output_timings_from_mode(intel_sdvo,
							     intel_sdvo->sdvo_lvds_fixed_mode))
			return false;

		(void) intel_sdvo_get_preferred_input_mode(intel_sdvo,
							   mode,
							   adjusted_mode);
	}

	/* Make the CRTC code factor in the SDVO pixel multiplier.  The
	 * SDVO device will factor out the multiplier during mode_set.
	 */
	multiplier = intel_sdvo_get_pixel_multiplier(adjusted_mode);
	intel_mode_set_pixel_multiplier(adjusted_mode, multiplier);

	if (intel_sdvo->color_range_auto) {
		/* See CEA-861-E - 5.1 Default Encoding Parameters */
		if (intel_sdvo->has_hdmi_monitor &&
		    drm_match_cea_mode(adjusted_mode) > 1)
			intel_sdvo->color_range = SDVO_COLOR_RANGE_16_235;
		else
			intel_sdvo->color_range = 0;
	}

	if (intel_sdvo->color_range)
		adjusted_mode->private_flags |= INTEL_MODE_LIMITED_COLOR_RANGE;

	return true;
}