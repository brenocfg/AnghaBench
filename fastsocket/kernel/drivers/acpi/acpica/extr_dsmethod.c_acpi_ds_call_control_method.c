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
typedef  union acpi_parse_object {int dummy; } acpi_parse_object ;
struct TYPE_4__ {size_t param_count; int method_flags; scalar_t__ (* implementation ) (struct acpi_walk_state*) ;int /*<<< orphan*/  aml_length; int /*<<< orphan*/  aml_start; int /*<<< orphan*/  owner_id; } ;
union acpi_operand_object {TYPE_2__ method; } ;
typedef  size_t u32 ;
struct acpi_walk_state {size_t num_operands; int /*<<< orphan*/ ** operands; struct acpi_namespace_node* method_call_node; int /*<<< orphan*/  prev_op; } ;
struct acpi_thread_state {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ascii; } ;
struct acpi_namespace_node {TYPE_1__ name; } ;
struct acpi_evaluate_info {int /*<<< orphan*/ ** parameters; } ;
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 struct acpi_evaluate_info* ACPI_ALLOCATE_ZEROED (int) ; 
 int /*<<< orphan*/  ACPI_DB_DISPATCH ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FREE (struct acpi_evaluate_info*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  ACPI_IMODE_EXECUTE ; 
 scalar_t__ AE_CTRL_TERMINATE ; 
 scalar_t__ AE_NO_MEMORY ; 
 scalar_t__ AE_NULL_ENTRY ; 
 scalar_t__ AE_NULL_OBJECT ; 
 scalar_t__ AE_OK ; 
 int AML_METHOD_INTERNAL_ONLY ; 
 scalar_t__ acpi_ds_begin_method_execution (struct acpi_namespace_node*,union acpi_operand_object*,struct acpi_walk_state*) ; 
 struct acpi_walk_state* acpi_ds_create_walk_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *,union acpi_operand_object*,struct acpi_thread_state*) ; 
 int /*<<< orphan*/  acpi_ds_delete_walk_state (struct acpi_walk_state*) ; 
 scalar_t__ acpi_ds_init_aml_walk (struct acpi_walk_state*,int /*<<< orphan*/ *,struct acpi_namespace_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_evaluate_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ds_terminate_control_method (union acpi_operand_object*,struct acpi_walk_state*) ; 
 union acpi_operand_object* acpi_ns_get_attached_object (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ds_call_control_method ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 
 scalar_t__ stub1 (struct acpi_walk_state*) ; 

acpi_status
acpi_ds_call_control_method(struct acpi_thread_state *thread,
			    struct acpi_walk_state *this_walk_state,
			    union acpi_parse_object *op)
{
	acpi_status status;
	struct acpi_namespace_node *method_node;
	struct acpi_walk_state *next_walk_state = NULL;
	union acpi_operand_object *obj_desc;
	struct acpi_evaluate_info *info;
	u32 i;

	ACPI_FUNCTION_TRACE_PTR(ds_call_control_method, this_walk_state);

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "Calling method %p, currentstate=%p\n",
			  this_walk_state->prev_op, this_walk_state));

	/*
	 * Get the namespace entry for the control method we are about to call
	 */
	method_node = this_walk_state->method_call_node;
	if (!method_node) {
		return_ACPI_STATUS(AE_NULL_ENTRY);
	}

	obj_desc = acpi_ns_get_attached_object(method_node);
	if (!obj_desc) {
		return_ACPI_STATUS(AE_NULL_OBJECT);
	}

	/* Init for new method, possibly wait on method mutex */

	status = acpi_ds_begin_method_execution(method_node, obj_desc,
						this_walk_state);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Begin method parse/execution. Create a new walk state */

	next_walk_state = acpi_ds_create_walk_state(obj_desc->method.owner_id,
						    NULL, obj_desc, thread);
	if (!next_walk_state) {
		status = AE_NO_MEMORY;
		goto cleanup;
	}

	/*
	 * The resolved arguments were put on the previous walk state's operand
	 * stack. Operands on the previous walk state stack always
	 * start at index 0. Also, null terminate the list of arguments
	 */
	this_walk_state->operands[this_walk_state->num_operands] = NULL;

	/*
	 * Allocate and initialize the evaluation information block
	 * TBD: this is somewhat inefficient, should change interface to
	 * ds_init_aml_walk. For now, keeps this struct off the CPU stack
	 */
	info = ACPI_ALLOCATE_ZEROED(sizeof(struct acpi_evaluate_info));
	if (!info) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	info->parameters = &this_walk_state->operands[0];

	status = acpi_ds_init_aml_walk(next_walk_state, NULL, method_node,
				       obj_desc->method.aml_start,
				       obj_desc->method.aml_length, info,
				       ACPI_IMODE_EXECUTE);

	ACPI_FREE(info);
	if (ACPI_FAILURE(status)) {
		goto cleanup;
	}

	/*
	 * Delete the operands on the previous walkstate operand stack
	 * (they were copied to new objects)
	 */
	for (i = 0; i < obj_desc->method.param_count; i++) {
		acpi_ut_remove_reference(this_walk_state->operands[i]);
		this_walk_state->operands[i] = NULL;
	}

	/* Clear the operand stack */

	this_walk_state->num_operands = 0;

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "**** Begin nested execution of [%4.4s] **** WalkState=%p\n",
			  method_node->name.ascii, next_walk_state));

	/* Invoke an internal method if necessary */

	if (obj_desc->method.method_flags & AML_METHOD_INTERNAL_ONLY) {
		status = obj_desc->method.implementation(next_walk_state);
		if (status == AE_OK) {
			status = AE_CTRL_TERMINATE;
		}
	}

	return_ACPI_STATUS(status);

      cleanup:

	/* On error, we must terminate the method properly */

	acpi_ds_terminate_control_method(obj_desc, next_walk_state);
	if (next_walk_state) {
		acpi_ds_delete_walk_state(next_walk_state);
	}

	return_ACPI_STATUS(status);
}