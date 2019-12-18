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
struct acpi_power_meter_resource {int /*<<< orphan*/  hwmon_dev; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct acpi_power_meter_resource* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  free_capabilities (struct acpi_power_meter_resource*) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct acpi_power_meter_resource*) ; 
 int /*<<< orphan*/  remove_attrs (struct acpi_power_meter_resource*) ; 

__attribute__((used)) static int acpi_power_meter_remove(struct acpi_device *device, int type)
{
	struct acpi_power_meter_resource *resource;

	if (!device || !acpi_driver_data(device))
		return -EINVAL;

	resource = acpi_driver_data(device);
	hwmon_device_unregister(resource->hwmon_dev);

	free_capabilities(resource);
	remove_attrs(resource);

	kfree(resource);
	return 0;
}