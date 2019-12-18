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
struct TYPE_2__ {scalar_t__ dev; } ;
struct acpi_sbs {scalar_t__ charger_entry; TYPE_1__ charger; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_ac_dir ; 
 int /*<<< orphan*/  acpi_sbs_remove_fs (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_supply_unregister (TYPE_1__*) ; 

__attribute__((used)) static void acpi_charger_remove(struct acpi_sbs *sbs)
{
#ifdef CONFIG_ACPI_SYSFS_POWER
	if (sbs->charger.dev)
		power_supply_unregister(&sbs->charger);
#endif
#ifdef CONFIG_ACPI_PROCFS_POWER
	if (sbs->charger_entry)
		acpi_sbs_remove_fs(&sbs->charger_entry, acpi_ac_dir);
#endif
}