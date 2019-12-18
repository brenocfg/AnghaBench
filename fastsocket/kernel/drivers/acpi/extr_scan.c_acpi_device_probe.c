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
struct device {int /*<<< orphan*/  driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* remove ) (struct acpi_device*,int /*<<< orphan*/ ) ;scalar_t__ notify; } ;
struct acpi_driver {int /*<<< orphan*/  name; TYPE_1__ ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  bus_id; } ;
struct TYPE_6__ {scalar_t__ acpi_op_start; } ;
struct acpi_device {TYPE_2__ pnp; int /*<<< orphan*/  removal_type; TYPE_3__ bus_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int acpi_bus_driver_init (struct acpi_device*,struct acpi_driver*) ; 
 int acpi_device_install_notify_handler (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_start_single_object (struct acpi_device*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct acpi_device*,int /*<<< orphan*/ ) ; 
 struct acpi_device* to_acpi_device (struct device*) ; 
 struct acpi_driver* to_acpi_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_device_probe(struct device * dev)
{
	struct acpi_device *acpi_dev = to_acpi_device(dev);
	struct acpi_driver *acpi_drv = to_acpi_driver(dev->driver);
	int ret;

	ret = acpi_bus_driver_init(acpi_dev, acpi_drv);
	if (!ret) {
		if (acpi_dev->bus_ops.acpi_op_start)
			acpi_start_single_object(acpi_dev);

		if (acpi_drv->ops.notify) {
			ret = acpi_device_install_notify_handler(acpi_dev);
			if (ret) {
				if (acpi_drv->ops.remove)
					acpi_drv->ops.remove(acpi_dev,
						     acpi_dev->removal_type);
				return ret;
			}
		}

		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			"Found driver [%s] for device [%s]\n",
			acpi_drv->name, acpi_dev->pnp.bus_id));
		get_device(dev);
	}
	return ret;
}