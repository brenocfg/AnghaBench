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
typedef  union acpi_operand_object {int dummy; } acpi_operand_object ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_gbl_root_node ; 
 int /*<<< orphan*/  acpi_ns_delete_namespace_subtree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ns_detach_object (int /*<<< orphan*/ ) ; 
 union acpi_operand_object* acpi_ns_get_attached_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_terminate ; 
 int /*<<< orphan*/  return_VOID ; 

void acpi_ns_terminate(void)
{
	union acpi_operand_object *obj_desc;

	ACPI_FUNCTION_TRACE(ns_terminate);

	/*
	 * 1) Free the entire namespace -- all nodes and objects
	 *
	 * Delete all object descriptors attached to namepsace nodes
	 */
	acpi_ns_delete_namespace_subtree(acpi_gbl_root_node);

	/* Detach any objects attached to the root */

	obj_desc = acpi_ns_get_attached_object(acpi_gbl_root_node);
	if (obj_desc) {
		acpi_ns_detach_object(acpi_gbl_root_node);
	}

	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "Namespace freed\n"));
	return_VOID;
}