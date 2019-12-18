#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ aml_opcode; TYPE_5__* parent; } ;
union acpi_parse_object {TYPE_6__ common; } ;
typedef  int /*<<< orphan*/  u8 ;
struct acpi_walk_state {TYPE_3__* control_state; int /*<<< orphan*/  result_obj; } ;
struct acpi_opcode_info {int class; } ;
struct TYPE_10__ {scalar_t__ aml_opcode; } ;
struct TYPE_11__ {TYPE_4__ common; } ;
struct TYPE_8__ {union acpi_parse_object* predicate_op; } ;
struct TYPE_7__ {int /*<<< orphan*/  state; } ;
struct TYPE_9__ {TYPE_2__ control; TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_CONTROL_PREDICATE_EXECUTING ; 
 int /*<<< orphan*/  ACPI_DB_DISPATCH ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_parse_object*) ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AML_BANK_FIELD_OP ; 
 scalar_t__ AML_BUFFER_OP ; 
#define  AML_CLASS_CONTROL 133 
#define  AML_CLASS_CREATE 132 
#define  AML_CLASS_NAMED_OBJECT 131 
 int AML_CLASS_UNKNOWN ; 
 scalar_t__ AML_DATA_REGION_OP ; 
#define  AML_IF_OP 130 
 scalar_t__ AML_INT_EVAL_SUBTREE_OP ; 
 scalar_t__ AML_PACKAGE_OP ; 
 scalar_t__ AML_REGION_OP ; 
#define  AML_RETURN_OP 129 
 scalar_t__ AML_SCOPE_OP ; 
 scalar_t__ AML_VAR_PACKAGE_OP ; 
#define  AML_WHILE_OP 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_ds_do_implicit_return (int /*<<< orphan*/ ,struct acpi_walk_state*,int /*<<< orphan*/ ) ; 
 struct acpi_opcode_info* acpi_ps_get_opcode_info (scalar_t__) ; 
 int /*<<< orphan*/  acpi_ps_get_opcode_name (scalar_t__) ; 
 int /*<<< orphan*/  ds_is_result_used ; 
 int /*<<< orphan*/  return_UINT8 (int /*<<< orphan*/ ) ; 

u8
acpi_ds_is_result_used(union acpi_parse_object * op,
		       struct acpi_walk_state * walk_state)
{
	const struct acpi_opcode_info *parent_info;

	ACPI_FUNCTION_TRACE_PTR(ds_is_result_used, op);

	/* Must have both an Op and a Result Object */

	if (!op) {
		ACPI_ERROR((AE_INFO, "Null Op"));
		return_UINT8(TRUE);
	}

	/*
	 * We know that this operator is not a
	 * Return() operator (would not come here.) The following code is the
	 * optional support for a so-called "implicit return". Some AML code
	 * assumes that the last value of the method is "implicitly" returned
	 * to the caller. Just save the last result as the return value.
	 * NOTE: this is optional because the ASL language does not actually
	 * support this behavior.
	 */
	(void)acpi_ds_do_implicit_return(walk_state->result_obj, walk_state,
					 TRUE);

	/*
	 * Now determine if the parent will use the result
	 *
	 * If there is no parent, or the parent is a scope_op, we are executing
	 * at the method level. An executing method typically has no parent,
	 * since each method is parsed separately.  A method invoked externally
	 * via execute_control_method has a scope_op as the parent.
	 */
	if ((!op->common.parent) ||
	    (op->common.parent->common.aml_opcode == AML_SCOPE_OP)) {

		/* No parent, the return value cannot possibly be used */

		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
				  "At Method level, result of [%s] not used\n",
				  acpi_ps_get_opcode_name(op->common.
							  aml_opcode)));
		return_UINT8(FALSE);
	}

	/* Get info on the parent. The root_op is AML_SCOPE */

	parent_info =
	    acpi_ps_get_opcode_info(op->common.parent->common.aml_opcode);
	if (parent_info->class == AML_CLASS_UNKNOWN) {
		ACPI_ERROR((AE_INFO, "Unknown parent opcode Op=%p", op));
		return_UINT8(FALSE);
	}

	/*
	 * Decide what to do with the result based on the parent.  If
	 * the parent opcode will not use the result, delete the object.
	 * Otherwise leave it as is, it will be deleted when it is used
	 * as an operand later.
	 */
	switch (parent_info->class) {
	case AML_CLASS_CONTROL:

		switch (op->common.parent->common.aml_opcode) {
		case AML_RETURN_OP:

			/* Never delete the return value associated with a return opcode */

			goto result_used;

		case AML_IF_OP:
		case AML_WHILE_OP:

			/*
			 * If we are executing the predicate AND this is the predicate op,
			 * we will use the return value
			 */
			if ((walk_state->control_state->common.state ==
			     ACPI_CONTROL_PREDICATE_EXECUTING)
			    && (walk_state->control_state->control.
				predicate_op == op)) {
				goto result_used;
			}
			break;

		default:
			/* Ignore other control opcodes */
			break;
		}

		/* The general control opcode returns no result */

		goto result_not_used;

	case AML_CLASS_CREATE:

		/*
		 * These opcodes allow term_arg(s) as operands and therefore
		 * the operands can be method calls.  The result is used.
		 */
		goto result_used;

	case AML_CLASS_NAMED_OBJECT:

		if ((op->common.parent->common.aml_opcode == AML_REGION_OP) ||
		    (op->common.parent->common.aml_opcode == AML_DATA_REGION_OP)
		    || (op->common.parent->common.aml_opcode == AML_PACKAGE_OP)
		    || (op->common.parent->common.aml_opcode ==
			AML_VAR_PACKAGE_OP)
		    || (op->common.parent->common.aml_opcode == AML_BUFFER_OP)
		    || (op->common.parent->common.aml_opcode ==
			AML_INT_EVAL_SUBTREE_OP)
		    || (op->common.parent->common.aml_opcode ==
			AML_BANK_FIELD_OP)) {
			/*
			 * These opcodes allow term_arg(s) as operands and therefore
			 * the operands can be method calls.  The result is used.
			 */
			goto result_used;
		}

		goto result_not_used;

	default:

		/*
		 * In all other cases. the parent will actually use the return
		 * object, so keep it.
		 */
		goto result_used;
	}

      result_used:
	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "Result of [%s] used by Parent [%s] Op=%p\n",
			  acpi_ps_get_opcode_name(op->common.aml_opcode),
			  acpi_ps_get_opcode_name(op->common.parent->common.
						  aml_opcode), op));

	return_UINT8(TRUE);

      result_not_used:
	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "Result of [%s] not used by Parent [%s] Op=%p\n",
			  acpi_ps_get_opcode_name(op->common.aml_opcode),
			  acpi_ps_get_opcode_name(op->common.parent->common.
						  aml_opcode), op));

	return_UINT8(FALSE);
}