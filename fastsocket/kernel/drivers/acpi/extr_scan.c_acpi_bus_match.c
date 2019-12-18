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
struct device_driver {int dummy; } ;
struct device {int dummy; } ;
struct acpi_driver {int /*<<< orphan*/  ids; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_match_device_ids (struct acpi_device*,int /*<<< orphan*/ ) ; 
 struct acpi_device* to_acpi_device (struct device*) ; 
 struct acpi_driver* to_acpi_driver (struct device_driver*) ; 

__attribute__((used)) static int acpi_bus_match(struct device *dev, struct device_driver *drv)
{
	struct acpi_device *acpi_dev = to_acpi_device(dev);
	struct acpi_driver *acpi_drv = to_acpi_driver(drv);

	return !acpi_match_device_ids(acpi_dev, acpi_drv->ids);
}