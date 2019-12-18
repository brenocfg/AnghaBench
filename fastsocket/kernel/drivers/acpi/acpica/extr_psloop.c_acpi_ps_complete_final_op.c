#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  aml_opcode; } ;
union acpi_parse_object {TYPE_1__ common; } ;
struct acpi_walk_state {scalar_t__ (* ascending_callback ) (struct acpi_walk_state*) ;int /*<<< orphan*/  arg_count; int /*<<< orphan*/  arg_types; int /*<<< orphan*/  parser_state; int /*<<< orphan*/  opcode; int /*<<< orphan*/  op_info; union acpi_parse_object* op; } ;
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_PARSE ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 scalar_t__ AE_CTRL_PENDING ; 
 scalar_t__ AE_CTRL_TERMINATE ; 
 scalar_t__ AE_OK ; 
 scalar_t__ acpi_ps_complete_op (struct acpi_walk_state*,union acpi_parse_object**,scalar_t__) ; 
 scalar_t__ acpi_ps_complete_this_op (struct acpi_walk_state*,union acpi_parse_object*) ; 
 int /*<<< orphan*/  acpi_ps_get_opcode_info (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_ps_next_parse_state (struct acpi_walk_state*,union acpi_parse_object*,scalar_t__) ; 
 int /*<<< orphan*/  acpi_ps_pop_scope (int /*<<< orphan*/ *,union acpi_parse_object**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ps_complete_final_op ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 
 scalar_t__ stub1 (struct acpi_walk_state*) ; 

__attribute__((used)) static acpi_status
acpi_ps_complete_final_op(struct acpi_walk_state *walk_state,
			  union acpi_parse_object *op, acpi_status status)
{
	acpi_status status2;

	ACPI_FUNCTION_TRACE_PTR(ps_complete_final_op, walk_state);

	/*
	 * Complete the last Op (if not completed), and clear the scope stack.
	 * It is easily possible to end an AML "package" with an unbounded number
	 * of open scopes (such as when several ASL blocks are closed with
	 * sequential closing braces). We want to terminate each one cleanly.
	 */
	ACPI_DEBUG_PRINT((ACPI_DB_PARSE, "AML package complete at Op %p\n",
			  op));
	do {
		if (op) {
			if (walk_state->ascending_callback != NULL) {
				walk_state->op = op;
				walk_state->op_info =
				    acpi_ps_get_opcode_info(op->common.
							    aml_opcode);
				walk_state->opcode = op->common.aml_opcode;

				status =
				    walk_state->ascending_callback(walk_state);
				status =
				    acpi_ps_next_parse_state(walk_state, op,
							     status);
				if (status == AE_CTRL_PENDING) {
					status =
					    acpi_ps_complete_op(walk_state, &op,
								AE_OK);
					if (ACPI_FAILURE(status)) {
						return_ACPI_STATUS(status);
					}
				}

				if (status == AE_CTRL_TERMINATE) {
					status = AE_OK;

					/* Clean up */
					do {
						if (op) {
							status2 =
							    acpi_ps_complete_this_op
							    (walk_state, op);
							if (ACPI_FAILURE
							    (status2)) {
								return_ACPI_STATUS
								    (status2);
							}
						}

						acpi_ps_pop_scope(&
								  (walk_state->
								   parser_state),
								  &op,
								  &walk_state->
								  arg_types,
								  &walk_state->
								  arg_count);

					} while (op);

					return_ACPI_STATUS(status);
				}

				else if (ACPI_FAILURE(status)) {

					/* First error is most important */

					(void)
					    acpi_ps_complete_this_op(walk_state,
								     op);
					return_ACPI_STATUS(status);
				}
			}

			status2 = acpi_ps_complete_this_op(walk_state, op);
			if (ACPI_FAILURE(status2)) {
				return_ACPI_STATUS(status2);
			}
		}

		acpi_ps_pop_scope(&(walk_state->parser_state), &op,
				  &walk_state->arg_types,
				  &walk_state->arg_count);

	} while (op);

	return_ACPI_STATUS(status);
}