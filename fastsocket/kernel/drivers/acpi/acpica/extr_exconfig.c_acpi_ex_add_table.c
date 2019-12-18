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
struct TYPE_4__ {int /*<<< orphan*/  value; int /*<<< orphan*/  class; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
union acpi_operand_object {TYPE_2__ reference; TYPE_1__ common; } ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_REFCLASS_TABLE ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_REFERENCE ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  acpi_ex_enter_interpreter () ; 
 int /*<<< orphan*/  acpi_ex_exit_interpreter () ; 
 int /*<<< orphan*/  acpi_ns_exec_module_code_list () ; 
 int /*<<< orphan*/  acpi_ns_load_table (int /*<<< orphan*/ ,struct acpi_namespace_node*) ; 
 union acpi_operand_object* acpi_ut_create_internal_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ex_add_table ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status
acpi_ex_add_table(u32 table_index,
		  struct acpi_namespace_node *parent_node,
		  union acpi_operand_object **ddb_handle)
{
	acpi_status status;
	union acpi_operand_object *obj_desc;

	ACPI_FUNCTION_TRACE(ex_add_table);

	/* Create an object to be the table handle */

	obj_desc = acpi_ut_create_internal_object(ACPI_TYPE_LOCAL_REFERENCE);
	if (!obj_desc) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	/* Init the table handle */

	obj_desc->common.flags |= AOPOBJ_DATA_VALID;
	obj_desc->reference.class = ACPI_REFCLASS_TABLE;
	*ddb_handle = obj_desc;

	/* Install the new table into the local data structures */

	obj_desc->reference.value = table_index;

	/* Add the table to the namespace */

	status = acpi_ns_load_table(table_index, parent_node);
	if (ACPI_FAILURE(status)) {
		acpi_ut_remove_reference(obj_desc);
		*ddb_handle = NULL;
		return_ACPI_STATUS(status);
	}

	/* Execute any module-level code that was found in the table */

	acpi_ex_exit_interpreter();
	acpi_ns_exec_module_code_list();
	acpi_ex_enter_interpreter();

	return_ACPI_STATUS(status);
}