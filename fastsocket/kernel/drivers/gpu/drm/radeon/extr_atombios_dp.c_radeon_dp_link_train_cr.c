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
typedef  int u8 ;
struct radeon_dp_link_train_info {int* train_set; int tries; int dp_lane_count; int /*<<< orphan*/  link_status; int /*<<< orphan*/  radeon_connector; int /*<<< orphan*/  dpcd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_TRAINING_PATTERN_1 ; 
 int DP_TRAIN_MAX_SWING_REACHED ; 
 int DP_TRAIN_PRE_EMPHASIS_MASK ; 
 int DP_TRAIN_PRE_EMPHASIS_SHIFT ; 
 int DP_TRAIN_VOLTAGE_SWING_MASK ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  dp_get_adjust_train (int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ drm_dp_clock_recovery_ok (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_dp_link_train_clock_recovery_delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_dp_get_link_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_dp_set_tp (struct radeon_dp_link_train_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_dp_update_vs_emph (struct radeon_dp_link_train_info*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int radeon_dp_link_train_cr(struct radeon_dp_link_train_info *dp_info)
{
	bool clock_recovery;
 	u8 voltage;
	int i;

	radeon_dp_set_tp(dp_info, DP_TRAINING_PATTERN_1);
	memset(dp_info->train_set, 0, 4);
	radeon_dp_update_vs_emph(dp_info);

	udelay(400);

	/* clock recovery loop */
	clock_recovery = false;
	dp_info->tries = 0;
	voltage = 0xff;
	while (1) {
		drm_dp_link_train_clock_recovery_delay(dp_info->dpcd);

		if (!radeon_dp_get_link_status(dp_info->radeon_connector, dp_info->link_status)) {
			DRM_ERROR("displayport link status failed\n");
			break;
		}

		if (drm_dp_clock_recovery_ok(dp_info->link_status, dp_info->dp_lane_count)) {
			clock_recovery = true;
			break;
		}

		for (i = 0; i < dp_info->dp_lane_count; i++) {
			if ((dp_info->train_set[i] & DP_TRAIN_MAX_SWING_REACHED) == 0)
				break;
		}
		if (i == dp_info->dp_lane_count) {
			DRM_ERROR("clock recovery reached max voltage\n");
			break;
		}

		if ((dp_info->train_set[0] & DP_TRAIN_VOLTAGE_SWING_MASK) == voltage) {
			++dp_info->tries;
			if (dp_info->tries == 5) {
				DRM_ERROR("clock recovery tried 5 times\n");
				break;
			}
		} else
			dp_info->tries = 0;

		voltage = dp_info->train_set[0] & DP_TRAIN_VOLTAGE_SWING_MASK;

		/* Compute new train_set as requested by sink */
		dp_get_adjust_train(dp_info->link_status, dp_info->dp_lane_count, dp_info->train_set);

		radeon_dp_update_vs_emph(dp_info);
	}
	if (!clock_recovery) {
		DRM_ERROR("clock recovery failed\n");
		return -1;
	} else {
		DRM_DEBUG_KMS("clock recovery at voltage %d pre-emphasis %d\n",
			  dp_info->train_set[0] & DP_TRAIN_VOLTAGE_SWING_MASK,
			  (dp_info->train_set[0] & DP_TRAIN_PRE_EMPHASIS_MASK) >>
			  DP_TRAIN_PRE_EMPHASIS_SHIFT);
		return 0;
	}
}