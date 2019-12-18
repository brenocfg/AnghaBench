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
struct acpiphp_func {int /*<<< orphan*/  handle; } ;
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BUS_TYPE_DEVICE ; 
 int acpi_bus_add (struct acpi_device**,struct acpi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 int acpi_bus_start (struct acpi_device*) ; 
 int acpi_bus_trim (struct acpi_device*,int) ; 
 int /*<<< orphan*/  acpi_get_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg (char*,...) ; 

__attribute__((used)) static int acpiphp_bus_add(struct acpiphp_func *func)
{
	acpi_handle phandle;
	struct acpi_device *device, *pdevice;
	int ret_val;

	acpi_get_parent(func->handle, &phandle);
	if (acpi_bus_get_device(phandle, &pdevice)) {
		dbg("no parent device, assuming NULL\n");
		pdevice = NULL;
	}
	if (!acpi_bus_get_device(func->handle, &device)) {
		dbg("bus exists... trim\n");
		/* this shouldn't be in here, so remove
		 * the bus then re-add it...
		 */
		ret_val = acpi_bus_trim(device, 1);
		dbg("acpi_bus_trim return %x\n", ret_val);
	}

	ret_val = acpi_bus_add(&device, pdevice, func->handle,
		ACPI_BUS_TYPE_DEVICE);
	if (ret_val) {
		dbg("error adding bus, %x\n",
			-ret_val);
		goto acpiphp_bus_add_out;
	}
	ret_val = acpi_bus_start(device);

acpiphp_bus_add_out:
	return ret_val;
}