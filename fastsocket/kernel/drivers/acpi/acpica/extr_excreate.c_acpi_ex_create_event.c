#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  os_semaphore; } ;
union acpi_operand_object {TYPE_1__ event; } ;
struct acpi_walk_state {scalar_t__* operands; } ;
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_NO_UNIT_LIMIT ; 
 int /*<<< orphan*/  ACPI_TYPE_EVENT ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  acpi_ns_attach_object (struct acpi_namespace_node*,union acpi_operand_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_create_semaphore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 union acpi_operand_object* acpi_ut_create_internal_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ex_create_event ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ex_create_event(struct acpi_walk_state *walk_state)
{
	acpi_status status;
	union acpi_operand_object *obj_desc;

	ACPI_FUNCTION_TRACE(ex_create_event);

	obj_desc = acpi_ut_create_internal_object(ACPI_TYPE_EVENT);
	if (!obj_desc) {
		status = AE_NO_MEMORY;
		goto cleanup;
	}

	/*
	 * Create the actual OS semaphore, with zero initial units -- meaning
	 * that the event is created in an unsignalled state
	 */
	status = acpi_os_create_semaphore(ACPI_NO_UNIT_LIMIT, 0,
					  &obj_desc->event.os_semaphore);
	if (ACPI_FAILURE(status)) {
		goto cleanup;
	}

	/* Attach object to the Node */

	status =
	    acpi_ns_attach_object((struct acpi_namespace_node *)walk_state->
				  operands[0], obj_desc, ACPI_TYPE_EVENT);

      cleanup:
	/*
	 * Remove local reference to the object (on error, will cause deletion
	 * of both object and semaphore if present.)
	 */
	acpi_ut_remove_reference(obj_desc);
	return_ACPI_STATUS(status);
}