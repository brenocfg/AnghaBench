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
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
struct TYPE_5__ {int /*<<< orphan*/  space_id; } ;
struct TYPE_4__ {int /*<<< orphan*/ * method_REG; } ;
union acpi_operand_object {TYPE_3__ integer; TYPE_2__ region; TYPE_1__ extra; } ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_evaluate_info {int /*<<< orphan*/ * prefix_node; int /*<<< orphan*/  flags; union acpi_operand_object** parameters; int /*<<< orphan*/ * pathname; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 struct acpi_evaluate_info* ACPI_ALLOCATE_ZEROED (int) ; 
 int /*<<< orphan*/  ACPI_DEBUG_EXEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (struct acpi_evaluate_info*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_IGNORE_RETURN_VALUE ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_TYPE_METHOD ; 
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ns_evaluate (struct acpi_evaluate_info*) ; 
 union acpi_operand_object* acpi_ns_get_secondary_object (union acpi_operand_object*) ; 
 union acpi_operand_object* acpi_ut_create_internal_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_display_init_pathname (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ev_execute_reg_method ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ev_execute_reg_method(union acpi_operand_object *region_obj, u32 function)
{
	struct acpi_evaluate_info *info;
	union acpi_operand_object *args[3];
	union acpi_operand_object *region_obj2;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ev_execute_reg_method);

	region_obj2 = acpi_ns_get_secondary_object(region_obj);
	if (!region_obj2) {
		return_ACPI_STATUS(AE_NOT_EXIST);
	}

	if (region_obj2->extra.method_REG == NULL) {
		return_ACPI_STATUS(AE_OK);
	}

	/* Allocate and initialize the evaluation information block */

	info = ACPI_ALLOCATE_ZEROED(sizeof(struct acpi_evaluate_info));
	if (!info) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	info->prefix_node = region_obj2->extra.method_REG;
	info->pathname = NULL;
	info->parameters = args;
	info->flags = ACPI_IGNORE_RETURN_VALUE;

	/*
	 * The _REG method has two arguments:
	 *
	 * Arg0 - Integer:
	 *  Operation region space ID Same value as region_obj->Region.space_id
	 *
	 * Arg1 - Integer:
	 *  connection status 1 for connecting the handler, 0 for disconnecting
	 *  the handler (Passed as a parameter)
	 */
	args[0] = acpi_ut_create_internal_object(ACPI_TYPE_INTEGER);
	if (!args[0]) {
		status = AE_NO_MEMORY;
		goto cleanup1;
	}

	args[1] = acpi_ut_create_internal_object(ACPI_TYPE_INTEGER);
	if (!args[1]) {
		status = AE_NO_MEMORY;
		goto cleanup2;
	}

	/* Setup the parameter objects */

	args[0]->integer.value = region_obj->region.space_id;
	args[1]->integer.value = function;
	args[2] = NULL;

	/* Execute the method, no return value */

	ACPI_DEBUG_EXEC(acpi_ut_display_init_pathname
			(ACPI_TYPE_METHOD, info->prefix_node, NULL));

	status = acpi_ns_evaluate(info);
	acpi_ut_remove_reference(args[1]);

      cleanup2:
	acpi_ut_remove_reference(args[0]);

      cleanup1:
	ACPI_FREE(info);
	return_ACPI_STATUS(status);
}