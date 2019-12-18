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
struct TYPE_8__ {int flags; TYPE_2__* parent; } ;
union acpi_parse_object {TYPE_4__ common; } ;
struct TYPE_7__ {scalar_t__ type; } ;
union acpi_operand_object {TYPE_3__ common; } ;
typedef  scalar_t__ u8 ;
struct acpi_walk_state {union acpi_operand_object* result_obj; union acpi_operand_object** operands; union acpi_parse_object* op; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_5__ {scalar_t__ aml_opcode; } ;
struct TYPE_6__ {TYPE_1__ common; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 int ACPI_PARSEOP_IN_STACK ; 
 int ACPI_PARSEOP_TARGET ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ AML_PACKAGE_OP ; 
 scalar_t__ AML_REF_OF_OP ; 
 scalar_t__ AML_VAR_PACKAGE_OP ; 
 int /*<<< orphan*/  acpi_ds_create_operand (struct acpi_walk_state*,union acpi_parse_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ds_obj_stack_pop (int,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ds_result_push (union acpi_operand_object*,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ex_resolve_to_value (union acpi_operand_object**,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ut_copy_iobject_to_iobject (union acpi_operand_object*,union acpi_operand_object**,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ds_evaluate_name_path ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ds_evaluate_name_path(struct acpi_walk_state *walk_state)
{
	acpi_status status = AE_OK;
	union acpi_parse_object *op = walk_state->op;
	union acpi_operand_object **operand = &walk_state->operands[0];
	union acpi_operand_object *new_obj_desc;
	u8 type;

	ACPI_FUNCTION_TRACE_PTR(ds_evaluate_name_path, walk_state);

	if (!op->common.parent) {

		/* This happens after certain exception processing */

		goto exit;
	}

	if ((op->common.parent->common.aml_opcode == AML_PACKAGE_OP) ||
	    (op->common.parent->common.aml_opcode == AML_VAR_PACKAGE_OP) ||
	    (op->common.parent->common.aml_opcode == AML_REF_OF_OP)) {

		/* TBD: Should we specify this feature as a bit of op_info->Flags of these opcodes? */

		goto exit;
	}

	status = acpi_ds_create_operand(walk_state, op, 0);
	if (ACPI_FAILURE(status)) {
		goto exit;
	}

	if (op->common.flags & ACPI_PARSEOP_TARGET) {
		new_obj_desc = *operand;
		goto push_result;
	}

	type = (*operand)->common.type;

	status = acpi_ex_resolve_to_value(operand, walk_state);
	if (ACPI_FAILURE(status)) {
		goto exit;
	}

	if (type == ACPI_TYPE_INTEGER) {

		/* It was incremented by acpi_ex_resolve_to_value */

		acpi_ut_remove_reference(*operand);

		status =
		    acpi_ut_copy_iobject_to_iobject(*operand, &new_obj_desc,
						    walk_state);
		if (ACPI_FAILURE(status)) {
			goto exit;
		}
	} else {
		/*
		 * The object either was anew created or is
		 * a Namespace node - don't decrement it.
		 */
		new_obj_desc = *operand;
	}

	/* Cleanup for name-path operand */

	status = acpi_ds_obj_stack_pop(1, walk_state);
	if (ACPI_FAILURE(status)) {
		walk_state->result_obj = new_obj_desc;
		goto exit;
	}

      push_result:

	walk_state->result_obj = new_obj_desc;

	status = acpi_ds_result_push(walk_state->result_obj, walk_state);
	if (ACPI_SUCCESS(status)) {

		/* Force to take it from stack */

		op->common.flags |= ACPI_PARSEOP_IN_STACK;
	}

      exit:

	return_ACPI_STATUS(status);
}