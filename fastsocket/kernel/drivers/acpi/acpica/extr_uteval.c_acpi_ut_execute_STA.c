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
struct TYPE_2__ {scalar_t__ value; } ;
union acpi_operand_object {TYPE_1__ integer; } ;
typedef  scalar_t__ u32 ;
struct acpi_namespace_node {int dummy; } ;
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BTYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_UINT32_MAX ; 
 scalar_t__ AE_NOT_FOUND ; 
 scalar_t__ AE_OK ; 
 int /*<<< orphan*/  METHOD_NAME__STA ; 
 scalar_t__ acpi_ut_evaluate_object (struct acpi_namespace_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union acpi_operand_object**) ; 
 int /*<<< orphan*/  acpi_ut_get_node_name (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 
 int /*<<< orphan*/  ut_execute_STA ; 

acpi_status
acpi_ut_execute_STA(struct acpi_namespace_node *device_node, u32 * flags)
{
	union acpi_operand_object *obj_desc;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ut_execute_STA);

	status = acpi_ut_evaluate_object(device_node, METHOD_NAME__STA,
					 ACPI_BTYPE_INTEGER, &obj_desc);
	if (ACPI_FAILURE(status)) {
		if (AE_NOT_FOUND == status) {
			ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
					  "_STA on %4.4s was not found, assuming device is present\n",
					  acpi_ut_get_node_name(device_node)));

			*flags = ACPI_UINT32_MAX;
			status = AE_OK;
		}

		return_ACPI_STATUS(status);
	}

	/* Extract the status flags */

	*flags = (u32) obj_desc->integer.value;

	/* On exit, we must delete the return object */

	acpi_ut_remove_reference(obj_desc);
	return_ACPI_STATUS(status);
}