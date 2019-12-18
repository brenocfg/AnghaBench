#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct acpi_walk_state {int /*<<< orphan*/  op; int /*<<< orphan*/  aml_offset; int /*<<< orphan*/  opcode; TYPE_2__* method_node; } ;
typedef  int acpi_status ;
struct TYPE_3__ {int /*<<< orphan*/  integer; } ;
struct TYPE_4__ {TYPE_1__ name; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ ACPI_SUCCESS (int) ; 
 int AE_CODE_CONTROL ; 
 int /*<<< orphan*/  acpi_dm_dump_method_info (int,struct acpi_walk_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ds_clear_implicit_return (struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ex_enter_interpreter () ; 
 int /*<<< orphan*/  acpi_ex_exit_interpreter () ; 
 int acpi_gbl_exception_handler (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

acpi_status
acpi_ds_method_error(acpi_status status, struct acpi_walk_state *walk_state)
{
	ACPI_FUNCTION_ENTRY();

	/* Ignore AE_OK and control exception codes */

	if (ACPI_SUCCESS(status) || (status & AE_CODE_CONTROL)) {
		return (status);
	}

	/* Invoke the global exception handler */

	if (acpi_gbl_exception_handler) {

		/* Exit the interpreter, allow handler to execute methods */

		acpi_ex_exit_interpreter();

		/*
		 * Handler can map the exception code to anything it wants, including
		 * AE_OK, in which case the executing method will not be aborted.
		 */
		status = acpi_gbl_exception_handler(status,
						    walk_state->method_node ?
						    walk_state->method_node->
						    name.integer : 0,
						    walk_state->opcode,
						    walk_state->aml_offset,
						    NULL);
		acpi_ex_enter_interpreter();
	}

	acpi_ds_clear_implicit_return(walk_state);

#ifdef ACPI_DISASSEMBLER
	if (ACPI_FAILURE(status)) {

		/* Display method locals/args if disassembler is present */

		acpi_dm_dump_method_info(status, walk_state, walk_state->op);
	}
#endif

	return (status);
}