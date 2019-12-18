#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int dynpm_can_upclock; int dynpm_can_downclock; int dynpm_planned_action; int requested_power_state_index; int current_power_state_index; int active_crtc_count; int num_power_states; int default_power_state_index; size_t requested_clock_mode_index; TYPE_2__* power_state; } ;
struct radeon_device {TYPE_3__ pm; } ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  pcie_lanes; TYPE_1__* clock_info; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  mclk; int /*<<< orphan*/  sclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
#define  DYNPM_ACTION_DEFAULT 132 
#define  DYNPM_ACTION_DOWNCLOCK 131 
#define  DYNPM_ACTION_MINIMUM 130 
#define  DYNPM_ACTION_NONE 129 
#define  DYNPM_ACTION_UPCLOCK 128 
 int RADEON_PM_MODE_NO_DISPLAY ; 
 int RADEON_PM_STATE_SINGLE_DISPLAY_ONLY ; 

void r100_pm_get_dynpm_state(struct radeon_device *rdev)
{
	int i;
	rdev->pm.dynpm_can_upclock = true;
	rdev->pm.dynpm_can_downclock = true;

	switch (rdev->pm.dynpm_planned_action) {
	case DYNPM_ACTION_MINIMUM:
		rdev->pm.requested_power_state_index = 0;
		rdev->pm.dynpm_can_downclock = false;
		break;
	case DYNPM_ACTION_DOWNCLOCK:
		if (rdev->pm.current_power_state_index == 0) {
			rdev->pm.requested_power_state_index = rdev->pm.current_power_state_index;
			rdev->pm.dynpm_can_downclock = false;
		} else {
			if (rdev->pm.active_crtc_count > 1) {
				for (i = 0; i < rdev->pm.num_power_states; i++) {
					if (rdev->pm.power_state[i].flags & RADEON_PM_STATE_SINGLE_DISPLAY_ONLY)
						continue;
					else if (i >= rdev->pm.current_power_state_index) {
						rdev->pm.requested_power_state_index = rdev->pm.current_power_state_index;
						break;
					} else {
						rdev->pm.requested_power_state_index = i;
						break;
					}
				}
			} else
				rdev->pm.requested_power_state_index =
					rdev->pm.current_power_state_index - 1;
		}
		/* don't use the power state if crtcs are active and no display flag is set */
		if ((rdev->pm.active_crtc_count > 0) &&
		    (rdev->pm.power_state[rdev->pm.requested_power_state_index].clock_info[0].flags &
		     RADEON_PM_MODE_NO_DISPLAY)) {
			rdev->pm.requested_power_state_index++;
		}
		break;
	case DYNPM_ACTION_UPCLOCK:
		if (rdev->pm.current_power_state_index == (rdev->pm.num_power_states - 1)) {
			rdev->pm.requested_power_state_index = rdev->pm.current_power_state_index;
			rdev->pm.dynpm_can_upclock = false;
		} else {
			if (rdev->pm.active_crtc_count > 1) {
				for (i = (rdev->pm.num_power_states - 1); i >= 0; i--) {
					if (rdev->pm.power_state[i].flags & RADEON_PM_STATE_SINGLE_DISPLAY_ONLY)
						continue;
					else if (i <= rdev->pm.current_power_state_index) {
						rdev->pm.requested_power_state_index = rdev->pm.current_power_state_index;
						break;
					} else {
						rdev->pm.requested_power_state_index = i;
						break;
					}
				}
			} else
				rdev->pm.requested_power_state_index =
					rdev->pm.current_power_state_index + 1;
		}
		break;
	case DYNPM_ACTION_DEFAULT:
		rdev->pm.requested_power_state_index = rdev->pm.default_power_state_index;
		rdev->pm.dynpm_can_upclock = false;
		break;
	case DYNPM_ACTION_NONE:
	default:
		DRM_ERROR("Requested mode for not defined action\n");
		return;
	}
	/* only one clock mode per power state */
	rdev->pm.requested_clock_mode_index = 0;

	DRM_DEBUG_DRIVER("Requested: e: %d m: %d p: %d\n",
		  rdev->pm.power_state[rdev->pm.requested_power_state_index].
		  clock_info[rdev->pm.requested_clock_mode_index].sclk,
		  rdev->pm.power_state[rdev->pm.requested_power_state_index].
		  clock_info[rdev->pm.requested_clock_mode_index].mclk,
		  rdev->pm.power_state[rdev->pm.requested_power_state_index].
		  pcie_lanes);
}