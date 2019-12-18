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
struct acpi_namespace_node {struct acpi_namespace_node* child; struct acpi_namespace_node* peer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  acpi_ns_delete_node (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  ns_delete_children ; 
 int /*<<< orphan*/  return_VOID ; 

void acpi_ns_delete_children(struct acpi_namespace_node *parent_node)
{
	struct acpi_namespace_node *next_node;
	struct acpi_namespace_node *node_to_delete;

	ACPI_FUNCTION_TRACE_PTR(ns_delete_children, parent_node);

	if (!parent_node) {
		return_VOID;
	}

	/* Deallocate all children at this level */

	next_node = parent_node->child;
	while (next_node) {

		/* Grandchildren should have all been deleted already */

		if (next_node->child) {
			ACPI_ERROR((AE_INFO, "Found a grandchild! P=%p C=%p",
				    parent_node, next_node));
		}

		/*
		 * Delete this child node and move on to the next child in the list.
		 * No need to unlink the node since we are deleting the entire branch.
		 */
		node_to_delete = next_node;
		next_node = next_node->peer;
		acpi_ns_delete_node(node_to_delete);
	};

	/* Clear the parent's child pointer */

	parent_node->child = NULL;
	return_VOID;
}