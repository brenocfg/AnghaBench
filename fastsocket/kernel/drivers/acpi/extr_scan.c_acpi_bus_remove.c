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
struct TYPE_4__ {scalar_t__ bus_address; } ;
struct acpi_device {TYPE_2__* parent; TYPE_1__ flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  removal_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* unbind ) (struct acpi_device*) ;} ;
struct TYPE_5__ {TYPE_3__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BUS_REMOVAL_EJECT ; 
 int EINVAL ; 
 int /*<<< orphan*/  acpi_device_unregister (struct acpi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_release_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct acpi_device*) ; 

__attribute__((used)) static int acpi_bus_remove(struct acpi_device *dev, int rmdevice)
{
	if (!dev)
		return -EINVAL;

	dev->removal_type = ACPI_BUS_REMOVAL_EJECT;
	device_release_driver(&dev->dev);

	if (!rmdevice)
		return 0;

	/*
	 * unbind _ADR-Based Devices when hot removal
	 */
	if (dev->flags.bus_address) {
		if ((dev->parent) && (dev->parent->ops.unbind))
			dev->parent->ops.unbind(dev);
	}
	acpi_device_unregister(dev, ACPI_BUS_REMOVAL_EJECT);

	return 0;
}