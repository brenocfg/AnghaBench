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
 int /*<<< orphan*/  ACPI_DB_PARSE ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_IMODE_LOAD_PASS1 ; 
 int /*<<< orphan*/  ACPI_IMODE_LOAD_PASS2 ; 
 int /*<<< orphan*/  acpi_ns_one_complete_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  ns_parse_table ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ns_parse_table(u32 table_index, struct acpi_namespace_node *start_node)
{
	acpi_status status;

	ACPI_FUNCTION_TRACE(ns_parse_table);

	/*
	 * AML Parse, pass 1
	 *
	 * In this pass, we load most of the namespace.  Control methods
	 * are not parsed until later.  A parse tree is not created.  Instead,
	 * each Parser Op subtree is deleted when it is finished.  This saves
	 * a great deal of memory, and allows a small cache of parse objects
	 * to service the entire parse.  The second pass of the parse then
	 * performs another complete parse of the AML.
	 */
	ACPI_DEBUG_PRINT((ACPI_DB_PARSE, "**** Start pass 1\n"));
	status = acpi_ns_one_complete_parse(ACPI_IMODE_LOAD_PASS1,
					    table_index, start_node);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/*
	 * AML Parse, pass 2
	 *
	 * In this pass, we resolve forward references and other things
	 * that could not be completed during the first pass.
	 * Another complete parse of the AML is performed, but the
	 * overhead of this is compensated for by the fact that the
	 * parse objects are all cached.
	 */
	ACPI_DEBUG_PRINT((ACPI_DB_PARSE, "**** Start pass 2\n"));
	status = acpi_ns_one_complete_parse(ACPI_IMODE_LOAD_PASS2,
					    table_index, start_node);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	return_ACPI_STATUS(status);
}