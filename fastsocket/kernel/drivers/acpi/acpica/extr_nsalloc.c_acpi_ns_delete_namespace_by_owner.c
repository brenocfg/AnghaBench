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
typedef  int u32 ;
struct acpi_namespace_node {scalar_t__ owner_id; struct acpi_namespace_node* parent; scalar_t__ child; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_owner_id ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_U32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ACPI_MTX_NAMESPACE ; 
 struct acpi_namespace_node* acpi_gbl_root_node ; 
 int /*<<< orphan*/  acpi_ns_delete_children (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ns_detach_object (struct acpi_namespace_node*) ; 
 struct acpi_namespace_node* acpi_ns_get_next_node (struct acpi_namespace_node*,struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ns_remove_node (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ut_acquire_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_release_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_delete_namespace_by_owner ; 
 int /*<<< orphan*/  return_VOID ; 

void acpi_ns_delete_namespace_by_owner(acpi_owner_id owner_id)
{
	struct acpi_namespace_node *child_node;
	struct acpi_namespace_node *deletion_node;
	struct acpi_namespace_node *parent_node;
	u32 level;
	acpi_status status;

	ACPI_FUNCTION_TRACE_U32(ns_delete_namespace_by_owner, owner_id);

	if (owner_id == 0) {
		return_VOID;
	}

	/* Lock namespace for possible update */

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAILURE(status)) {
		return_VOID;
	}

	deletion_node = NULL;
	parent_node = acpi_gbl_root_node;
	child_node = NULL;
	level = 1;

	/*
	 * Traverse the tree of nodes until we bubble back up
	 * to where we started.
	 */
	while (level > 0) {
		/*
		 * Get the next child of this parent node. When child_node is NULL,
		 * the first child of the parent is returned
		 */
		child_node = acpi_ns_get_next_node(parent_node, child_node);

		if (deletion_node) {
			acpi_ns_delete_children(deletion_node);
			acpi_ns_remove_node(deletion_node);
			deletion_node = NULL;
		}

		if (child_node) {
			if (child_node->owner_id == owner_id) {

				/* Found a matching child node - detach any attached object */

				acpi_ns_detach_object(child_node);
			}

			/* Check if this node has any children */

			if (child_node->child) {
				/*
				 * There is at least one child of this node,
				 * visit the node
				 */
				level++;
				parent_node = child_node;
				child_node = NULL;
			} else if (child_node->owner_id == owner_id) {
				deletion_node = child_node;
			}
		} else {
			/*
			 * No more children of this parent node.
			 * Move up to the grandparent.
			 */
			level--;
			if (level != 0) {
				if (parent_node->owner_id == owner_id) {
					deletion_node = parent_node;
				}
			}

			/* New "last child" is this parent node */

			child_node = parent_node;

			/* Move up the tree to the grandparent */

			parent_node = parent_node->parent;
		}
	}

	(void)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	return_VOID;
}