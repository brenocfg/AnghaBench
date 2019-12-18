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
struct atk_data {scalar_t__ disable_ec; int /*<<< orphan*/  hwmon_dev; } ;
struct acpi_device {int /*<<< orphan*/  dev; struct atk_data* driver_data; } ;

/* Variables and functions */
 scalar_t__ atk_ec_ctl (struct atk_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atk_free_sensors (struct atk_data*) ; 
 int /*<<< orphan*/  atk_remove_files (struct atk_data*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct atk_data*) ; 

__attribute__((used)) static int atk_remove(struct acpi_device *device, int type)
{
	struct atk_data *data = device->driver_data;
	dev_dbg(&device->dev, "removing...\n");

	device->driver_data = NULL;

	atk_remove_files(data);
	atk_free_sensors(data);
	hwmon_device_unregister(data->hwmon_dev);

	if (data->disable_ec) {
		if (atk_ec_ctl(data, 0))
			dev_err(&device->dev, "Failed to disable EC\n");
	}

	kfree(data);

	return 0;
}