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
typedef  int /*<<< orphan*/  acpi_integer ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ex_reacquire_interpreter () ; 
 int /*<<< orphan*/  acpi_ex_relinquish_interpreter () ; 
 int /*<<< orphan*/  acpi_os_sleep (int /*<<< orphan*/ ) ; 

acpi_status acpi_ex_system_do_suspend(acpi_integer how_long)
{
	ACPI_FUNCTION_ENTRY();

	/* Since this thread will sleep, we must release the interpreter */

	acpi_ex_relinquish_interpreter();

	acpi_os_sleep(how_long);

	/* And now we must get the interpreter again */

	acpi_ex_reacquire_interpreter();
	return (AE_OK);
}