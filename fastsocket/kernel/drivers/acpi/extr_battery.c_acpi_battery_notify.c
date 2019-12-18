#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int /*<<< orphan*/  device_class; } ;
struct acpi_device {int /*<<< orphan*/  dev; TYPE_1__ pnp; } ;
struct TYPE_6__ {TYPE_2__* dev; } ;
struct acpi_battery {TYPE_3__ bat; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 scalar_t__ ACPI_BATTERY_NOTIFY_INFO ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  acpi_battery_present (struct acpi_battery*) ; 
 int /*<<< orphan*/  acpi_battery_update (struct acpi_battery*,int) ; 
 int /*<<< orphan*/  acpi_bus_generate_netlink_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_bus_generate_proc_event (struct acpi_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct acpi_battery* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acpi_battery_notify(struct acpi_device *device, u32 event)
{
	struct acpi_battery *battery = acpi_driver_data(device);

	if (!battery)
		return;
	acpi_battery_update(battery, ((event == ACPI_BATTERY_NOTIFY_INFO) ? true
				      : false));
	acpi_bus_generate_proc_event(device, event,
				     acpi_battery_present(battery));
	acpi_bus_generate_netlink_event(device->pnp.device_class,
					dev_name(&device->dev), event,
					acpi_battery_present(battery));
#ifdef CONFIG_ACPI_SYSFS_POWER
	/* acpi_batter_update could remove power_supply object */
	if (battery->bat.dev)
		kobject_uevent(&battery->bat.dev->kobj, KOBJ_CHANGE);
#endif
}