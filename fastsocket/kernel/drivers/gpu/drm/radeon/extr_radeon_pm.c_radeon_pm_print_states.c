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
struct radeon_power_state {size_t type; int flags; int num_clock_modes; struct radeon_pm_clock_info* clock_info; int /*<<< orphan*/  pcie_lanes; } ;
struct TYPE_4__ {int /*<<< orphan*/  voltage; } ;
struct radeon_pm_clock_info {int sclk; int mclk; TYPE_2__ voltage; } ;
struct TYPE_3__ {int num_power_states; int default_power_state_index; struct radeon_power_state* power_state; } ;
struct radeon_device {int flags; TYPE_1__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,...) ; 
 int RADEON_IS_IGP ; 
 int RADEON_IS_PCIE ; 
 int RADEON_PM_STATE_SINGLE_DISPLAY_ONLY ; 
 int /*<<< orphan*/ * radeon_pm_state_type_name ; 

__attribute__((used)) static void radeon_pm_print_states(struct radeon_device *rdev)
{
	int i, j;
	struct radeon_power_state *power_state;
	struct radeon_pm_clock_info *clock_info;

	DRM_DEBUG_DRIVER("%d Power State(s)\n", rdev->pm.num_power_states);
	for (i = 0; i < rdev->pm.num_power_states; i++) {
		power_state = &rdev->pm.power_state[i];
		DRM_DEBUG_DRIVER("State %d: %s\n", i,
			radeon_pm_state_type_name[power_state->type]);
		if (i == rdev->pm.default_power_state_index)
			DRM_DEBUG_DRIVER("\tDefault");
		if ((rdev->flags & RADEON_IS_PCIE) && !(rdev->flags & RADEON_IS_IGP))
			DRM_DEBUG_DRIVER("\t%d PCIE Lanes\n", power_state->pcie_lanes);
		if (power_state->flags & RADEON_PM_STATE_SINGLE_DISPLAY_ONLY)
			DRM_DEBUG_DRIVER("\tSingle display only\n");
		DRM_DEBUG_DRIVER("\t%d Clock Mode(s)\n", power_state->num_clock_modes);
		for (j = 0; j < power_state->num_clock_modes; j++) {
			clock_info = &(power_state->clock_info[j]);
			if (rdev->flags & RADEON_IS_IGP)
				DRM_DEBUG_DRIVER("\t\t%d e: %d\n",
						 j,
						 clock_info->sclk * 10);
			else
				DRM_DEBUG_DRIVER("\t\t%d e: %d\tm: %d\tv: %d\n",
						 j,
						 clock_info->sclk * 10,
						 clock_info->mclk * 10,
						 clock_info->voltage.voltage);
		}
	}
}