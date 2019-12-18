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
struct intel_dp {int link_bw; int lane_count; scalar_t__ color_range; scalar_t__ color_range_auto; int /*<<< orphan*/  dpcd; struct intel_connector* attached_connector; } ;
struct TYPE_2__ {int /*<<< orphan*/  fitting_mode; scalar_t__ fixed_mode; } ;
struct intel_connector {TYPE_1__ panel; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_display_mode {int flags; int clock; int private_flags; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ DP_COLOR_RANGE_16_235 ; 
#define  DP_LINK_BW_1_62 129 
#define  DP_LINK_BW_2_7 128 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int,...) ; 
 int DRM_MODE_FLAG_DBLCLK ; 
 int INTEL_MODE_DP_FORCE_6BPC ; 
 int INTEL_MODE_LIMITED_COLOR_RANGE ; 
 int drm_dp_bw_code_to_link_rate (int) ; 
 int drm_dp_max_lane_count (int /*<<< orphan*/ ) ; 
 int drm_match_cea_mode (struct drm_display_mode*) ; 
 struct intel_dp* enc_to_intel_dp (struct drm_encoder*) ; 
 int /*<<< orphan*/  intel_dp_adjust_dithering (struct intel_dp*,struct drm_display_mode*,int) ; 
 int intel_dp_link_required (int,int) ; 
 int intel_dp_max_data_rate (int,int) ; 
 scalar_t__ intel_dp_max_link_bw (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_fixed_panel_mode (scalar_t__,struct drm_display_mode*) ; 
 int /*<<< orphan*/  intel_pch_panel_fitting (struct drm_device*,int /*<<< orphan*/ ,struct drm_display_mode const*,struct drm_display_mode*) ; 
 scalar_t__ is_edp (struct intel_dp*) ; 

bool
intel_dp_mode_fixup(struct drm_encoder *encoder,
		    const struct drm_display_mode *mode,
		    struct drm_display_mode *adjusted_mode)
{
	struct drm_device *dev = encoder->dev;
	struct intel_dp *intel_dp = enc_to_intel_dp(encoder);
	struct intel_connector *intel_connector = intel_dp->attached_connector;
	int lane_count, clock;
	int max_lane_count = drm_dp_max_lane_count(intel_dp->dpcd);
	int max_clock = intel_dp_max_link_bw(intel_dp) == DP_LINK_BW_2_7 ? 1 : 0;
	int bpp, mode_rate;
	static int bws[2] = { DP_LINK_BW_1_62, DP_LINK_BW_2_7 };

	if (is_edp(intel_dp) && intel_connector->panel.fixed_mode) {
		intel_fixed_panel_mode(intel_connector->panel.fixed_mode,
				       adjusted_mode);
		intel_pch_panel_fitting(dev,
					intel_connector->panel.fitting_mode,
					mode, adjusted_mode);
	}

	if (adjusted_mode->flags & DRM_MODE_FLAG_DBLCLK)
		return false;

	DRM_DEBUG_KMS("DP link computation with max lane count %i "
		      "max bw %02x pixel clock %iKHz\n",
		      max_lane_count, bws[max_clock], adjusted_mode->clock);

	if (!intel_dp_adjust_dithering(intel_dp, adjusted_mode, true))
		return false;

	bpp = adjusted_mode->private_flags & INTEL_MODE_DP_FORCE_6BPC ? 18 : 24;

	if (intel_dp->color_range_auto) {
		/*
		 * See:
		 * CEA-861-E - 5.1 Default Encoding Parameters
		 * VESA DisplayPort Ver.1.2a - 5.1.1.1 Video Colorimetry
		 */
		if (bpp != 18 && drm_match_cea_mode(adjusted_mode) > 1)
			intel_dp->color_range = DP_COLOR_RANGE_16_235;
		else
			intel_dp->color_range = 0;
	}

	if (intel_dp->color_range)
		adjusted_mode->private_flags |= INTEL_MODE_LIMITED_COLOR_RANGE;

	mode_rate = intel_dp_link_required(adjusted_mode->clock, bpp);

	for (clock = 0; clock <= max_clock; clock++) {
		for (lane_count = 1; lane_count <= max_lane_count; lane_count <<= 1) {
			int link_bw_clock =
				drm_dp_bw_code_to_link_rate(bws[clock]);
			int link_avail = intel_dp_max_data_rate(link_bw_clock,
								lane_count);

			if (mode_rate <= link_avail) {
				intel_dp->link_bw = bws[clock];
				intel_dp->lane_count = lane_count;
				adjusted_mode->clock = link_bw_clock;
				DRM_DEBUG_KMS("DP link bw %02x lane "
						"count %d clock %d bpp %d\n",
				       intel_dp->link_bw, intel_dp->lane_count,
				       adjusted_mode->clock, bpp);
				DRM_DEBUG_KMS("DP link bw required %i available %i\n",
					      mode_rate, link_avail);
				return true;
			}
		}
	}

	return false;
}