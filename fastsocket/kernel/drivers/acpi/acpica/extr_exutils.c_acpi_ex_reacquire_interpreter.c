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

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ex_enter_interpreter () ; 
 int /*<<< orphan*/  acpi_gbl_all_methods_serialized ; 
 int /*<<< orphan*/  ex_reacquire_interpreter ; 
 int /*<<< orphan*/  return_VOID ; 

void acpi_ex_reacquire_interpreter(void)
{
	ACPI_FUNCTION_TRACE(ex_reacquire_interpreter);

	/*
	 * If the global serialized flag is set, do not release the interpreter,
	 * since it was not actually released by acpi_ex_relinquish_interpreter.
	 * This forces the interpreter to be single threaded.
	 */
	if (!acpi_gbl_all_methods_serialized) {
		acpi_ex_enter_interpreter();
	}

	return_VOID;
}