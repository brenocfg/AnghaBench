#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ aml_opcode; int /*<<< orphan*/  aml_offset; } ;
struct TYPE_16__ {int /*<<< orphan*/ * data; void* length; } ;
union acpi_parse_object {TYPE_8__ common; TYPE_7__ named; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
struct acpi_parse_state {int /*<<< orphan*/ * aml; int /*<<< orphan*/ * aml_end; TYPE_4__* scope; } ;
struct acpi_walk_state {int walk_type; scalar_t__ (* ascending_callback ) (struct acpi_walk_state*) ;scalar_t__ opcode; union acpi_parse_object* op; TYPE_9__* op_info; int /*<<< orphan*/  arg_count; int /*<<< orphan*/  arg_types; int /*<<< orphan*/  aml_offset; int /*<<< orphan*/  prev_arg_types; union acpi_parse_object* prev_op; TYPE_6__* control_state; struct acpi_parse_state parser_state; int /*<<< orphan*/ * descending_callback; } ;
typedef  scalar_t__ acpi_status ;
struct TYPE_18__ {int flags; int /*<<< orphan*/  name; } ;
struct TYPE_14__ {scalar_t__ state; } ;
struct TYPE_15__ {TYPE_5__ common; } ;
struct TYPE_12__ {TYPE_2__* op; } ;
struct TYPE_13__ {TYPE_3__ parse_scope; } ;
struct TYPE_10__ {scalar_t__ aml_opcode; } ;
struct TYPE_11__ {TYPE_1__ common; } ;

/* Variables and functions */
 scalar_t__ ACPI_CONTROL_PREDICATE_EXECUTING ; 
 int /*<<< orphan*/  ACPI_DB_PARSE ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  ACPI_TO_POINTER (int /*<<< orphan*/ ) ; 
 int ACPI_WALK_METHOD_RESTART ; 
 scalar_t__ AE_AML_NO_RETURN_VALUE ; 
 scalar_t__ AE_BAD_PARAMETER ; 
 scalar_t__ AE_CODE_CONTROL ; 
 scalar_t__ AE_CODE_MASK ; 
 scalar_t__ AE_CTRL_PARSE_CONTINUE ; 
 scalar_t__ AE_CTRL_PARSE_PENDING ; 
 scalar_t__ AE_CTRL_PENDING ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AE_OK ; 
 scalar_t__ AML_BANK_FIELD_OP ; 
 int AML_CREATE ; 
 scalar_t__ AML_DATA_REGION_OP ; 
 scalar_t__ AML_IF_OP ; 
 int AML_NAMED ; 
 scalar_t__ AML_REGION_OP ; 
 scalar_t__ AML_WHILE_OP ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ acpi_ds_get_predicate_value (struct acpi_walk_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_gbl_depth ; 
 scalar_t__ acpi_ps_complete_final_op (struct acpi_walk_state*,union acpi_parse_object*,scalar_t__) ; 
 scalar_t__ acpi_ps_complete_op (struct acpi_walk_state*,union acpi_parse_object**,scalar_t__) ; 
 scalar_t__ acpi_ps_create_op (struct acpi_walk_state*,int /*<<< orphan*/ *,union acpi_parse_object**) ; 
 scalar_t__ acpi_ps_get_arguments (struct acpi_walk_state*,int /*<<< orphan*/ *,union acpi_parse_object*) ; 
 TYPE_9__* acpi_ps_get_opcode_info (scalar_t__) ; 
 scalar_t__ acpi_ps_has_completed_scope (struct acpi_parse_state*) ; 
 scalar_t__ acpi_ps_next_parse_state (struct acpi_walk_state*,union acpi_parse_object*,scalar_t__) ; 
 int /*<<< orphan*/  acpi_ps_pop_scope (struct acpi_parse_state*,union acpi_parse_object**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ acpi_ps_push_scope (struct acpi_parse_state*,union acpi_parse_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps_parse_loop ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 
 scalar_t__ stub1 (struct acpi_walk_state*) ; 

acpi_status acpi_ps_parse_loop(struct acpi_walk_state *walk_state)
{
	acpi_status status = AE_OK;
	union acpi_parse_object *op = NULL;	/* current op */
	struct acpi_parse_state *parser_state;
	u8 *aml_op_start = NULL;

	ACPI_FUNCTION_TRACE_PTR(ps_parse_loop, walk_state);

	if (walk_state->descending_callback == NULL) {
		return_ACPI_STATUS(AE_BAD_PARAMETER);
	}

	parser_state = &walk_state->parser_state;
	walk_state->arg_types = 0;

#if (!defined (ACPI_NO_METHOD_EXECUTION) && !defined (ACPI_CONSTANT_EVAL_ONLY))

	if (walk_state->walk_type & ACPI_WALK_METHOD_RESTART) {

		/* We are restarting a preempted control method */

		if (acpi_ps_has_completed_scope(parser_state)) {
			/*
			 * We must check if a predicate to an IF or WHILE statement
			 * was just completed
			 */
			if ((parser_state->scope->parse_scope.op) &&
			    ((parser_state->scope->parse_scope.op->common.
			      aml_opcode == AML_IF_OP)
			     || (parser_state->scope->parse_scope.op->common.
				 aml_opcode == AML_WHILE_OP))
			    && (walk_state->control_state)
			    && (walk_state->control_state->common.state ==
				ACPI_CONTROL_PREDICATE_EXECUTING)) {
				/*
				 * A predicate was just completed, get the value of the
				 * predicate and branch based on that value
				 */
				walk_state->op = NULL;
				status =
				    acpi_ds_get_predicate_value(walk_state,
								ACPI_TO_POINTER
								(TRUE));
				if (ACPI_FAILURE(status)
				    && ((status & AE_CODE_MASK) !=
					AE_CODE_CONTROL)) {
					if (status == AE_AML_NO_RETURN_VALUE) {
						ACPI_EXCEPTION((AE_INFO, status,
								"Invoked method did not return a value"));

					}

					ACPI_EXCEPTION((AE_INFO, status,
							"GetPredicate Failed"));
					return_ACPI_STATUS(status);
				}

				status =
				    acpi_ps_next_parse_state(walk_state, op,
							     status);
			}

			acpi_ps_pop_scope(parser_state, &op,
					  &walk_state->arg_types,
					  &walk_state->arg_count);
			ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
					  "Popped scope, Op=%p\n", op));
		} else if (walk_state->prev_op) {

			/* We were in the middle of an op */

			op = walk_state->prev_op;
			walk_state->arg_types = walk_state->prev_arg_types;
		}
	}
#endif

	/* Iterative parsing loop, while there is more AML to process: */

	while ((parser_state->aml < parser_state->aml_end) || (op)) {
		aml_op_start = parser_state->aml;
		if (!op) {
			status =
			    acpi_ps_create_op(walk_state, aml_op_start, &op);
			if (ACPI_FAILURE(status)) {
				if (status == AE_CTRL_PARSE_CONTINUE) {
					continue;
				}

				if (status == AE_CTRL_PARSE_PENDING) {
					status = AE_OK;
				}

				status =
				    acpi_ps_complete_op(walk_state, &op,
							status);
				if (ACPI_FAILURE(status)) {
					return_ACPI_STATUS(status);
				}

				continue;
			}

			op->common.aml_offset = walk_state->aml_offset;

			if (walk_state->op_info) {
				ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
						  "Opcode %4.4X [%s] Op %p Aml %p AmlOffset %5.5X\n",
						  (u32) op->common.aml_opcode,
						  walk_state->op_info->name, op,
						  parser_state->aml,
						  op->common.aml_offset));
			}
		}

		/*
		 * Start arg_count at zero because we don't know if there are
		 * any args yet
		 */
		walk_state->arg_count = 0;

		/* Are there any arguments that must be processed? */

		if (walk_state->arg_types) {

			/* Get arguments */

			status =
			    acpi_ps_get_arguments(walk_state, aml_op_start, op);
			if (ACPI_FAILURE(status)) {
				status =
				    acpi_ps_complete_op(walk_state, &op,
							status);
				if (ACPI_FAILURE(status)) {
					return_ACPI_STATUS(status);
				}

				continue;
			}
		}

		/* Check for arguments that need to be processed */

		if (walk_state->arg_count) {
			/*
			 * There are arguments (complex ones), push Op and
			 * prepare for argument
			 */
			status = acpi_ps_push_scope(parser_state, op,
						    walk_state->arg_types,
						    walk_state->arg_count);
			if (ACPI_FAILURE(status)) {
				status =
				    acpi_ps_complete_op(walk_state, &op,
							status);
				if (ACPI_FAILURE(status)) {
					return_ACPI_STATUS(status);
				}

				continue;
			}

			op = NULL;
			continue;
		}

		/*
		 * All arguments have been processed -- Op is complete,
		 * prepare for next
		 */
		walk_state->op_info =
		    acpi_ps_get_opcode_info(op->common.aml_opcode);
		if (walk_state->op_info->flags & AML_NAMED) {
			if (acpi_gbl_depth) {
				acpi_gbl_depth--;
			}

			if (op->common.aml_opcode == AML_REGION_OP ||
			    op->common.aml_opcode == AML_DATA_REGION_OP) {
				/*
				 * Skip parsing of control method or opregion body,
				 * because we don't have enough info in the first pass
				 * to parse them correctly.
				 *
				 * Completed parsing an op_region declaration, we now
				 * know the length.
				 */
				op->named.length =
				    (u32) (parser_state->aml - op->named.data);
			}
		}

		if (walk_state->op_info->flags & AML_CREATE) {
			/*
			 * Backup to beginning of create_xXXfield declaration (1 for
			 * Opcode)
			 *
			 * body_length is unknown until we parse the body
			 */
			op->named.length =
			    (u32) (parser_state->aml - op->named.data);
		}

		if (op->common.aml_opcode == AML_BANK_FIELD_OP) {
			/*
			 * Backup to beginning of bank_field declaration
			 *
			 * body_length is unknown until we parse the body
			 */
			op->named.length =
			    (u32) (parser_state->aml - op->named.data);
		}

		/* This op complete, notify the dispatcher */

		if (walk_state->ascending_callback != NULL) {
			walk_state->op = op;
			walk_state->opcode = op->common.aml_opcode;

			status = walk_state->ascending_callback(walk_state);
			status =
			    acpi_ps_next_parse_state(walk_state, op, status);
			if (status == AE_CTRL_PENDING) {
				status = AE_OK;
			}
		}

		status = acpi_ps_complete_op(walk_state, &op, status);
		if (ACPI_FAILURE(status)) {
			return_ACPI_STATUS(status);
		}

	}			/* while parser_state->Aml */

	status = acpi_ps_complete_final_op(walk_state, op, status);
	return_ACPI_STATUS(status);
}