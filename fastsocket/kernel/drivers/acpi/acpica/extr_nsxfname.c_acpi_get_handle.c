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
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/ * acpi_string ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int /*<<< orphan*/  ACPI_NS_NO_UPSEARCH ; 
 int /*<<< orphan*/  ACPI_NS_ROOT_PATH ; 
 int /*<<< orphan*/  ACPI_STRCMP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 struct acpi_namespace_node* acpi_gbl_root_node ; 
 scalar_t__ acpi_ns_convert_entry_to_handle (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ns_get_node (struct acpi_namespace_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct acpi_namespace_node**) ; 
 struct acpi_namespace_node* acpi_ns_map_handle_to_node (scalar_t__) ; 
 scalar_t__ acpi_ns_valid_root_prefix (int /*<<< orphan*/ ) ; 

acpi_status
acpi_get_handle(acpi_handle parent,
		acpi_string pathname, acpi_handle * ret_handle)
{
	acpi_status status;
	struct acpi_namespace_node *node = NULL;
	struct acpi_namespace_node *prefix_node = NULL;

	ACPI_FUNCTION_ENTRY();

	/* Parameter Validation */

	if (!ret_handle || !pathname) {
		return (AE_BAD_PARAMETER);
	}

	/* Convert a parent handle to a prefix node */

	if (parent) {
		prefix_node = acpi_ns_map_handle_to_node(parent);
		if (!prefix_node) {
			return (AE_BAD_PARAMETER);
		}
	}

	/*
	 * Valid cases are:
	 * 1) Fully qualified pathname
	 * 2) Parent + Relative pathname
	 *
	 * Error for <null Parent + relative path>
	 */
	if (acpi_ns_valid_root_prefix(pathname[0])) {

		/* Pathname is fully qualified (starts with '\') */

		/* Special case for root-only, since we can't search for it */

		if (!ACPI_STRCMP(pathname, ACPI_NS_ROOT_PATH)) {
			*ret_handle =
			    acpi_ns_convert_entry_to_handle(acpi_gbl_root_node);
			return (AE_OK);
		}
	} else if (!prefix_node) {

		/* Relative path with null prefix is disallowed */

		return (AE_BAD_PARAMETER);
	}

	/* Find the Node and convert to a handle */

	status =
	    acpi_ns_get_node(prefix_node, pathname, ACPI_NS_NO_UPSEARCH, &node);
	if (ACPI_SUCCESS(status)) {
		*ret_handle = acpi_ns_convert_entry_to_handle(node);
	}

	return (status);
}