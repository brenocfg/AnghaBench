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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct acpi_eject_event {int /*<<< orphan*/  event; int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {scalar_t__ eject_pending; int /*<<< orphan*/  ejectable; } ;
struct acpi_device {TYPE_1__ flags; int /*<<< orphan*/  handle; int /*<<< orphan*/ * driver; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_object_type ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_NOTIFY_EJECT_REQUEST ; 
 int /*<<< orphan*/  ACPI_OST_EC_OSPM_EJECT ; 
 int /*<<< orphan*/  ACPI_OST_SC_EJECT_IN_PROGRESS ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  acpi_bus_hot_remove_device ; 
 int /*<<< orphan*/  acpi_evaluate_hotplug_ost (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_get_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_os_hotplug_execute (int /*<<< orphan*/ ,void*) ; 
 struct acpi_eject_event* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct acpi_device* to_acpi_device (struct device*) ; 

__attribute__((used)) static ssize_t
acpi_eject_store(struct device *d, struct device_attribute *attr,
		const char *buf, size_t count)
{
	int ret = count;
	acpi_status status;
	acpi_object_type type = 0;
	struct acpi_device *acpi_device = to_acpi_device(d);
	struct acpi_eject_event *ej_event;

	if ((!count) || (buf[0] != '1')) {
		return -EINVAL;
	}
#ifndef FORCE_EJECT
	if (acpi_device->driver == NULL) {
		ret = -ENODEV;
		goto err;
	}
#endif
	status = acpi_get_type(acpi_device->handle, &type);
	if (ACPI_FAILURE(status) || (!acpi_device->flags.ejectable)) {
		ret = -ENODEV;
		goto err;
	}

	ej_event = kmalloc(sizeof(*ej_event), GFP_KERNEL);
	if (!ej_event) {
		ret = -ENOMEM;
		goto err;
	}

	ej_event->handle = acpi_device->handle;
	if (acpi_device->flags.eject_pending) {
		/* event originated from ACPI eject notification */
		ej_event->event = ACPI_NOTIFY_EJECT_REQUEST;
		acpi_device->flags.eject_pending = 0;
	} else {
		/* event originated from user */
		ej_event->event = ACPI_OST_EC_OSPM_EJECT;
		(void) acpi_evaluate_hotplug_ost(ej_event->handle,
			ej_event->event, ACPI_OST_SC_EJECT_IN_PROGRESS, NULL);
	}

	acpi_os_hotplug_execute(acpi_bus_hot_remove_device, (void *)ej_event);
err:
	return ret;
}