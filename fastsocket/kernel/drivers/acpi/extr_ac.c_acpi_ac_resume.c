#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct acpi_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct acpi_ac {unsigned int state; TYPE_2__ charger; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 scalar_t__ acpi_ac_get_state (struct acpi_ac*) ; 
 struct acpi_ac* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_ac_resume(struct acpi_device *device)
{
	struct acpi_ac *ac;
	unsigned old_state;
	if (!device || !acpi_driver_data(device))
		return -EINVAL;
	ac = acpi_driver_data(device);
	old_state = ac->state;
	if (acpi_ac_get_state(ac))
		return 0;
#ifdef CONFIG_ACPI_SYSFS_POWER
	if (old_state != ac->state)
		kobject_uevent(&ac->charger.dev->kobj, KOBJ_CHANGE);
#endif
	return 0;
}