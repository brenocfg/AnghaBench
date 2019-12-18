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
struct device {int dummy; } ;
struct atk_data {int /*<<< orphan*/  hwmon_dev; TYPE_1__* acpi_dev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int atk_create_files (struct atk_data*) ; 
 int /*<<< orphan*/  atk_remove_files (struct atk_data*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  hwmon_device_register (struct device*) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atk_register_hwmon(struct atk_data *data)
{
	struct device *dev = &data->acpi_dev->dev;
	int err;

	dev_dbg(dev, "registering hwmon device\n");
	data->hwmon_dev = hwmon_device_register(dev);
	if (IS_ERR(data->hwmon_dev))
		return PTR_ERR(data->hwmon_dev);

	dev_dbg(dev, "populating sysfs directory\n");
	err = atk_create_files(data);
	if (err)
		goto remove;

	return 0;
remove:
	/* Cleanup the registered files */
	atk_remove_files(data);
	hwmon_device_unregister(data->hwmon_dev);
	return err;
}