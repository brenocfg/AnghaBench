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
struct acpi_namespace_node {struct acpi_namespace_node* parent; } ;
typedef  int acpi_size ;

/* Variables and functions */
 scalar_t__ ACPI_DESC_TYPE_NAMED ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (struct acpi_namespace_node*) ; 
 scalar_t__ ACPI_PATH_SEGMENT_LENGTH ; 
 int /*<<< orphan*/  AE_INFO ; 
 struct acpi_namespace_node* acpi_gbl_root_node ; 

acpi_size acpi_ns_get_pathname_length(struct acpi_namespace_node *node)
{
	acpi_size size;
	struct acpi_namespace_node *next_node;

	ACPI_FUNCTION_ENTRY();

	/*
	 * Compute length of pathname as 5 * number of name segments.
	 * Go back up the parent tree to the root
	 */
	size = 0;
	next_node = node;

	while (next_node && (next_node != acpi_gbl_root_node)) {
		if (ACPI_GET_DESCRIPTOR_TYPE(next_node) != ACPI_DESC_TYPE_NAMED) {
			ACPI_ERROR((AE_INFO,
				    "Invalid Namespace Node (%p) while traversing namespace",
				    next_node));
			return 0;
		}
		size += ACPI_PATH_SEGMENT_LENGTH;
		next_node = next_node->parent;
	}

	if (!size) {
		size = 1;	/* Root node case */
	}

	return (size + 1);	/* +1 for null string terminator */
}