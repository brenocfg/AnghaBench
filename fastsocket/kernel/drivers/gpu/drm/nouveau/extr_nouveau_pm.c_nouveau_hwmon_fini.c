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
struct nouveau_pm {TYPE_1__* hwmon; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwmon_default_attrgroup ; 
 int /*<<< orphan*/  hwmon_device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  hwmon_fan_rpm_attrgroup ; 
 int /*<<< orphan*/  hwmon_pwm_fan_attrgroup ; 
 int /*<<< orphan*/  hwmon_temp_attrgroup ; 
 struct nouveau_pm* nouveau_pm (struct drm_device*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nouveau_hwmon_fini(struct drm_device *dev)
{
#if defined(CONFIG_HWMON) || (defined(MODULE) && defined(CONFIG_HWMON_MODULE))
	struct nouveau_pm *pm = nouveau_pm(dev);

	if (pm->hwmon) {
		sysfs_remove_group(&pm->hwmon->kobj, &hwmon_default_attrgroup);
		sysfs_remove_group(&pm->hwmon->kobj, &hwmon_temp_attrgroup);
		sysfs_remove_group(&pm->hwmon->kobj, &hwmon_pwm_fan_attrgroup);
		sysfs_remove_group(&pm->hwmon->kobj, &hwmon_fan_rpm_attrgroup);

		hwmon_device_unregister(pm->hwmon);
	}
#endif
}