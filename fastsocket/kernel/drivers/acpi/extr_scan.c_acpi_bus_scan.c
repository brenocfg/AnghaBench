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
struct acpi_bus_ops {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_bus_check_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_bus_ops*,void**) ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_bus_ops*,void**),struct acpi_bus_ops*,void**) ; 

__attribute__((used)) static int acpi_bus_scan(acpi_handle handle, struct acpi_bus_ops *ops,
			 struct acpi_device **child)
{
	acpi_status status;
	void *device = NULL;

	status = acpi_bus_check_add(handle, 0, ops, &device);
	if (ACPI_SUCCESS(status))
		acpi_walk_namespace(ACPI_TYPE_ANY, handle, ACPI_UINT32_MAX,
				    acpi_bus_check_add, ops, &device);

	if (child)
		*child = device;

	if (device)
		return 0;
	else
		return -ENODEV;
}