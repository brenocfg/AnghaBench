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
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_bus_check_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acpi_bus_check_scope(acpi_handle handle)
{
	/* Status Change? */
	acpi_bus_check_device(handle);

	/*
	 * TBD: Enumerate child devices within this device's scope and
	 *       run acpi_bus_check_device()'s on them.
	 */
}