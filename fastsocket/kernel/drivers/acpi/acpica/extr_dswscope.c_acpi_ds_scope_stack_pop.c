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
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
struct TYPE_3__ {int /*<<< orphan*/  node; } ;
union acpi_generic_state {TYPE_2__ common; TYPE_1__ scope; } ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_walk_state {union acpi_generic_state* scope_info; scalar_t__ scope_depth; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_STACK_UNDERFLOW ; 
 int /*<<< orphan*/  acpi_ut_delete_generic_state (union acpi_generic_state*) ; 
 int /*<<< orphan*/  acpi_ut_get_node_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_get_type_name (int /*<<< orphan*/ ) ; 
 union acpi_generic_state* acpi_ut_pop_generic_state (union acpi_generic_state**) ; 
 int /*<<< orphan*/  ds_scope_stack_pop ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ds_scope_stack_pop(struct acpi_walk_state *walk_state)
{
	union acpi_generic_state *scope_info;
	union acpi_generic_state *new_scope_info;

	ACPI_FUNCTION_TRACE(ds_scope_stack_pop);

	/*
	 * Pop scope info object off the stack.
	 */
	scope_info = acpi_ut_pop_generic_state(&walk_state->scope_info);
	if (!scope_info) {
		return_ACPI_STATUS(AE_STACK_UNDERFLOW);
	}

	walk_state->scope_depth--;

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "[%.2d] Popped scope [%4.4s] (%s), New scope -> ",
			  (u32) walk_state->scope_depth,
			  acpi_ut_get_node_name(scope_info->scope.node),
			  acpi_ut_get_type_name(scope_info->common.value)));

	new_scope_info = walk_state->scope_info;
	if (new_scope_info) {
		ACPI_DEBUG_PRINT_RAW((ACPI_DB_EXEC,
				      "[%4.4s] (%s)\n",
				      acpi_ut_get_node_name(new_scope_info->
							    scope.node),
				      acpi_ut_get_type_name(new_scope_info->
							    common.value)));
	} else {
		ACPI_DEBUG_PRINT_RAW((ACPI_DB_EXEC, "[\\___] (ROOT)\n"));
	}

	acpi_ut_delete_generic_state(scope_info);
	return_ACPI_STATUS(AE_OK);
}