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
typedef  int /*<<< orphan*/  u32 ;
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MTX_NAMESPACE ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_ALREADY_EXISTS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_ds_initialize_objects (int /*<<< orphan*/ ,struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ns_parse_table (int /*<<< orphan*/ ,struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_tb_allocate_owner_id (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_tb_is_table_loaded (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_tb_release_owner_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_tb_set_table_loaded_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_acquire_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_release_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_load_table ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ns_load_table(u32 table_index, struct acpi_namespace_node *node)
{
	acpi_status status;

	ACPI_FUNCTION_TRACE(ns_load_table);

	/*
	 * Parse the table and load the namespace with all named
	 * objects found within.  Control methods are NOT parsed
	 * at this time.  In fact, the control methods cannot be
	 * parsed until the entire namespace is loaded, because
	 * if a control method makes a forward reference (call)
	 * to another control method, we can't continue parsing
	 * because we don't know how many arguments to parse next!
	 */
	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* If table already loaded into namespace, just return */

	if (acpi_tb_is_table_loaded(table_index)) {
		status = AE_ALREADY_EXISTS;
		goto unlock;
	}

	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "**** Loading table into namespace ****\n"));

	status = acpi_tb_allocate_owner_id(table_index);
	if (ACPI_FAILURE(status)) {
		goto unlock;
	}

	status = acpi_ns_parse_table(table_index, node);
	if (ACPI_SUCCESS(status)) {
		acpi_tb_set_table_loaded_flag(table_index, TRUE);
	} else {
		(void)acpi_tb_release_owner_id(table_index);
	}

      unlock:
	(void)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);

	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/*
	 * Now we can parse the control methods.  We always parse
	 * them here for a sanity check, and if configured for
	 * just-in-time parsing, we delete the control method
	 * parse trees.
	 */
	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "**** Begin Table Method Parsing and Object Initialization\n"));

	status = acpi_ds_initialize_objects(table_index, node);

	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "**** Completed Table Method Parsing and Object Initialization\n"));

	return_ACPI_STATUS(status);
}