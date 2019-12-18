#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ aml_opcode; scalar_t__ arg_list_length; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {scalar_t__* data; scalar_t__ length; } ;
union acpi_parse_object {TYPE_3__ common; TYPE_2__ named; } ;
typedef  scalar_t__ u8 ;
struct acpi_walk_state {scalar_t__ opcode; scalar_t__ (* descending_callback ) (struct acpi_walk_state*,union acpi_parse_object**) ;union acpi_parse_object* op; int /*<<< orphan*/  parser_state; TYPE_1__* op_info; } ;
struct acpi_opcode_info {int flags; int /*<<< orphan*/  type; } ;
typedef  scalar_t__ acpi_status ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  ACPI_PARSEOP_TARGET ; 
 scalar_t__ AE_CTRL_PARSE_CONTINUE ; 
 scalar_t__ AE_CTRL_PARSE_PENDING ; 
 scalar_t__ AE_CTRL_PENDING ; 
 scalar_t__ AE_NO_MEMORY ; 
 scalar_t__ AE_OK ; 
 scalar_t__ AML_BANK_FIELD_OP ; 
 int AML_CREATE ; 
 int AML_HAS_TARGET ; 
 scalar_t__ AML_INCREMENT_OP ; 
 int AML_NAMED ; 
 union acpi_parse_object* acpi_ps_alloc_op (scalar_t__) ; 
 int /*<<< orphan*/  acpi_ps_append_arg (union acpi_parse_object*,union acpi_parse_object*) ; 
 scalar_t__ acpi_ps_build_named_op (struct acpi_walk_state*,scalar_t__*,union acpi_parse_object*,union acpi_parse_object**) ; 
 int /*<<< orphan*/  acpi_ps_free_op (union acpi_parse_object*) ; 
 scalar_t__ acpi_ps_get_aml_opcode (struct acpi_walk_state*) ; 
 scalar_t__ acpi_ps_get_argument_count (int /*<<< orphan*/ ) ; 
 void* acpi_ps_get_opcode_info (scalar_t__) ; 
 union acpi_parse_object* acpi_ps_get_parent_scope (int /*<<< orphan*/ *) ; 
 scalar_t__ acpi_ps_next_parse_state (struct acpi_walk_state*,union acpi_parse_object*,scalar_t__) ; 
 int /*<<< orphan*/  ps_create_op ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 
 scalar_t__ stub1 (struct acpi_walk_state*,union acpi_parse_object**) ; 

__attribute__((used)) static acpi_status
acpi_ps_create_op(struct acpi_walk_state *walk_state,
		  u8 * aml_op_start, union acpi_parse_object **new_op)
{
	acpi_status status = AE_OK;
	union acpi_parse_object *op;
	union acpi_parse_object *named_op = NULL;
	union acpi_parse_object *parent_scope;
	u8 argument_count;
	const struct acpi_opcode_info *op_info;

	ACPI_FUNCTION_TRACE_PTR(ps_create_op, walk_state);

	status = acpi_ps_get_aml_opcode(walk_state);
	if (status == AE_CTRL_PARSE_CONTINUE) {
		return_ACPI_STATUS(AE_CTRL_PARSE_CONTINUE);
	}

	/* Create Op structure and append to parent's argument list */

	walk_state->op_info = acpi_ps_get_opcode_info(walk_state->opcode);
	op = acpi_ps_alloc_op(walk_state->opcode);
	if (!op) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	if (walk_state->op_info->flags & AML_NAMED) {
		status =
		    acpi_ps_build_named_op(walk_state, aml_op_start, op,
					   &named_op);
		acpi_ps_free_op(op);
		if (ACPI_FAILURE(status)) {
			return_ACPI_STATUS(status);
		}

		*new_op = named_op;
		return_ACPI_STATUS(AE_OK);
	}

	/* Not a named opcode, just allocate Op and append to parent */

	if (walk_state->op_info->flags & AML_CREATE) {
		/*
		 * Backup to beginning of create_xXXfield declaration
		 * body_length is unknown until we parse the body
		 */
		op->named.data = aml_op_start;
		op->named.length = 0;
	}

	if (walk_state->opcode == AML_BANK_FIELD_OP) {
		/*
		 * Backup to beginning of bank_field declaration
		 * body_length is unknown until we parse the body
		 */
		op->named.data = aml_op_start;
		op->named.length = 0;
	}

	parent_scope = acpi_ps_get_parent_scope(&(walk_state->parser_state));
	acpi_ps_append_arg(parent_scope, op);

	if (parent_scope) {
		op_info =
		    acpi_ps_get_opcode_info(parent_scope->common.aml_opcode);
		if (op_info->flags & AML_HAS_TARGET) {
			argument_count =
			    acpi_ps_get_argument_count(op_info->type);
			if (parent_scope->common.arg_list_length >
			    argument_count) {
				op->common.flags |= ACPI_PARSEOP_TARGET;
			}
		} else if (parent_scope->common.aml_opcode == AML_INCREMENT_OP) {
			op->common.flags |= ACPI_PARSEOP_TARGET;
		}
	}

	if (walk_state->descending_callback != NULL) {
		/*
		 * Find the object. This will either insert the object into
		 * the namespace or simply look it up
		 */
		walk_state->op = *new_op = op;

		status = walk_state->descending_callback(walk_state, &op);
		status = acpi_ps_next_parse_state(walk_state, op, status);
		if (status == AE_CTRL_PENDING) {
			status = AE_CTRL_PARSE_PENDING;
		}
	}

	return_ACPI_STATUS(status);
}