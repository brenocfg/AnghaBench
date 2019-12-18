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
struct acpi_device {int dummy; } ;
struct acpi_battery {scalar_t__ update_time; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  acpi_battery_update (struct acpi_battery*,int) ; 
 struct acpi_battery* acpi_driver_data (struct acpi_device*) ; 

__attribute__((used)) static int acpi_battery_resume(struct acpi_device *device)
{
	struct acpi_battery *battery;
	if (!device)
		return -EINVAL;
	battery = acpi_driver_data(device);
	battery->update_time = 0;
	acpi_battery_update(battery, true);
	return 0;
}