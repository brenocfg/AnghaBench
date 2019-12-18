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
 int ENODEV ; 
 scalar_t__ acpi_bus_add (struct acpi_device**,struct acpi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 int acpi_bus_start (struct acpi_device*) ; 
 scalar_t__ acpi_get_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int container_device_add(struct acpi_device **device, acpi_handle handle)
{
	acpi_handle phandle;
	struct acpi_device *pdev;
	int result;


	if (acpi_get_parent(handle, &phandle)) {
		return -ENODEV;
	}

	if (acpi_bus_get_device(phandle, &pdev)) {
		return -ENODEV;
	}

	if (acpi_bus_add(device, pdev, handle, ACPI_BUS_TYPE_DEVICE)) {
		return -ENODEV;
	}

	result = acpi_bus_start(*device);

	return result;
}