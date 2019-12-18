#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  union acpi_operand_object {int dummy; } acpi_operand_object ;
struct acpi_walk_state {scalar_t__ num_operands; size_t operand_index; void** operands; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_OBJ_NUM_OPERANDS ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_STACK_OVERFLOW ; 
 int /*<<< orphan*/  acpi_ut_get_object_type_name (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ds_obj_stack_push ; 

acpi_status
acpi_ds_obj_stack_push(void *object, struct acpi_walk_state * walk_state)
{
	ACPI_FUNCTION_NAME(ds_obj_stack_push);

	/* Check for stack overflow */

	if (walk_state->num_operands >= ACPI_OBJ_NUM_OPERANDS) {
		ACPI_ERROR((AE_INFO,
			    "Object stack overflow! Obj=%p State=%p #Ops=%X",
			    object, walk_state, walk_state->num_operands));
		return (AE_STACK_OVERFLOW);
	}

	/* Put the object onto the stack */

	walk_state->operands[walk_state->operand_index] = object;
	walk_state->num_operands++;

	/* For the usual order of filling the operand stack */

	walk_state->operand_index++;

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Obj=%p [%s] State=%p #Ops=%X\n",
			  object,
			  acpi_ut_get_object_type_name((union
							acpi_operand_object *)
						       object), walk_state,
			  walk_state->num_operands));

	return (AE_OK);
}