#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mockfs_fsnode_t ;
struct TYPE_4__ {scalar_t__ mnt; struct TYPE_4__* parent; struct TYPE_4__* child_b; struct TYPE_4__* child_a; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 

int mockfs_fsnode_adopt(mockfs_fsnode_t parent, mockfs_fsnode_t child)
{
	int rvalue;

	rvalue = 0;

	/*
	 * The child must be an orphan, and the parent cannot be the child.
	 */
	if ((!parent || !child || child->parent) && (parent != child)) {
		rvalue = EINVAL;
		goto done;
	}

	/*
	 * Nodes are actually tied to a specific mount, so assert that both nodes belong to the same mount.
	 */
	if (parent->mnt != child->mnt) {
		rvalue = EINVAL;
		goto done;
	}

	/*
	 * TODO: Get rid of this check if I ever get around to making the tree non-binary.
	 * TODO: Enforce that the parent cannot have two children of the same type (for the moment, this is
	 *   implicit in the structure of the tree constructed by mockfs_mountroot, so we don't need to
	 *   worry about it).
	 * 
	 * Can the parent support another child (food, shelter, unused pointers)?
	 */
	if (!parent->child_a) {
		parent->child_a = child;
		child->parent = parent;
	}
	else if (!parent->child_b) {
		parent->child_b = child;
		child->parent = parent;
	}
	else {
		rvalue = ENOMEM;
	}

done:
	return rvalue;
}