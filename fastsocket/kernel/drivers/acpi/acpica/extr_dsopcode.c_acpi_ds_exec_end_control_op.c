#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  arg; } ;
struct TYPE_19__ {int aml_opcode; TYPE_2__ value; } ;
union acpi_parse_object {TYPE_8__ common; } ;
struct TYPE_18__ {int const opcode; int /*<<< orphan*/  package_end; int /*<<< orphan*/  aml_predicate_start; int /*<<< orphan*/  loop_count; } ;
struct TYPE_12__ {int /*<<< orphan*/  value; } ;
union acpi_generic_state {TYPE_7__ control; TYPE_1__ common; } ;
typedef  int /*<<< orphan*/  u8 ;
struct acpi_walk_state {union acpi_generic_state* control_state; int /*<<< orphan*/  aml_last_while; TYPE_9__* return_desc; int /*<<< orphan*/  num_operands; TYPE_9__** operands; TYPE_6__* results; int /*<<< orphan*/  result_count; int /*<<< orphan*/  last_predicate; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_15__ {int /*<<< orphan*/  class; } ;
struct TYPE_14__ {int /*<<< orphan*/  type; } ;
struct TYPE_20__ {TYPE_4__ reference; TYPE_3__ common; } ;
struct TYPE_16__ {TYPE_9__** obj_desc; } ;
struct TYPE_17__ {TYPE_5__ results; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_DISPATCH ; 
 int /*<<< orphan*/  ACPI_DEBUGGER_EXEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DESC_TYPE_OPERAND ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_GET_DESCRIPTOR_TYPE (TYPE_9__*) ; 
 int /*<<< orphan*/  ACPI_MAX_LOOP_ITERATIONS ; 
 int /*<<< orphan*/  ACPI_REFCLASS_INDEX ; 
 int /*<<< orphan*/  ACPI_SIGNAL_BREAKPOINT ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_REFERENCE ; 
 int /*<<< orphan*/  AE_AML_BAD_OPCODE ; 
 int /*<<< orphan*/  AE_AML_INFINITE_LOOP ; 
 int /*<<< orphan*/  AE_AML_NO_WHILE ; 
 int /*<<< orphan*/  AE_CTRL_BREAK ; 
 int /*<<< orphan*/  AE_CTRL_CONTINUE ; 
 int /*<<< orphan*/  AE_CTRL_PENDING ; 
 int /*<<< orphan*/  AE_CTRL_TERMINATE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
#define  AML_BREAK_OP 135 
#define  AML_BREAK_POINT_OP 134 
#define  AML_CONTINUE_OP 133 
#define  AML_ELSE_OP 132 
#define  AML_IF_OP 131 
#define  AML_NOOP_OP 130 
#define  AML_RETURN_OP 129 
#define  AML_WHILE_OP 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_ds_clear_implicit_return (struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ds_create_operands (struct acpi_walk_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ex_resolve_to_value (TYPE_9__**,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_gbl_cm_single_step ; 
 int /*<<< orphan*/  acpi_os_printf (char*) ; 
 int /*<<< orphan*/  acpi_os_signal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  acpi_ut_delete_generic_state (union acpi_generic_state*) ; 
 union acpi_generic_state* acpi_ut_pop_generic_state (union acpi_generic_state**) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (TYPE_9__*) ; 
 int /*<<< orphan*/  ds_exec_end_control_op ; 

acpi_status
acpi_ds_exec_end_control_op(struct acpi_walk_state * walk_state,
			    union acpi_parse_object * op)
{
	acpi_status status = AE_OK;
	union acpi_generic_state *control_state;

	ACPI_FUNCTION_NAME(ds_exec_end_control_op);

	switch (op->common.aml_opcode) {
	case AML_IF_OP:

		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH, "[IF_OP] Op=%p\n", op));

		/*
		 * Save the result of the predicate in case there is an
		 * ELSE to come
		 */
		walk_state->last_predicate =
		    (u8) walk_state->control_state->common.value;

		/*
		 * Pop the control state that was created at the start
		 * of the IF and free it
		 */
		control_state =
		    acpi_ut_pop_generic_state(&walk_state->control_state);
		acpi_ut_delete_generic_state(control_state);
		break;

	case AML_ELSE_OP:

		break;

	case AML_WHILE_OP:

		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH, "[WHILE_OP] Op=%p\n", op));

		control_state = walk_state->control_state;
		if (control_state->common.value) {

			/* Predicate was true, the body of the loop was just executed */

			/*
			 * This loop counter mechanism allows the interpreter to escape
			 * possibly infinite loops. This can occur in poorly written AML
			 * when the hardware does not respond within a while loop and the
			 * loop does not implement a timeout.
			 */
			control_state->control.loop_count++;
			if (control_state->control.loop_count >
				ACPI_MAX_LOOP_ITERATIONS) {
				status = AE_AML_INFINITE_LOOP;
				break;
			}

			/*
			 * Go back and evaluate the predicate and maybe execute the loop
			 * another time
			 */
			status = AE_CTRL_PENDING;
			walk_state->aml_last_while =
			    control_state->control.aml_predicate_start;
			break;
		}

		/* Predicate was false, terminate this while loop */

		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
				  "[WHILE_OP] termination! Op=%p\n", op));

		/* Pop this control state and free it */

		control_state =
		    acpi_ut_pop_generic_state(&walk_state->control_state);
		acpi_ut_delete_generic_state(control_state);
		break;

	case AML_RETURN_OP:

		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
				  "[RETURN_OP] Op=%p Arg=%p\n", op,
				  op->common.value.arg));

		/*
		 * One optional operand -- the return value
		 * It can be either an immediate operand or a result that
		 * has been bubbled up the tree
		 */
		if (op->common.value.arg) {

			/* Since we have a real Return(), delete any implicit return */

			acpi_ds_clear_implicit_return(walk_state);

			/* Return statement has an immediate operand */

			status =
			    acpi_ds_create_operands(walk_state,
						    op->common.value.arg);
			if (ACPI_FAILURE(status)) {
				return (status);
			}

			/*
			 * If value being returned is a Reference (such as
			 * an arg or local), resolve it now because it may
			 * cease to exist at the end of the method.
			 */
			status =
			    acpi_ex_resolve_to_value(&walk_state->operands[0],
						     walk_state);
			if (ACPI_FAILURE(status)) {
				return (status);
			}

			/*
			 * Get the return value and save as the last result
			 * value.  This is the only place where walk_state->return_desc
			 * is set to anything other than zero!
			 */
			walk_state->return_desc = walk_state->operands[0];
		} else if (walk_state->result_count) {

			/* Since we have a real Return(), delete any implicit return */

			acpi_ds_clear_implicit_return(walk_state);

			/*
			 * The return value has come from a previous calculation.
			 *
			 * If value being returned is a Reference (such as
			 * an arg or local), resolve it now because it may
			 * cease to exist at the end of the method.
			 *
			 * Allow references created by the Index operator to return unchanged.
			 */
			if ((ACPI_GET_DESCRIPTOR_TYPE
			     (walk_state->results->results.obj_desc[0]) ==
			     ACPI_DESC_TYPE_OPERAND)
			    && ((walk_state->results->results.obj_desc[0])->
				common.type == ACPI_TYPE_LOCAL_REFERENCE)
			    && ((walk_state->results->results.obj_desc[0])->
				reference.class != ACPI_REFCLASS_INDEX)) {
				status =
				    acpi_ex_resolve_to_value(&walk_state->
							     results->results.
							     obj_desc[0],
							     walk_state);
				if (ACPI_FAILURE(status)) {
					return (status);
				}
			}

			walk_state->return_desc =
			    walk_state->results->results.obj_desc[0];
		} else {
			/* No return operand */

			if (walk_state->num_operands) {
				acpi_ut_remove_reference(walk_state->
							 operands[0]);
			}

			walk_state->operands[0] = NULL;
			walk_state->num_operands = 0;
			walk_state->return_desc = NULL;
		}

		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
				  "Completed RETURN_OP State=%p, RetVal=%p\n",
				  walk_state, walk_state->return_desc));

		/* End the control method execution right now */

		status = AE_CTRL_TERMINATE;
		break;

	case AML_NOOP_OP:

		/* Just do nothing! */
		break;

	case AML_BREAK_POINT_OP:

		/*
		 * Set the single-step flag. This will cause the debugger (if present)
		 * to break to the console within the AML debugger at the start of the
		 * next AML instruction.
		 */
		ACPI_DEBUGGER_EXEC(acpi_gbl_cm_single_step = TRUE);
		ACPI_DEBUGGER_EXEC(acpi_os_printf
				   ("**break** Executed AML BreakPoint opcode\n"));

		/* Call to the OSL in case OS wants a piece of the action */

		status = acpi_os_signal(ACPI_SIGNAL_BREAKPOINT,
					"Executed AML Breakpoint opcode");
		break;

	case AML_BREAK_OP:
	case AML_CONTINUE_OP:	/* ACPI 2.0 */

		/* Pop and delete control states until we find a while */

		while (walk_state->control_state &&
		       (walk_state->control_state->control.opcode !=
			AML_WHILE_OP)) {
			control_state =
			    acpi_ut_pop_generic_state(&walk_state->
						      control_state);
			acpi_ut_delete_generic_state(control_state);
		}

		/* No while found? */

		if (!walk_state->control_state) {
			return (AE_AML_NO_WHILE);
		}

		/* Was: walk_state->aml_last_while = walk_state->control_state->Control.aml_predicate_start; */

		walk_state->aml_last_while =
		    walk_state->control_state->control.package_end;

		/* Return status depending on opcode */

		if (op->common.aml_opcode == AML_BREAK_OP) {
			status = AE_CTRL_BREAK;
		} else {
			status = AE_CTRL_CONTINUE;
		}
		break;

	default:

		ACPI_ERROR((AE_INFO, "Unknown control opcode=%X Op=%p",
			    op->common.aml_opcode, op));

		status = AE_AML_BAD_OPCODE;
		break;
	}

	return (status);
}