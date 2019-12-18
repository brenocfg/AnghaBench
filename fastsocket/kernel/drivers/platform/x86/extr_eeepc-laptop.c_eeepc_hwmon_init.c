#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct device*) ; 
 int PTR_ERR (struct device*) ; 
 struct device* eeepc_hwmon_device ; 
 int /*<<< orphan*/  eeepc_hwmon_exit () ; 
 int /*<<< orphan*/  hwmon_attribute_group ; 
 struct device* hwmon_device_register (struct device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int eeepc_hwmon_init(struct device *dev)
{
	struct device *hwmon;
	int result;

	hwmon = hwmon_device_register(dev);
	if (IS_ERR(hwmon)) {
		pr_err("Could not register eeepc hwmon device\n");
		eeepc_hwmon_device = NULL;
		return PTR_ERR(hwmon);
	}
	eeepc_hwmon_device = hwmon;
	result = sysfs_create_group(&hwmon->kobj,
				    &hwmon_attribute_group);
	if (result)
		eeepc_hwmon_exit();
	return result;
}