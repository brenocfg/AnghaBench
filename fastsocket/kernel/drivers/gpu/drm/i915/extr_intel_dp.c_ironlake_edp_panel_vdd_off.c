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
struct intel_dp {int want_panel_vdd; int panel_power_cycle_delay; int /*<<< orphan*/  panel_vdd_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  ironlake_panel_vdd_off_sync (struct intel_dp*) ; 
 int /*<<< orphan*/  is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ironlake_edp_panel_vdd_off(struct intel_dp *intel_dp, bool sync)
{
	if (!is_edp(intel_dp))
		return;

	DRM_DEBUG_KMS("Turn eDP VDD off %d\n", intel_dp->want_panel_vdd);
	WARN(!intel_dp->want_panel_vdd, "eDP VDD not forced on");

	intel_dp->want_panel_vdd = false;

	if (sync) {
		ironlake_panel_vdd_off_sync(intel_dp);
	} else {
		/*
		 * Queue the timer to fire a long
		 * time from now (relative to the power down delay)
		 * to keep the panel power up across a sequence of operations
		 */
		schedule_delayed_work(&intel_dp->panel_vdd_work,
				      msecs_to_jiffies(intel_dp->panel_power_cycle_delay * 5));
	}
}