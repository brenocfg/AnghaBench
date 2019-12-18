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
struct TYPE_6__ {int dynpm_can_upclock; int dynpm_can_downclock; int num_power_states; int dynpm_planned_action; int requested_power_state_index; size_t requested_clock_mode_index; int current_power_state_index; int active_crtc_count; int default_power_state_index; size_t current_clock_mode_index; TYPE_2__* power_state; } ;
struct radeon_device {int flags; scalar_t__ family; TYPE_3__ pm; } ;
struct TYPE_5__ {int flags; scalar_t__ type; int /*<<< orphan*/  pcie_lanes; TYPE_1__* clock_info; int /*<<< orphan*/  num_clock_modes; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  mclk; int /*<<< orphan*/  sclk; } ;

/* Variables and functions */
 scalar_t__ CHIP_R600 ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
#define  DYNPM_ACTION_DEFAULT 132 
#define  DYNPM_ACTION_DOWNCLOCK 131 
#define  DYNPM_ACTION_MINIMUM 130 
#define  DYNPM_ACTION_NONE 129 
#define  DYNPM_ACTION_UPCLOCK 128 
 scalar_t__ POWER_STATE_TYPE_BATTERY ; 
 scalar_t__ POWER_STATE_TYPE_PERFORMANCE ; 
 int RADEON_IS_IGP ; 
 int RADEON_PM_MODE_NO_DISPLAY ; 
 int RADEON_PM_STATE_SINGLE_DISPLAY_ONLY ; 

void r600_pm_get_dynpm_state(struct radeon_device *rdev)
{
	int i;

	rdev->pm.dynpm_can_upclock = true;
	rdev->pm.dynpm_can_downclock = true;

	/* power state array is low to high, default is first */
	if ((rdev->flags & RADEON_IS_IGP) || (rdev->family == CHIP_R600)) {
		int min_power_state_index = 0;

		if (rdev->pm.num_power_states > 2)
			min_power_state_index = 1;

		switch (rdev->pm.dynpm_planned_action) {
		case DYNPM_ACTION_MINIMUM:
			rdev->pm.requested_power_state_index = min_power_state_index;
			rdev->pm.requested_clock_mode_index = 0;
			rdev->pm.dynpm_can_downclock = false;
			break;
		case DYNPM_ACTION_DOWNCLOCK:
			if (rdev->pm.current_power_state_index == min_power_state_index) {
				rdev->pm.requested_power_state_index = rdev->pm.current_power_state_index;
				rdev->pm.dynpm_can_downclock = false;
			} else {
				if (rdev->pm.active_crtc_count > 1) {
					for (i = 0; i < rdev->pm.num_power_states; i++) {
						if (rdev->pm.power_state[i].flags & RADEON_PM_STATE_SINGLE_DISPLAY_ONLY)
							continue;
						else if (i >= rdev->pm.current_power_state_index) {
							rdev->pm.requested_power_state_index =
								rdev->pm.current_power_state_index;
							break;
						} else {
							rdev->pm.requested_power_state_index = i;
							break;
						}
					}
				} else {
					if (rdev->pm.current_power_state_index == 0)
						rdev->pm.requested_power_state_index =
							rdev->pm.num_power_states - 1;
					else
						rdev->pm.requested_power_state_index =
							rdev->pm.current_power_state_index - 1;
				}
			}
			rdev->pm.requested_clock_mode_index = 0;
			/* don't use the power state if crtcs are active and no display flag is set */
			if ((rdev->pm.active_crtc_count > 0) &&
			    (rdev->pm.power_state[rdev->pm.requested_power_state_index].
			     clock_info[rdev->pm.requested_clock_mode_index].flags &
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
							rdev->pm.requested_power_state_index =
								rdev->pm.current_power_state_index;
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
			rdev->pm.requested_clock_mode_index = 0;
			break;
		case DYNPM_ACTION_DEFAULT:
			rdev->pm.requested_power_state_index = rdev->pm.default_power_state_index;
			rdev->pm.requested_clock_mode_index = 0;
			rdev->pm.dynpm_can_upclock = false;
			break;
		case DYNPM_ACTION_NONE:
		default:
			DRM_ERROR("Requested mode for not defined action\n");
			return;
		}
	} else {
		/* XXX select a power state based on AC/DC, single/dualhead, etc. */
		/* for now just select the first power state and switch between clock modes */
		/* power state array is low to high, default is first (0) */
		if (rdev->pm.active_crtc_count > 1) {
			rdev->pm.requested_power_state_index = -1;
			/* start at 1 as we don't want the default mode */
			for (i = 1; i < rdev->pm.num_power_states; i++) {
				if (rdev->pm.power_state[i].flags & RADEON_PM_STATE_SINGLE_DISPLAY_ONLY)
					continue;
				else if ((rdev->pm.power_state[i].type == POWER_STATE_TYPE_PERFORMANCE) ||
					 (rdev->pm.power_state[i].type == POWER_STATE_TYPE_BATTERY)) {
					rdev->pm.requested_power_state_index = i;
					break;
				}
			}
			/* if nothing selected, grab the default state. */
			if (rdev->pm.requested_power_state_index == -1)
				rdev->pm.requested_power_state_index = 0;
		} else
			rdev->pm.requested_power_state_index = 1;

		switch (rdev->pm.dynpm_planned_action) {
		case DYNPM_ACTION_MINIMUM:
			rdev->pm.requested_clock_mode_index = 0;
			rdev->pm.dynpm_can_downclock = false;
			break;
		case DYNPM_ACTION_DOWNCLOCK:
			if (rdev->pm.requested_power_state_index == rdev->pm.current_power_state_index) {
				if (rdev->pm.current_clock_mode_index == 0) {
					rdev->pm.requested_clock_mode_index = 0;
					rdev->pm.dynpm_can_downclock = false;
				} else
					rdev->pm.requested_clock_mode_index =
						rdev->pm.current_clock_mode_index - 1;
			} else {
				rdev->pm.requested_clock_mode_index = 0;
				rdev->pm.dynpm_can_downclock = false;
			}
			/* don't use the power state if crtcs are active and no display flag is set */
			if ((rdev->pm.active_crtc_count > 0) &&
			    (rdev->pm.power_state[rdev->pm.requested_power_state_index].
			     clock_info[rdev->pm.requested_clock_mode_index].flags &
			     RADEON_PM_MODE_NO_DISPLAY)) {
				rdev->pm.requested_clock_mode_index++;
			}
			break;
		case DYNPM_ACTION_UPCLOCK:
			if (rdev->pm.requested_power_state_index == rdev->pm.current_power_state_index) {
				if (rdev->pm.current_clock_mode_index ==
				    (rdev->pm.power_state[rdev->pm.requested_power_state_index].num_clock_modes - 1)) {
					rdev->pm.requested_clock_mode_index = rdev->pm.current_clock_mode_index;
					rdev->pm.dynpm_can_upclock = false;
				} else
					rdev->pm.requested_clock_mode_index =
						rdev->pm.current_clock_mode_index + 1;
			} else {
				rdev->pm.requested_clock_mode_index =
					rdev->pm.power_state[rdev->pm.requested_power_state_index].num_clock_modes - 1;
				rdev->pm.dynpm_can_upclock = false;
			}
			break;
		case DYNPM_ACTION_DEFAULT:
			rdev->pm.requested_power_state_index = rdev->pm.default_power_state_index;
			rdev->pm.requested_clock_mode_index = 0;
			rdev->pm.dynpm_can_upclock = false;
			break;
		case DYNPM_ACTION_NONE:
		default:
			DRM_ERROR("Requested mode for not defined action\n");
			return;
		}
	}

	DRM_DEBUG_DRIVER("Requested: e: %d m: %d p: %d\n",
		  rdev->pm.power_state[rdev->pm.requested_power_state_index].
		  clock_info[rdev->pm.requested_clock_mode_index].sclk,
		  rdev->pm.power_state[rdev->pm.requested_power_state_index].
		  clock_info[rdev->pm.requested_clock_mode_index].mclk,
		  rdev->pm.power_state[rdev->pm.requested_power_state_index].
		  pcie_lanes);
}