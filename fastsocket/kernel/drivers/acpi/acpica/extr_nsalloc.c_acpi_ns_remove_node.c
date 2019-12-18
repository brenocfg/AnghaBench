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
struct acpi_namespace_node {struct acpi_namespace_node* peer; struct acpi_namespace_node* child; struct acpi_namespace_node* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ns_delete_node (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  ns_remove_node ; 
 int /*<<< orphan*/  return_VOID ; 

void acpi_ns_remove_node(struct acpi_namespace_node *node)
{
	struct acpi_namespace_node *parent_node;
	struct acpi_namespace_node *prev_node;
	struct acpi_namespace_node *next_node;

	ACPI_FUNCTION_TRACE_PTR(ns_remove_node, node);

	parent_node = node->parent;

	prev_node = NULL;
	next_node = parent_node->child;

	/* Find the node that is the previous peer in the parent's child list */

	while (next_node != node) {
		prev_node = next_node;
		next_node = next_node->peer;
	}

	if (prev_node) {

		/* Node is not first child, unlink it */

		prev_node->peer = node->peer;
	} else {
		/*
		 * Node is first child (has no previous peer).
		 * Link peer list to parent
		 */
		parent_node->child = node->peer;
	}

	/* Delete the node and any attached objects */

	acpi_ns_delete_node(node);
	return_VOID;
}