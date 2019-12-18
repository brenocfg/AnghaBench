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
struct TYPE_2__ {int profile; } ;
struct radeon_device {TYPE_1__ pm; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PM_PROFILE_AUTO ; 
 int PM_PROFILE_HIGH ; 
 int PM_PROFILE_LOW ; 
 int PM_PROFILE_MID ; 
 struct drm_device* pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 

__attribute__((used)) static ssize_t radeon_get_pm_profile(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	struct drm_device *ddev = pci_get_drvdata(to_pci_dev(dev));
	struct radeon_device *rdev = ddev->dev_private;
	int cp = rdev->pm.profile;

	return snprintf(buf, PAGE_SIZE, "%s\n",
			(cp == PM_PROFILE_AUTO) ? "auto" :
			(cp == PM_PROFILE_LOW) ? "low" :
			(cp == PM_PROFILE_MID) ? "mid" :
			(cp == PM_PROFILE_HIGH) ? "high" : "default");
}