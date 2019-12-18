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
struct acpi_bus_ops {int acpi_op_add; } ;
typedef  int /*<<< orphan*/  ops ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int acpi_bus_scan (int /*<<< orphan*/ ,struct acpi_bus_ops*,struct acpi_device**) ; 
 int /*<<< orphan*/  memset (struct acpi_bus_ops*,int /*<<< orphan*/ ,int) ; 

int
acpi_bus_add(struct acpi_device **child,
	     struct acpi_device *parent, acpi_handle handle, int type)
{
	struct acpi_bus_ops ops;

	memset(&ops, 0, sizeof(ops));
	ops.acpi_op_add = 1;

	return acpi_bus_scan(handle, &ops, child);
}