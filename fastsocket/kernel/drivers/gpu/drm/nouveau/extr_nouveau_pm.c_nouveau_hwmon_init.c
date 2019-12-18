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
struct nouveau_therm {scalar_t__ (* temp_get ) (struct nouveau_therm*) ;scalar_t__ (* fan_get ) (struct nouveau_therm*) ;scalar_t__ (* fan_sense ) (struct nouveau_therm*) ;int /*<<< orphan*/  attr_set; int /*<<< orphan*/  attr_get; } ;
struct nouveau_pm {struct device* hwmon; } ;
struct nouveau_drm {int /*<<< orphan*/  device; } ;
struct drm_device {TYPE_1__* pdev; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*,int) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct drm_device*) ; 
 int /*<<< orphan*/  hwmon_default_attrgroup ; 
 struct device* hwmon_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_device_unregister (struct device*) ; 
 int /*<<< orphan*/  hwmon_fan_rpm_attrgroup ; 
 int /*<<< orphan*/  hwmon_pwm_fan_attrgroup ; 
 int /*<<< orphan*/  hwmon_temp_attrgroup ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 struct nouveau_pm* nouveau_pm (struct drm_device*) ; 
 struct nouveau_therm* nouveau_therm (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct nouveau_therm*) ; 
 scalar_t__ stub2 (struct nouveau_therm*) ; 
 scalar_t__ stub3 (struct nouveau_therm*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nouveau_hwmon_init(struct drm_device *dev)
{
	struct nouveau_pm *pm = nouveau_pm(dev);

#if defined(CONFIG_HWMON) || (defined(MODULE) && defined(CONFIG_HWMON_MODULE))
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_therm *therm = nouveau_therm(drm->device);
	struct device *hwmon_dev;
	int ret = 0;

	if (!therm || !therm->temp_get || !therm->attr_get || !therm->attr_set)
		return -ENODEV;

	hwmon_dev = hwmon_device_register(&dev->pdev->dev);
	if (IS_ERR(hwmon_dev)) {
		ret = PTR_ERR(hwmon_dev);
		NV_ERROR(drm, "Unable to register hwmon device: %d\n", ret);
		return ret;
	}
	dev_set_drvdata(hwmon_dev, dev);

	/* set the default attributes */
	ret = sysfs_create_group(&hwmon_dev->kobj, &hwmon_default_attrgroup);
	if (ret) {
		if (ret)
			goto error;
	}

	/* if the card has a working thermal sensor */
	if (therm->temp_get(therm) >= 0) {
		ret = sysfs_create_group(&hwmon_dev->kobj, &hwmon_temp_attrgroup);
		if (ret) {
			if (ret)
				goto error;
		}
	}

	/* if the card has a pwm fan */
	/*XXX: incorrect, need better detection for this, some boards have
	 *     the gpio entries for pwm fan control even when there's no
	 *     actual fan connected to it... therm table? */
	if (therm->fan_get && therm->fan_get(therm) >= 0) {
		ret = sysfs_create_group(&hwmon_dev->kobj,
					 &hwmon_pwm_fan_attrgroup);
		if (ret)
			goto error;
	}

	/* if the card can read the fan rpm */
	if (therm->fan_sense(therm) >= 0) {
		ret = sysfs_create_group(&hwmon_dev->kobj,
					 &hwmon_fan_rpm_attrgroup);
		if (ret)
			goto error;
	}

	pm->hwmon = hwmon_dev;

	return 0;

error:
	NV_ERROR(drm, "Unable to create some hwmon sysfs files: %d\n", ret);
	hwmon_device_unregister(hwmon_dev);
	pm->hwmon = NULL;
	return ret;
#else
	pm->hwmon = NULL;
	return 0;
#endif
}