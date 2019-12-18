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
struct TYPE_4__ {int /*<<< orphan*/  aml_start; int /*<<< orphan*/  aml_length; } ;
struct TYPE_6__ {struct acpi_namespace_node* node; } ;
struct TYPE_5__ {int flags; } ;
union acpi_operand_object {TYPE_1__ extra; TYPE_3__ buffer_field; TYPE_2__ common; } ;
struct acpi_namespace_node {int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_EXEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
 int /*<<< orphan*/  ACPI_TYPE_BUFFER_FIELD ; 
 int /*<<< orphan*/  AE_OK ; 
 int AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  acpi_ds_execute_arguments (struct acpi_namespace_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 union acpi_operand_object* acpi_ns_get_secondary_object (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_display_init_pathname (int /*<<< orphan*/ ,struct acpi_namespace_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_get_node_name (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  ds_get_buffer_field_arguments ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ds_get_buffer_field_arguments(union acpi_operand_object *obj_desc)
{
	union acpi_operand_object *extra_desc;
	struct acpi_namespace_node *node;
	acpi_status status;

	ACPI_FUNCTION_TRACE_PTR(ds_get_buffer_field_arguments, obj_desc);

	if (obj_desc->common.flags & AOPOBJ_DATA_VALID) {
		return_ACPI_STATUS(AE_OK);
	}

	/* Get the AML pointer (method object) and buffer_field node */

	extra_desc = acpi_ns_get_secondary_object(obj_desc);
	node = obj_desc->buffer_field.node;

	ACPI_DEBUG_EXEC(acpi_ut_display_init_pathname
			(ACPI_TYPE_BUFFER_FIELD, node, NULL));
	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "[%4.4s] BufferField Arg Init\n",
			  acpi_ut_get_node_name(node)));

	/* Execute the AML code for the term_arg arguments */

	status = acpi_ds_execute_arguments(node, node->parent,
					   extra_desc->extra.aml_length,
					   extra_desc->extra.aml_start);
	return_ACPI_STATUS(status);
}