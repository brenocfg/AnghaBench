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
struct TYPE_3__ {union acpi_parse_object* arg; } ;
struct TYPE_4__ {scalar_t__ aml_opcode; TYPE_1__ value; struct acpi_namespace_node* node; } ;
union acpi_parse_object {TYPE_2__ common; } ;
typedef  union acpi_operand_object {int dummy; } acpi_operand_object ;
struct acpi_walk_state {int /*<<< orphan*/ ** operands; } ;
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_parse_object*) ; 
 int /*<<< orphan*/  ACPI_WALK_OPERANDS ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 scalar_t__ AML_CREATE_FIELD_OP ; 
 int /*<<< orphan*/  acpi_ds_create_operands (struct acpi_walk_state*,union acpi_parse_object*) ; 
 int /*<<< orphan*/  acpi_ds_init_buffer_field (scalar_t__,union acpi_operand_object*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ex_resolve_operands (scalar_t__,int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 union acpi_operand_object* acpi_ns_get_attached_object (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ps_get_opcode_name (scalar_t__) ; 
 int /*<<< orphan*/  ds_eval_buffer_field_operands ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ds_eval_buffer_field_operands(struct acpi_walk_state *walk_state,
				   union acpi_parse_object *op)
{
	acpi_status status;
	union acpi_operand_object *obj_desc;
	struct acpi_namespace_node *node;
	union acpi_parse_object *next_op;

	ACPI_FUNCTION_TRACE_PTR(ds_eval_buffer_field_operands, op);

	/*
	 * This is where we evaluate the address and length fields of the
	 * create_xxx_field declaration
	 */
	node = op->common.node;

	/* next_op points to the op that holds the Buffer */

	next_op = op->common.value.arg;

	/* Evaluate/create the address and length operands */

	status = acpi_ds_create_operands(walk_state, next_op);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	obj_desc = acpi_ns_get_attached_object(node);
	if (!obj_desc) {
		return_ACPI_STATUS(AE_NOT_EXIST);
	}

	/* Resolve the operands */

	status = acpi_ex_resolve_operands(op->common.aml_opcode,
					  ACPI_WALK_OPERANDS, walk_state);
	if (ACPI_FAILURE(status)) {
		ACPI_ERROR((AE_INFO, "(%s) bad operand(s) (%X)",
			    acpi_ps_get_opcode_name(op->common.aml_opcode),
			    status));

		return_ACPI_STATUS(status);
	}

	/* Initialize the Buffer Field */

	if (op->common.aml_opcode == AML_CREATE_FIELD_OP) {

		/* NOTE: Slightly different operands for this opcode */

		status =
		    acpi_ds_init_buffer_field(op->common.aml_opcode, obj_desc,
					      walk_state->operands[0],
					      walk_state->operands[1],
					      walk_state->operands[2],
					      walk_state->operands[3]);
	} else {
		/* All other, create_xxx_field opcodes */

		status =
		    acpi_ds_init_buffer_field(op->common.aml_opcode, obj_desc,
					      walk_state->operands[0],
					      walk_state->operands[1], NULL,
					      walk_state->operands[2]);
	}

	return_ACPI_STATUS(status);
}