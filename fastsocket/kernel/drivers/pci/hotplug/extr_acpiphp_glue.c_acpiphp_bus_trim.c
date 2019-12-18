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
 int acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 int acpi_bus_trim (struct acpi_device*,int) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  err (char*) ; 

__attribute__((used)) static int acpiphp_bus_trim(acpi_handle handle)
{
	struct acpi_device *device;
	int retval;

	retval = acpi_bus_get_device(handle, &device);
	if (retval) {
		dbg("acpi_device not found\n");
		return retval;
	}

	retval = acpi_bus_trim(device, 1);
	if (retval)
		err("cannot remove from acpi list\n");

	return retval;
}