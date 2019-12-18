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
typedef  int /*<<< orphan*/  acpi_execute_type ;

/* Variables and functions */
 int /*<<< orphan*/  __acpi_os_execute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

acpi_status acpi_os_execute(acpi_execute_type type,
			    acpi_osd_exec_callback function, void *context)
{
	return __acpi_os_execute(type, function, context, 0);
}