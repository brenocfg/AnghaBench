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
struct TYPE_4__ {size_t value; } ;
struct TYPE_3__ {size_t count; union acpi_operand_object** elements; } ;
union acpi_operand_object {TYPE_2__ integer; TYPE_1__ package; } ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_walk_state {int opcode; union acpi_operand_object* result_obj; union acpi_operand_object** operands; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  size_t acpi_integer ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (size_t) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_STR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ACPI_INTEGER_MAX ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  AE_AML_BAD_OPCODE ; 
 int /*<<< orphan*/  AE_AML_OPERAND_VALUE ; 
 int /*<<< orphan*/  AE_AML_PACKAGE_LIMIT ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
#define  AML_LOAD_TABLE_OP 129 
#define  AML_MATCH_OP 128 
 size_t MAX_MATCH_OPERATOR ; 
 int /*<<< orphan*/  acpi_ex_do_match (int /*<<< orphan*/ ,union acpi_operand_object*,union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ex_load_table_op (struct acpi_walk_state*,union acpi_operand_object**) ; 
 int /*<<< orphan*/  acpi_ps_get_opcode_name (int) ; 
 union acpi_operand_object* acpi_ut_create_internal_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ex_opcode_6A_0T_1R ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ex_opcode_6A_0T_1R(struct acpi_walk_state * walk_state)
{
	union acpi_operand_object **operand = &walk_state->operands[0];
	union acpi_operand_object *return_desc = NULL;
	acpi_status status = AE_OK;
	acpi_integer index;
	union acpi_operand_object *this_element;

	ACPI_FUNCTION_TRACE_STR(ex_opcode_6A_0T_1R,
				acpi_ps_get_opcode_name(walk_state->opcode));

	switch (walk_state->opcode) {
	case AML_MATCH_OP:
		/*
		 * Match (search_pkg[0], match_op1[1], match_obj1[2],
		 *                      match_op2[3], match_obj2[4], start_index[5])
		 */

		/* Validate both Match Term Operators (MTR, MEQ, etc.) */

		if ((operand[1]->integer.value > MAX_MATCH_OPERATOR) ||
		    (operand[3]->integer.value > MAX_MATCH_OPERATOR)) {
			ACPI_ERROR((AE_INFO, "Match operator out of range"));
			status = AE_AML_OPERAND_VALUE;
			goto cleanup;
		}

		/* Get the package start_index, validate against the package length */

		index = operand[5]->integer.value;
		if (index >= operand[0]->package.count) {
			ACPI_ERROR((AE_INFO,
				    "Index (%X%8.8X) beyond package end (%X)",
				    ACPI_FORMAT_UINT64(index),
				    operand[0]->package.count));
			status = AE_AML_PACKAGE_LIMIT;
			goto cleanup;
		}

		/* Create an integer for the return value */

		return_desc = acpi_ut_create_internal_object(ACPI_TYPE_INTEGER);
		if (!return_desc) {
			status = AE_NO_MEMORY;
			goto cleanup;

		}

		/* Default return value if no match found */

		return_desc->integer.value = ACPI_INTEGER_MAX;

		/*
		 * Examine each element until a match is found. Both match conditions
		 * must be satisfied for a match to occur. Within the loop,
		 * "continue" signifies that the current element does not match
		 * and the next should be examined.
		 *
		 * Upon finding a match, the loop will terminate via "break" at
		 * the bottom.  If it terminates "normally", match_value will be
		 * ACPI_INTEGER_MAX (Ones) (its initial value) indicating that no
		 * match was found.
		 */
		for (; index < operand[0]->package.count; index++) {

			/* Get the current package element */

			this_element = operand[0]->package.elements[index];

			/* Treat any uninitialized (NULL) elements as non-matching */

			if (!this_element) {
				continue;
			}

			/*
			 * Both match conditions must be satisfied. Execution of a continue
			 * (proceed to next iteration of enclosing for loop) signifies a
			 * non-match.
			 */
			if (!acpi_ex_do_match((u32) operand[1]->integer.value,
					      this_element, operand[2])) {
				continue;
			}

			if (!acpi_ex_do_match((u32) operand[3]->integer.value,
					      this_element, operand[4])) {
				continue;
			}

			/* Match found: Index is the return value */

			return_desc->integer.value = index;
			break;
		}
		break;

	case AML_LOAD_TABLE_OP:

		status = acpi_ex_load_table_op(walk_state, &return_desc);
		break;

	default:

		ACPI_ERROR((AE_INFO, "Unknown AML opcode %X",
			    walk_state->opcode));
		status = AE_AML_BAD_OPCODE;
		goto cleanup;
	}

      cleanup:

	/* Delete return object on error */

	if (ACPI_FAILURE(status)) {
		acpi_ut_remove_reference(return_desc);
	}

	/* Save return object on success */

	else {
		walk_state->result_obj = return_desc;
	}

	return_ACPI_STATUS(status);
}