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
struct TYPE_2__ {int (* resume ) (struct acpi_device*) ;} ;
struct acpi_driver {TYPE_1__ ops; } ;
struct acpi_device {struct acpi_driver* driver; } ;

/* Variables and functions */
 int stub1 (struct acpi_device*) ; 
 struct acpi_device* to_acpi_device (struct device*) ; 

__attribute__((used)) static int acpi_device_resume(struct device *dev)
{
	struct acpi_device *acpi_dev = to_acpi_device(dev);
	struct acpi_driver *acpi_drv = acpi_dev->driver;

	if (acpi_drv && acpi_drv->ops.resume)
		return acpi_drv->ops.resume(acpi_dev);
	return 0;
}