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
struct TYPE_4__ {int* aml_start; int method_flags; int param_count; int sync_level; int /*<<< orphan*/  aml_length; } ;
struct TYPE_3__ {scalar_t__ value; } ;
union acpi_operand_object {TYPE_2__ method; TYPE_1__ integer; } ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_walk_state {union acpi_operand_object** operands; } ;
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  ACPI_TYPE_METHOD ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int AML_METHOD_ARG_COUNT ; 
 int AML_METHOD_SERIALIZED ; 
 int AML_METHOD_SYNC_LEVEL ; 
 int /*<<< orphan*/  acpi_ns_attach_object (struct acpi_namespace_node*,union acpi_operand_object*,int /*<<< orphan*/ ) ; 
 union acpi_operand_object* acpi_ut_create_internal_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ex_create_method ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_create_method(u8 * aml_start,
		      u32 aml_length, struct acpi_walk_state *walk_state)
{
	union acpi_operand_object **operand = &walk_state->operands[0];
	union acpi_operand_object *obj_desc;
	acpi_status status;
	u8 method_flags;

	ACPI_FUNCTION_TRACE_PTR(ex_create_method, walk_state);

	/* Create a new method object */

	obj_desc = acpi_ut_create_internal_object(ACPI_TYPE_METHOD);
	if (!obj_desc) {
		status = AE_NO_MEMORY;
		goto exit;
	}

	/* Save the method's AML pointer and length  */

	obj_desc->method.aml_start = aml_start;
	obj_desc->method.aml_length = aml_length;

	/*
	 * Disassemble the method flags. Split off the Arg Count
	 * for efficiency
	 */
	method_flags = (u8) operand[1]->integer.value;

	obj_desc->method.method_flags =
	    (u8) (method_flags & ~AML_METHOD_ARG_COUNT);
	obj_desc->method.param_count =
	    (u8) (method_flags & AML_METHOD_ARG_COUNT);

	/*
	 * Get the sync_level. If method is serialized, a mutex will be
	 * created for this method when it is parsed.
	 */
	if (method_flags & AML_METHOD_SERIALIZED) {
		/*
		 * ACPI 1.0: sync_level = 0
		 * ACPI 2.0: sync_level = sync_level in method declaration
		 */
		obj_desc->method.sync_level = (u8)
		    ((method_flags & AML_METHOD_SYNC_LEVEL) >> 4);
	}

	/* Attach the new object to the method Node */

	status = acpi_ns_attach_object((struct acpi_namespace_node *)operand[0],
				       obj_desc, ACPI_TYPE_METHOD);

	/* Remove local reference to the object */

	acpi_ut_remove_reference(obj_desc);

      exit:
	/* Remove a reference to the operand */

	acpi_ut_remove_reference(operand[1]);
	return_ACPI_STATUS(status);
}