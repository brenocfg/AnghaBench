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
struct acpi_thermal {int /*<<< orphan*/  lock; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct acpi_thermal* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_thermal_remove_fs (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_thermal_unregister_thermal_zone (struct acpi_thermal*) ; 
 int /*<<< orphan*/  kfree (struct acpi_thermal*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_thermal_remove(struct acpi_device *device, int type)
{
	struct acpi_thermal *tz = NULL;

	if (!device || !acpi_driver_data(device))
		return -EINVAL;

	tz = acpi_driver_data(device);

	acpi_thermal_remove_fs(device);
	acpi_thermal_unregister_thermal_zone(tz);
	mutex_destroy(&tz->lock);
	kfree(tz);
	return 0;
}