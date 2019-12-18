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
struct TYPE_2__ {scalar_t__ pm_method; scalar_t__ profile; int /*<<< orphan*/  mutex; } ;
struct radeon_device {TYPE_1__ pm; } ;

/* Variables and functions */
 scalar_t__ PM_METHOD_PROFILE ; 
 scalar_t__ PM_PROFILE_AUTO ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_pm_set_clocks (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_pm_update_profile (struct radeon_device*) ; 

void radeon_pm_acpi_event_handler(struct radeon_device *rdev)
{
	if (rdev->pm.pm_method == PM_METHOD_PROFILE) {
		if (rdev->pm.profile == PM_PROFILE_AUTO) {
			mutex_lock(&rdev->pm.mutex);
			radeon_pm_update_profile(rdev);
			radeon_pm_set_clocks(rdev);
			mutex_unlock(&rdev->pm.mutex);
		}
	}
}