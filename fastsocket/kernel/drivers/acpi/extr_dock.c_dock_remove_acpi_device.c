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
 int /*<<< orphan*/  acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 int acpi_bus_trim (struct acpi_device*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static void dock_remove_acpi_device(acpi_handle handle)
{
	struct acpi_device *device;
	int ret;

	if (!acpi_bus_get_device(handle, &device)) {
		ret = acpi_bus_trim(device, 1);
		if (ret)
			pr_debug("error removing bus, %x\n", -ret);
	}
}