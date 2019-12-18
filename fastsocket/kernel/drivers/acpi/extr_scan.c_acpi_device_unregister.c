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
struct acpi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  handle; int /*<<< orphan*/  wakeup_list; int /*<<< orphan*/  node; scalar_t__ parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_bus_data_handler ; 
 int /*<<< orphan*/  acpi_detach_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_device_lock ; 
 int /*<<< orphan*/  acpi_device_remove_files (struct acpi_device*) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_device_unregister(struct acpi_device *device, int type)
{
	mutex_lock(&acpi_device_lock);
	if (device->parent)
		list_del(&device->node);

	list_del(&device->wakeup_list);
	mutex_unlock(&acpi_device_lock);

	acpi_detach_data(device->handle, acpi_bus_data_handler);

	acpi_device_remove_files(device);
	device_unregister(&device->dev);
}