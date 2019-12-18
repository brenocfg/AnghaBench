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
typedef  union acpi_parse_object {int dummy; } acpi_parse_object ;
typedef  union acpi_operand_object {int dummy; } acpi_operand_object ;
struct acpi_walk_state {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  acpi_ds_is_result_used (union acpi_parse_object*,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ds_result_pop (union acpi_operand_object**,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ds_delete_result_if_not_used ; 
 int /*<<< orphan*/  return_VOID ; 

void
acpi_ds_delete_result_if_not_used(union acpi_parse_object *op,
				  union acpi_operand_object *result_obj,
				  struct acpi_walk_state *walk_state)
{
	union acpi_operand_object *obj_desc;
	acpi_status status;

	ACPI_FUNCTION_TRACE_PTR(ds_delete_result_if_not_used, result_obj);

	if (!op) {
		ACPI_ERROR((AE_INFO, "Null Op"));
		return_VOID;
	}

	if (!result_obj) {
		return_VOID;
	}

	if (!acpi_ds_is_result_used(op, walk_state)) {

		/* Must pop the result stack (obj_desc should be equal to result_obj) */

		status = acpi_ds_result_pop(&obj_desc, walk_state);
		if (ACPI_SUCCESS(status)) {
			acpi_ut_remove_reference(result_obj);
		}
	}

	return_VOID;
}