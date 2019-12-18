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
struct acpi_sbs {struct acpi_battery* battery; } ;
struct TYPE_2__ {scalar_t__ dev; } ;
struct acpi_battery {scalar_t__ proc_entry; TYPE_1__ bat; scalar_t__ have_sysfs_alarm; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_battery_dir ; 
 int /*<<< orphan*/  acpi_sbs_remove_fs (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alarm_attr ; 
 int /*<<< orphan*/  device_remove_file (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  power_supply_unregister (TYPE_1__*) ; 

__attribute__((used)) static void acpi_battery_remove(struct acpi_sbs *sbs, int id)
{
	struct acpi_battery *battery = &sbs->battery[id];
#ifdef CONFIG_ACPI_SYSFS_POWER
	if (battery->bat.dev) {
		if (battery->have_sysfs_alarm)
			device_remove_file(battery->bat.dev, &alarm_attr);
		power_supply_unregister(&battery->bat);
	}
#endif
#ifdef CONFIG_ACPI_PROCFS_POWER
	if (battery->proc_entry)
		acpi_sbs_remove_fs(&battery->proc_entry, acpi_battery_dir);
#endif
}