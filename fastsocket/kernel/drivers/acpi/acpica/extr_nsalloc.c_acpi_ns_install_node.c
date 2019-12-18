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
typedef  scalar_t__ u8 ;
struct acpi_walk_state {TYPE_2__* method_desc; struct acpi_namespace_node* method_node; int /*<<< orphan*/  owner_id; } ;
struct acpi_namespace_node {scalar_t__ type; int /*<<< orphan*/  owner_id; struct acpi_namespace_node* peer; struct acpi_namespace_node* child; struct acpi_namespace_node* parent; } ;
typedef  int /*<<< orphan*/  acpi_owner_id ;
typedef  scalar_t__ acpi_object_type ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__ method; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_NAMES ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AOPOBJ_MODIFIED_NAMESPACE ; 
 int /*<<< orphan*/  acpi_ut_get_node_name (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ut_get_type_name (scalar_t__) ; 
 int /*<<< orphan*/  ns_install_node ; 
 int /*<<< orphan*/  return_VOID ; 

void acpi_ns_install_node(struct acpi_walk_state *walk_state, struct acpi_namespace_node *parent_node,	/* Parent */
			  struct acpi_namespace_node *node,	/* New Child */
			  acpi_object_type type)
{
	acpi_owner_id owner_id = 0;
	struct acpi_namespace_node *child_node;

	ACPI_FUNCTION_TRACE(ns_install_node);

	if (walk_state) {
		/*
		 * Get the owner ID from the Walk state. The owner ID is used to
		 * track table deletion and deletion of objects created by methods.
		 */
		owner_id = walk_state->owner_id;

		if ((walk_state->method_desc) &&
		    (parent_node != walk_state->method_node)) {
			/*
			 * A method is creating a new node that is not a child of the
			 * method (it is non-local). Mark the executing method as having
			 * modified the namespace. This is used for cleanup when the
			 * method exits.
			 */
			walk_state->method_desc->method.flags |=
			    AOPOBJ_MODIFIED_NAMESPACE;
		}
	}

	/* Link the new entry into the parent and existing children */

	node->peer = NULL;
	node->parent = parent_node;
	child_node = parent_node->child;

	if (!child_node) {
		parent_node->child = node;
	} else {
		/* Add node to the end of the peer list */

		while (child_node->peer) {
			child_node = child_node->peer;
		}

		child_node->peer = node;
	}

	/* Init the new entry */

	node->owner_id = owner_id;
	node->type = (u8) type;

	ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
			  "%4.4s (%s) [Node %p Owner %X] added to %4.4s (%s) [Node %p]\n",
			  acpi_ut_get_node_name(node),
			  acpi_ut_get_type_name(node->type), node, owner_id,
			  acpi_ut_get_node_name(parent_node),
			  acpi_ut_get_type_name(parent_node->type),
			  parent_node));

	return_VOID;
}