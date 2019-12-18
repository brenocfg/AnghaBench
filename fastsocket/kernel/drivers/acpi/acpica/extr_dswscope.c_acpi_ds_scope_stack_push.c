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
struct TYPE_4__ {scalar_t__ value; int /*<<< orphan*/  descriptor_type; } ;
struct TYPE_3__ {struct acpi_namespace_node* node; } ;
union acpi_generic_state {TYPE_2__ common; TYPE_1__ scope; } ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct acpi_walk_state {union acpi_generic_state* scope_info; scalar_t__ scope_depth; } ;
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_object_type ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DESC_TYPE_STATE_WSCOPE ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 union acpi_generic_state* acpi_ut_create_generic_state () ; 
 int /*<<< orphan*/  acpi_ut_get_node_name (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ut_get_type_name (scalar_t__) ; 
 int /*<<< orphan*/  acpi_ut_push_generic_state (union acpi_generic_state**,union acpi_generic_state*) ; 
 int /*<<< orphan*/  acpi_ut_valid_object_type (scalar_t__) ; 
 int /*<<< orphan*/  ds_scope_stack_push ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ds_scope_stack_push(struct acpi_namespace_node *node,
			 acpi_object_type type,
			 struct acpi_walk_state *walk_state)
{
	union acpi_generic_state *scope_info;
	union acpi_generic_state *old_scope_info;

	ACPI_FUNCTION_TRACE(ds_scope_stack_push);

	if (!node) {

		/* Invalid scope   */

		ACPI_ERROR((AE_INFO, "Null scope parameter"));
		return_ACPI_STATUS(AE_BAD_PARAMETER);
	}

	/* Make sure object type is valid */

	if (!acpi_ut_valid_object_type(type)) {
		ACPI_WARNING((AE_INFO, "Invalid object type: 0x%X", type));
	}

	/* Allocate a new scope object */

	scope_info = acpi_ut_create_generic_state();
	if (!scope_info) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	/* Init new scope object */

	scope_info->common.descriptor_type = ACPI_DESC_TYPE_STATE_WSCOPE;
	scope_info->scope.node = node;
	scope_info->common.value = (u16) type;

	walk_state->scope_depth++;

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "[%.2d] Pushed scope ",
			  (u32) walk_state->scope_depth));

	old_scope_info = walk_state->scope_info;
	if (old_scope_info) {
		ACPI_DEBUG_PRINT_RAW((ACPI_DB_EXEC,
				      "[%4.4s] (%s)",
				      acpi_ut_get_node_name(old_scope_info->
							    scope.node),
				      acpi_ut_get_type_name(old_scope_info->
							    common.value)));
	} else {
		ACPI_DEBUG_PRINT_RAW((ACPI_DB_EXEC, "[\\___] (%s)", "ROOT"));
	}

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_EXEC,
			      ", New scope -> [%4.4s] (%s)\n",
			      acpi_ut_get_node_name(scope_info->scope.node),
			      acpi_ut_get_type_name(scope_info->common.value)));

	/* Push new scope object onto stack */

	acpi_ut_push_generic_state(&walk_state->scope_info, scope_info);
	return_ACPI_STATUS(AE_OK);
}