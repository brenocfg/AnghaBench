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
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BUS_TYPE_DEVICE ; 
 int acpi_bus_add (struct acpi_device**,struct acpi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 int /*<<< orphan*/  acpi_get_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static struct acpi_device * dock_create_acpi_device(acpi_handle handle)
{
	struct acpi_device *device = NULL;
	struct acpi_device *parent_device;
	acpi_handle parent;
	int ret;

	if (acpi_bus_get_device(handle, &device)) {
		/*
		 * no device created for this object,
		 * so we should create one.
		 */
		acpi_get_parent(handle, &parent);
		if (acpi_bus_get_device(parent, &parent_device))
			parent_device = NULL;

		ret = acpi_bus_add(&device, parent_device, handle,
			ACPI_BUS_TYPE_DEVICE);
		if (ret) {
			pr_debug("error adding bus, %x\n",
				-ret);
			return NULL;
		}
	}
	return device;
}