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
struct intel_dp {int /*<<< orphan*/  dpcd; } ;
struct drm_display_mode {int /*<<< orphan*/  private_flags; int /*<<< orphan*/  clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_MODE_DP_FORCE_6BPC ; 
 int drm_dp_bw_code_to_link_rate (int /*<<< orphan*/ ) ; 
 int drm_dp_max_lane_count (int /*<<< orphan*/ ) ; 
 int intel_dp_link_required (int /*<<< orphan*/ ,int) ; 
 int intel_dp_max_data_rate (int,int) ; 
 int /*<<< orphan*/  intel_dp_max_link_bw (struct intel_dp*) ; 

__attribute__((used)) static bool
intel_dp_adjust_dithering(struct intel_dp *intel_dp,
			  struct drm_display_mode *mode,
			  bool adjust_mode)
{
	int max_link_clock =
		drm_dp_bw_code_to_link_rate(intel_dp_max_link_bw(intel_dp));
	int max_lanes = drm_dp_max_lane_count(intel_dp->dpcd);
	int max_rate, mode_rate;

	mode_rate = intel_dp_link_required(mode->clock, 24);
	max_rate = intel_dp_max_data_rate(max_link_clock, max_lanes);

	if (mode_rate > max_rate) {
		mode_rate = intel_dp_link_required(mode->clock, 18);
		if (mode_rate > max_rate)
			return false;

		if (adjust_mode)
			mode->private_flags
				|= INTEL_MODE_DP_FORCE_6BPC;

		return true;
	}

	return true;
}