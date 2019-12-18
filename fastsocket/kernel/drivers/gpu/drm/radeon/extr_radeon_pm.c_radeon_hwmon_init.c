#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int int_thermal_type; TYPE_2__* int_hwmon_dev; } ;
struct radeon_device {int /*<<< orphan*/  dev; TYPE_1__ pm; int /*<<< orphan*/  ddev; int /*<<< orphan*/  family; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_ARUBA ; 
 int /*<<< orphan*/  IS_ERR (TYPE_2__*) ; 
 int PTR_ERR (TYPE_2__*) ; 
#define  THERMAL_TYPE_EVERGREEN 133 
#define  THERMAL_TYPE_NI 132 
#define  THERMAL_TYPE_RV6XX 131 
#define  THERMAL_TYPE_RV770 130 
#define  THERMAL_TYPE_SI 129 
#define  THERMAL_TYPE_SUMO 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_attrgroup ; 
 TYPE_2__* hwmon_device_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int radeon_hwmon_init(struct radeon_device *rdev)
{
	int err = 0;

	rdev->pm.int_hwmon_dev = NULL;

	switch (rdev->pm.int_thermal_type) {
	case THERMAL_TYPE_RV6XX:
	case THERMAL_TYPE_RV770:
	case THERMAL_TYPE_EVERGREEN:
	case THERMAL_TYPE_NI:
	case THERMAL_TYPE_SUMO:
	case THERMAL_TYPE_SI:
		/* No support for TN yet */
		if (rdev->family == CHIP_ARUBA)
			return err;
		rdev->pm.int_hwmon_dev = hwmon_device_register(rdev->dev);
		if (IS_ERR(rdev->pm.int_hwmon_dev)) {
			err = PTR_ERR(rdev->pm.int_hwmon_dev);
			dev_err(rdev->dev,
				"Unable to register hwmon device: %d\n", err);
			break;
		}
		dev_set_drvdata(rdev->pm.int_hwmon_dev, rdev->ddev);
		err = sysfs_create_group(&rdev->pm.int_hwmon_dev->kobj,
					 &hwmon_attrgroup);
		if (err) {
			dev_err(rdev->dev,
				"Unable to create hwmon sysfs file: %d\n", err);
			hwmon_device_unregister(rdev->dev);
		}
		break;
	default:
		break;
	}

	return err;
}