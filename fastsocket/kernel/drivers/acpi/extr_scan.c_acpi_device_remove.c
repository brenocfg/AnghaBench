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
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* remove ) (struct acpi_device*,int /*<<< orphan*/ ) ;scalar_t__ notify; } ;
struct acpi_driver {TYPE_1__ ops; } ;
struct acpi_device {int /*<<< orphan*/ * driver_data; struct acpi_driver* driver; int /*<<< orphan*/  removal_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_device_remove_notify_handler (struct acpi_device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct acpi_device*,int /*<<< orphan*/ ) ; 
 struct acpi_device* to_acpi_device (struct device*) ; 

__attribute__((used)) static int acpi_device_remove(struct device * dev)
{
	struct acpi_device *acpi_dev = to_acpi_device(dev);
	struct acpi_driver *acpi_drv = acpi_dev->driver;

	if (acpi_drv) {
		if (acpi_drv->ops.notify)
			acpi_device_remove_notify_handler(acpi_dev);
		if (acpi_drv->ops.remove)
			acpi_drv->ops.remove(acpi_dev, acpi_dev->removal_type);
	}
	acpi_dev->driver = NULL;
	acpi_dev->driver_data = NULL;

	put_device(dev);
	return 0;
}