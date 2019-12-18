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

/* Variables and functions */
 int /*<<< orphan*/ * acpi_ac_dir ; 
 int /*<<< orphan*/ * acpi_battery_dir ; 
 int /*<<< orphan*/  acpi_unlock_ac_dir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_unlock_battery_dir (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_sbs_rmdirs(void)
{
#ifdef CONFIG_ACPI_PROCFS_POWER
	if (acpi_ac_dir) {
		acpi_unlock_ac_dir(acpi_ac_dir);
		acpi_ac_dir = NULL;
	}
	if (acpi_battery_dir) {
		acpi_unlock_battery_dir(acpi_battery_dir);
		acpi_battery_dir = NULL;
	}
#endif
}