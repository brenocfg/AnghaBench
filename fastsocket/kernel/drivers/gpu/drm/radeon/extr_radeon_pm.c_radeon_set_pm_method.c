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
struct TYPE_2__ {int /*<<< orphan*/  dynpm_idle_work; int /*<<< orphan*/  mutex; int /*<<< orphan*/  pm_method; int /*<<< orphan*/  dynpm_planned_action; int /*<<< orphan*/  dynpm_state; } ;
struct radeon_device {TYPE_1__ pm; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DYNPM_ACTION_DEFAULT ; 
 int /*<<< orphan*/  DYNPM_ACTION_NONE ; 
 int /*<<< orphan*/  DYNPM_STATE_DISABLED ; 
 int /*<<< orphan*/  DYNPM_STATE_PAUSED ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  PM_METHOD_DYNPM ; 
 int /*<<< orphan*/  PM_METHOD_PROFILE ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_device* pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_pm_compute_clocks (struct radeon_device*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 

__attribute__((used)) static ssize_t radeon_set_pm_method(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf,
				    size_t count)
{
	struct drm_device *ddev = pci_get_drvdata(to_pci_dev(dev));
	struct radeon_device *rdev = ddev->dev_private;


	if (strncmp("dynpm", buf, strlen("dynpm")) == 0) {
		mutex_lock(&rdev->pm.mutex);
		rdev->pm.pm_method = PM_METHOD_DYNPM;
		rdev->pm.dynpm_state = DYNPM_STATE_PAUSED;
		rdev->pm.dynpm_planned_action = DYNPM_ACTION_DEFAULT;
		mutex_unlock(&rdev->pm.mutex);
	} else if (strncmp("profile", buf, strlen("profile")) == 0) {
		mutex_lock(&rdev->pm.mutex);
		/* disable dynpm */
		rdev->pm.dynpm_state = DYNPM_STATE_DISABLED;
		rdev->pm.dynpm_planned_action = DYNPM_ACTION_NONE;
		rdev->pm.pm_method = PM_METHOD_PROFILE;
		mutex_unlock(&rdev->pm.mutex);
		cancel_delayed_work_sync(&rdev->pm.dynpm_idle_work);
	} else {
		count = -EINVAL;
		goto fail;
	}
	radeon_pm_compute_clocks(rdev);
fail:
	return count;
}