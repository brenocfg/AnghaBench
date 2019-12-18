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
struct TYPE_6__ {int default_power_state_index; TYPE_2__* power_state; TYPE_1__* profiles; } ;
struct radeon_device {int flags; TYPE_3__ pm; } ;
struct TYPE_5__ {scalar_t__ num_clock_modes; } ;
struct TYPE_4__ {int dpms_off_ps_idx; int dpms_on_ps_idx; scalar_t__ dpms_on_cm_idx; scalar_t__ dpms_off_cm_idx; } ;

/* Variables and functions */
 size_t PM_PROFILE_DEFAULT_IDX ; 
 size_t PM_PROFILE_HIGH_MH_IDX ; 
 size_t PM_PROFILE_HIGH_SH_IDX ; 
 size_t PM_PROFILE_LOW_MH_IDX ; 
 size_t PM_PROFILE_LOW_SH_IDX ; 
 size_t PM_PROFILE_MID_MH_IDX ; 
 size_t PM_PROFILE_MID_SH_IDX ; 
 int /*<<< orphan*/  POWER_STATE_TYPE_BATTERY ; 
 int /*<<< orphan*/  POWER_STATE_TYPE_PERFORMANCE ; 
 int RADEON_IS_MOBILITY ; 
 int radeon_pm_get_type_index (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sumo_pm_init_profile(struct radeon_device *rdev)
{
	int idx;

	/* default */
	rdev->pm.profiles[PM_PROFILE_DEFAULT_IDX].dpms_off_ps_idx = rdev->pm.default_power_state_index;
	rdev->pm.profiles[PM_PROFILE_DEFAULT_IDX].dpms_on_ps_idx = rdev->pm.default_power_state_index;
	rdev->pm.profiles[PM_PROFILE_DEFAULT_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROFILE_DEFAULT_IDX].dpms_on_cm_idx = 0;

	/* low,mid sh/mh */
	if (rdev->flags & RADEON_IS_MOBILITY)
		idx = radeon_pm_get_type_index(rdev, POWER_STATE_TYPE_BATTERY, 0);
	else
		idx = radeon_pm_get_type_index(rdev, POWER_STATE_TYPE_PERFORMANCE, 0);

	rdev->pm.profiles[PM_PROFILE_LOW_SH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_LOW_SH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_LOW_SH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROFILE_LOW_SH_IDX].dpms_on_cm_idx = 0;

	rdev->pm.profiles[PM_PROFILE_LOW_MH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_LOW_MH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_LOW_MH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROFILE_LOW_MH_IDX].dpms_on_cm_idx = 0;

	rdev->pm.profiles[PM_PROFILE_MID_SH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_MID_SH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_MID_SH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROFILE_MID_SH_IDX].dpms_on_cm_idx = 0;

	rdev->pm.profiles[PM_PROFILE_MID_MH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_MID_MH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_MID_MH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROFILE_MID_MH_IDX].dpms_on_cm_idx = 0;

	/* high sh/mh */
	idx = radeon_pm_get_type_index(rdev, POWER_STATE_TYPE_PERFORMANCE, 0);
	rdev->pm.profiles[PM_PROFILE_HIGH_SH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_HIGH_SH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_HIGH_SH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROFILE_HIGH_SH_IDX].dpms_on_cm_idx =
		rdev->pm.power_state[idx].num_clock_modes - 1;

	rdev->pm.profiles[PM_PROFILE_HIGH_MH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_HIGH_MH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_HIGH_MH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROFILE_HIGH_MH_IDX].dpms_on_cm_idx =
		rdev->pm.power_state[idx].num_clock_modes - 1;
}