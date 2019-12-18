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
typedef  int u32 ;
struct acpi_processor {int performance_platform_limit; } ;
struct TYPE_2__ {int /*<<< orphan*/  device_class; } ;
struct acpi_device {int /*<<< orphan*/  dev; TYPE_1__ pnp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
#define  ACPI_PROCESSOR_NOTIFY_PERFORMANCE 130 
#define  ACPI_PROCESSOR_NOTIFY_POWER 129 
#define  ACPI_PROCESSOR_NOTIFY_THROTTLING 128 
 int /*<<< orphan*/  acpi_bus_generate_netlink_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  acpi_bus_generate_proc_event (struct acpi_device*,int,int) ; 
 struct acpi_processor* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_processor_cst_has_changed (struct acpi_processor*) ; 
 int /*<<< orphan*/  acpi_processor_ppc_has_changed (struct acpi_processor*) ; 
 int /*<<< orphan*/  acpi_processor_tstate_has_changed (struct acpi_processor*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_processor_notify(struct acpi_device *device, u32 event)
{
	struct acpi_processor *pr = acpi_driver_data(device);
	int saved;

	if (!pr)
		return;

	switch (event) {
	case ACPI_PROCESSOR_NOTIFY_PERFORMANCE:
		saved = pr->performance_platform_limit;
		acpi_processor_ppc_has_changed(pr);
		if (saved == pr->performance_platform_limit)
			break;
		acpi_bus_generate_proc_event(device, event,
					pr->performance_platform_limit);
		acpi_bus_generate_netlink_event(device->pnp.device_class,
						  dev_name(&device->dev), event,
						  pr->performance_platform_limit);
		break;
	case ACPI_PROCESSOR_NOTIFY_POWER:
		acpi_processor_cst_has_changed(pr);
		acpi_bus_generate_proc_event(device, event, 0);
		acpi_bus_generate_netlink_event(device->pnp.device_class,
						  dev_name(&device->dev), event, 0);
		break;
	case ACPI_PROCESSOR_NOTIFY_THROTTLING:
		acpi_processor_tstate_has_changed(pr);
		acpi_bus_generate_proc_event(device, event, 0);
		acpi_bus_generate_netlink_event(device->pnp.device_class,
						  dev_name(&device->dev), event, 0);
	default:
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "Unsupported event [0x%x]\n", event));
		break;
	}

	return;
}