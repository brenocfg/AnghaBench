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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct acpi_battery {int power_unit; TYPE_1__ bat; scalar_t__ update_time; } ;

/* Variables and functions */
 int acpi_battery_get_info (struct acpi_battery*) ; 
 int acpi_battery_get_state (struct acpi_battery*) ; 
 int acpi_battery_get_status (struct acpi_battery*) ; 
 int /*<<< orphan*/  acpi_battery_init_alarm (struct acpi_battery*) ; 
 int acpi_battery_present (struct acpi_battery*) ; 
 int /*<<< orphan*/  acpi_battery_quirks (struct acpi_battery*) ; 
 int /*<<< orphan*/  sysfs_add_battery (struct acpi_battery*) ; 
 int /*<<< orphan*/  sysfs_remove_battery (struct acpi_battery*) ; 

__attribute__((used)) static int acpi_battery_update(struct acpi_battery *battery, bool get_info)
{
	int result, old_present = acpi_battery_present(battery);
#ifdef CONFIG_ACPI_SYSFS_POWER
	int old_power_unit = battery->power_unit;
#endif
	result = acpi_battery_get_status(battery);
	if (result)
		return result;
#ifdef CONFIG_ACPI_SYSFS_POWER
	if (!acpi_battery_present(battery)) {
		sysfs_remove_battery(battery);
		battery->update_time = 0;
		return 0;
	}
#endif
	if (!battery->update_time ||
	    old_present != acpi_battery_present(battery)) {
		result = acpi_battery_get_info(battery);
		if (result)
			return result;
		acpi_battery_quirks(battery);
		acpi_battery_init_alarm(battery);
	}
#ifdef CONFIG_ACPI_SYSFS_POWER
	if (!battery->bat.dev)
		sysfs_add_battery(battery);
#endif
	if (get_info) {
		acpi_battery_get_info(battery);
#ifdef CONFIG_ACPI_SYSFS_POWER
		if (old_power_unit != battery->power_unit) {
			/* The battery has changed its reporting units */
			sysfs_remove_battery(battery);
			sysfs_add_battery(battery);
		}
#endif
	}
	return acpi_battery_get_state(battery);
}