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
struct intel_dp {int* dpcd; int /*<<< orphan*/ * link_configuration; int /*<<< orphan*/  lane_count; int /*<<< orphan*/  link_bw; } ;

/* Variables and functions */
 size_t DP_DPCD_REV ; 
 int DP_ENHANCED_FRAME_CAP ; 
 int /*<<< orphan*/  DP_LANE_COUNT_ENHANCED_FRAME_EN ; 
 int /*<<< orphan*/  DP_LINK_CONFIGURATION_SIZE ; 
 size_t DP_MAX_LANE_COUNT ; 
 int /*<<< orphan*/  DP_SET_ANSI_8B10B ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void intel_dp_init_link_config(struct intel_dp *intel_dp)
{
	memset(intel_dp->link_configuration, 0, DP_LINK_CONFIGURATION_SIZE);
	intel_dp->link_configuration[0] = intel_dp->link_bw;
	intel_dp->link_configuration[1] = intel_dp->lane_count;
	intel_dp->link_configuration[8] = DP_SET_ANSI_8B10B;
	/*
	 * Check for DPCD version > 1.1 and enhanced framing support
	 */
	if (intel_dp->dpcd[DP_DPCD_REV] >= 0x11 &&
	    (intel_dp->dpcd[DP_MAX_LANE_COUNT] & DP_ENHANCED_FRAME_CAP)) {
		intel_dp->link_configuration[1] |= DP_LANE_COUNT_ENHANCED_FRAME_EN;
	}
}