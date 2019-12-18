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
struct acpi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ dev; } ;
struct acpi_ac {TYPE_1__ charger; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  acpi_ac_remove_fs (struct acpi_device*) ; 
 struct acpi_ac* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  kfree (struct acpi_ac*) ; 
 int /*<<< orphan*/  power_supply_unregister (TYPE_1__*) ; 

__attribute__((used)) static int acpi_ac_remove(struct acpi_device *device, int type)
{
	struct acpi_ac *ac = NULL;


	if (!device || !acpi_driver_data(device))
		return -EINVAL;

	ac = acpi_driver_data(device);

#ifdef CONFIG_ACPI_SYSFS_POWER
	if (ac->charger.dev)
		power_supply_unregister(&ac->charger);
#endif
#ifdef CONFIG_ACPI_PROCFS_POWER
	acpi_ac_remove_fs(device);
#endif

	kfree(ac);

	return 0;
}