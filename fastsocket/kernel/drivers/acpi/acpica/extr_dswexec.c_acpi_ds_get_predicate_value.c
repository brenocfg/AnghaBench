#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ value; } ;
struct TYPE_5__ {scalar_t__ type; } ;
union acpi_operand_object {TYPE_2__ integer; TYPE_1__ common; } ;
struct acpi_walk_state {TYPE_4__* control_state; int /*<<< orphan*/  op; union acpi_operand_object** operands; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_7__ {scalar_t__ state; int /*<<< orphan*/  value; } ;
struct TYPE_8__ {TYPE_3__ common; } ;

/* Variables and functions */
 scalar_t__ ACPI_CONTROL_NORMAL ; 
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUGGER_EXEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  AE_AML_NO_OPERAND ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_CTRL_FALSE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_db_display_result_object (union acpi_operand_object*,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ds_create_operand (struct acpi_walk_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ds_do_implicit_return (union acpi_operand_object*,struct acpi_walk_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ds_result_pop (union acpi_operand_object**,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ex_convert_to_integer (union acpi_operand_object*,union acpi_operand_object**,int) ; 
 int /*<<< orphan*/  acpi_ex_resolve_to_value (union acpi_operand_object**,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ex_truncate_for32bit_table (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ds_get_predicate_value ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ds_get_predicate_value(struct acpi_walk_state *walk_state,
			    union acpi_operand_object *result_obj)
{
	acpi_status status = AE_OK;
	union acpi_operand_object *obj_desc;
	union acpi_operand_object *local_obj_desc = NULL;

	ACPI_FUNCTION_TRACE_PTR(ds_get_predicate_value, walk_state);

	walk_state->control_state->common.state = 0;

	if (result_obj) {
		status = acpi_ds_result_pop(&obj_desc, walk_state);
		if (ACPI_FAILURE(status)) {
			ACPI_EXCEPTION((AE_INFO, status,
					"Could not get result from predicate evaluation"));

			return_ACPI_STATUS(status);
		}
	} else {
		status = acpi_ds_create_operand(walk_state, walk_state->op, 0);
		if (ACPI_FAILURE(status)) {
			return_ACPI_STATUS(status);
		}

		status =
		    acpi_ex_resolve_to_value(&walk_state->operands[0],
					     walk_state);
		if (ACPI_FAILURE(status)) {
			return_ACPI_STATUS(status);
		}

		obj_desc = walk_state->operands[0];
	}

	if (!obj_desc) {
		ACPI_ERROR((AE_INFO,
			    "No predicate ObjDesc=%p State=%p",
			    obj_desc, walk_state));

		return_ACPI_STATUS(AE_AML_NO_OPERAND);
	}

	/*
	 * Result of predicate evaluation must be an Integer
	 * object. Implicitly convert the argument if necessary.
	 */
	status = acpi_ex_convert_to_integer(obj_desc, &local_obj_desc, 16);
	if (ACPI_FAILURE(status)) {
		goto cleanup;
	}

	if (local_obj_desc->common.type != ACPI_TYPE_INTEGER) {
		ACPI_ERROR((AE_INFO,
			    "Bad predicate (not an integer) ObjDesc=%p State=%p Type=%X",
			    obj_desc, walk_state, obj_desc->common.type));

		status = AE_AML_OPERAND_TYPE;
		goto cleanup;
	}

	/* Truncate the predicate to 32-bits if necessary */

	acpi_ex_truncate_for32bit_table(local_obj_desc);

	/*
	 * Save the result of the predicate evaluation on
	 * the control stack
	 */
	if (local_obj_desc->integer.value) {
		walk_state->control_state->common.value = TRUE;
	} else {
		/*
		 * Predicate is FALSE, we will just toss the
		 * rest of the package
		 */
		walk_state->control_state->common.value = FALSE;
		status = AE_CTRL_FALSE;
	}

	/* Predicate can be used for an implicit return value */

	(void)acpi_ds_do_implicit_return(local_obj_desc, walk_state, TRUE);

      cleanup:

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Completed a predicate eval=%X Op=%p\n",
			  walk_state->control_state->common.value,
			  walk_state->op));

	/* Break to debugger to display result */

	ACPI_DEBUGGER_EXEC(acpi_db_display_result_object
			   (local_obj_desc, walk_state));

	/*
	 * Delete the predicate result object (we know that
	 * we don't need it anymore)
	 */
	if (local_obj_desc != obj_desc) {
		acpi_ut_remove_reference(local_obj_desc);
	}
	acpi_ut_remove_reference(obj_desc);

	walk_state->control_state->common.state = ACPI_CONTROL_NORMAL;
	return_ACPI_STATUS(status);
}