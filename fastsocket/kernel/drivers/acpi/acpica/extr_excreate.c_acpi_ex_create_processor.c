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
struct TYPE_4__ {scalar_t__ value; } ;
struct TYPE_3__ {scalar_t__ address; void* length; void* proc_id; } ;
union acpi_operand_object {TYPE_2__ integer; TYPE_1__ processor; } ;
typedef  void* u8 ;
struct acpi_walk_state {union acpi_operand_object** operands; } ;
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_io_address ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  ACPI_TYPE_PROCESSOR ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  acpi_ns_attach_object (struct acpi_namespace_node*,union acpi_operand_object*,int /*<<< orphan*/ ) ; 
 union acpi_operand_object* acpi_ut_create_internal_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ex_create_processor ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ex_create_processor(struct acpi_walk_state *walk_state)
{
	union acpi_operand_object **operand = &walk_state->operands[0];
	union acpi_operand_object *obj_desc;
	acpi_status status;

	ACPI_FUNCTION_TRACE_PTR(ex_create_processor, walk_state);

	/* Create the processor object */

	obj_desc = acpi_ut_create_internal_object(ACPI_TYPE_PROCESSOR);
	if (!obj_desc) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	/* Initialize the processor object from the operands */

	obj_desc->processor.proc_id = (u8) operand[1]->integer.value;
	obj_desc->processor.length = (u8) operand[3]->integer.value;
	obj_desc->processor.address =
	    (acpi_io_address) operand[2]->integer.value;

	/* Install the processor object in the parent Node */

	status = acpi_ns_attach_object((struct acpi_namespace_node *)operand[0],
				       obj_desc, ACPI_TYPE_PROCESSOR);

	/* Remove local reference to the object */

	acpi_ut_remove_reference(obj_desc);
	return_ACPI_STATUS(status);
}