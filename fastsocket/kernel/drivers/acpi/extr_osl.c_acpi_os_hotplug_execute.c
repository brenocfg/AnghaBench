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
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_osd_exec_callback ;

/* Variables and functions */
 int /*<<< orphan*/  __acpi_os_execute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

acpi_status acpi_os_hotplug_execute(acpi_osd_exec_callback function,
	void *context)
{
	return __acpi_os_execute(0, function, context, 1);
}