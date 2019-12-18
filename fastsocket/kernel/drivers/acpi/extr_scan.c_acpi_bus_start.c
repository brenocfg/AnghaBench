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
struct acpi_device {int /*<<< orphan*/  handle; } ;
struct acpi_bus_ops {int acpi_op_start; } ;
typedef  int /*<<< orphan*/  ops ;

/* Variables and functions */
 int EINVAL ; 
 int acpi_bus_scan (int /*<<< orphan*/ ,struct acpi_bus_ops*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct acpi_bus_ops*,int /*<<< orphan*/ ,int) ; 

int acpi_bus_start(struct acpi_device *device)
{
	struct acpi_bus_ops ops;

	if (!device)
		return -EINVAL;

	memset(&ops, 0, sizeof(ops));
	ops.acpi_op_start = 1;

	return acpi_bus_scan(device->handle, &ops, NULL);
}