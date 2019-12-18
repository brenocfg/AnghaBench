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
struct TYPE_4__ {scalar_t__ type; int flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
union acpi_operand_object {TYPE_2__ common; TYPE_1__ reference; } ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_table_header {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_DESC_TYPE_OPERAND ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (union acpi_operand_object*) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TABLE_EVENT_UNLOAD ; 
 scalar_t__ ACPI_TYPE_LOCAL_REFERENCE ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 int /*<<< orphan*/  AE_OK ; 
 int AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  acpi_gbl_table_handler (int /*<<< orphan*/ ,struct acpi_table_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_gbl_table_handler_context ; 
 int /*<<< orphan*/  acpi_get_table_by_index (int /*<<< orphan*/ ,struct acpi_table_header**) ; 
 int /*<<< orphan*/  acpi_tb_delete_namespace_by_owner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_tb_is_table_loaded (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_tb_release_owner_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_tb_set_table_loaded_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_unload_table ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ex_unload_table(union acpi_operand_object *ddb_handle)
{
	acpi_status status = AE_OK;
	union acpi_operand_object *table_desc = ddb_handle;
	u32 table_index;
	struct acpi_table_header *table;

	ACPI_FUNCTION_TRACE(ex_unload_table);

	/*
	 * Validate the handle
	 * Although the handle is partially validated in acpi_ex_reconfiguration()
	 * when it calls acpi_ex_resolve_operands(), the handle is more completely
	 * validated here.
	 *
	 * Handle must be a valid operand object of type reference. Also, the
	 * ddb_handle must still be marked valid (table has not been previously
	 * unloaded)
	 */
	if ((!ddb_handle) ||
	    (ACPI_GET_DESCRIPTOR_TYPE(ddb_handle) != ACPI_DESC_TYPE_OPERAND) ||
	    (ddb_handle->common.type != ACPI_TYPE_LOCAL_REFERENCE) ||
	    (!(ddb_handle->common.flags & AOPOBJ_DATA_VALID))) {
		return_ACPI_STATUS(AE_BAD_PARAMETER);
	}

	/* Get the table index from the ddb_handle */

	table_index = table_desc->reference.value;

	/* Ensure the table is still loaded */

	if (!acpi_tb_is_table_loaded(table_index)) {
		return_ACPI_STATUS(AE_NOT_EXIST);
	}

	/* Invoke table handler if present */

	if (acpi_gbl_table_handler) {
		status = acpi_get_table_by_index(table_index, &table);
		if (ACPI_SUCCESS(status)) {
			(void)acpi_gbl_table_handler(ACPI_TABLE_EVENT_UNLOAD,
						     table,
						     acpi_gbl_table_handler_context);
		}
	}

	/* Delete the portion of the namespace owned by this table */

	status = acpi_tb_delete_namespace_by_owner(table_index);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	(void)acpi_tb_release_owner_id(table_index);
	acpi_tb_set_table_loaded_flag(table_index, FALSE);

	/*
	 * Invalidate the handle. We do this because the handle may be stored
	 * in a named object and may not be actually deleted until much later.
	 */
	ddb_handle->common.flags &= ~AOPOBJ_DATA_VALID;
	return_ACPI_STATUS(AE_OK);
}