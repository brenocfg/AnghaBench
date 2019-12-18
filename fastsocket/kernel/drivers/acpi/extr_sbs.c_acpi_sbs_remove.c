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
struct acpi_sbs {int /*<<< orphan*/  lock; int /*<<< orphan*/  hc; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_SBS_BAT ; 
 int /*<<< orphan*/  acpi_battery_remove (struct acpi_sbs*,int) ; 
 int /*<<< orphan*/  acpi_charger_remove (struct acpi_sbs*) ; 
 struct acpi_sbs* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_smbus_unregister_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct acpi_sbs*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_sbs_remove(struct acpi_device *device, int type)
{
	struct acpi_sbs *sbs;
	int id;

	if (!device)
		return -EINVAL;
	sbs = acpi_driver_data(device);
	if (!sbs)
		return -EINVAL;
	mutex_lock(&sbs->lock);
	acpi_smbus_unregister_callback(sbs->hc);
	for (id = 0; id < MAX_SBS_BAT; ++id)
		acpi_battery_remove(sbs, id);
	acpi_charger_remove(sbs);
	mutex_unlock(&sbs->lock);
	mutex_destroy(&sbs->lock);
	kfree(sbs);
	return 0;
}