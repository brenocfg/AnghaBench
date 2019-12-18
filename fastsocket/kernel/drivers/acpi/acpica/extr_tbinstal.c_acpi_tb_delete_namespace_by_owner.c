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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_owner_id ;
struct TYPE_4__ {size_t count; TYPE_1__* tables; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner_id; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MTX_INTERPRETER ; 
 int /*<<< orphan*/  ACPI_MTX_TABLES ; 
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 int /*<<< orphan*/  acpi_gbl_namespace_rw_lock ; 
 TYPE_2__ acpi_gbl_root_table_list ; 
 int /*<<< orphan*/  acpi_ns_delete_namespace_by_owner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_acquire_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_acquire_write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_release_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_release_write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_delete_namespace_by_owner ; 

acpi_status acpi_tb_delete_namespace_by_owner(u32 table_index)
{
	acpi_owner_id owner_id;
	acpi_status status;

	ACPI_FUNCTION_TRACE(tb_delete_namespace_by_owner);

	status = acpi_ut_acquire_mutex(ACPI_MTX_TABLES);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	if (table_index >= acpi_gbl_root_table_list.count) {

		/* The table index does not exist */

		(void)acpi_ut_release_mutex(ACPI_MTX_TABLES);
		return_ACPI_STATUS(AE_NOT_EXIST);
	}

	/* Get the owner ID for this table, used to delete namespace nodes */

	owner_id = acpi_gbl_root_table_list.tables[table_index].owner_id;
	(void)acpi_ut_release_mutex(ACPI_MTX_TABLES);

	/*
	 * Need to acquire the namespace writer lock to prevent interference
	 * with any concurrent namespace walks. The interpreter must be
	 * released during the deletion since the acquisition of the deletion
	 * lock may block, and also since the execution of a namespace walk
	 * must be allowed to use the interpreter.
	 */
	(void)acpi_ut_release_mutex(ACPI_MTX_INTERPRETER);
	status = acpi_ut_acquire_write_lock(&acpi_gbl_namespace_rw_lock);

	acpi_ns_delete_namespace_by_owner(owner_id);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	acpi_ut_release_write_lock(&acpi_gbl_namespace_rw_lock);

	status = acpi_ut_acquire_mutex(ACPI_MTX_INTERPRETER);
	return_ACPI_STATUS(status);
}