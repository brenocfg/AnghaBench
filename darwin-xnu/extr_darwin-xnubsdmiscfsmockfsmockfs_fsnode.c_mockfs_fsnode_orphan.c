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
struct TYPE_4__ {struct TYPE_4__* parent; struct TYPE_4__* child_b; struct TYPE_4__* child_a; scalar_t__ vp; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*) ; 

int mockfs_fsnode_orphan(mockfs_fsnode_t fsnp)
{
	int rvalue;
	mockfs_fsnode_t parent;

	rvalue = 0;

	if (!fsnp || !fsnp->parent) {
		rvalue = EINVAL;
		goto done;
	}

	/*
	 * Disallow orphaning a node with a live vnode for now.
	 */
	if (fsnp->vp)
		panic("mockfs_fsnode_orphan called on node with live vnode; fsnp = %p (in case gdb is screwing with you)", fsnp);

	parent = fsnp->parent;

	if (parent->child_a == fsnp) {
		parent->child_a = NULL;
		fsnp->parent = NULL;
	}
	else if (parent->child_b == fsnp) {
		parent->child_b = NULL;
		fsnp->parent = NULL;
	}
	else
		panic("mockfs_fsnode_orphan insanity, fsnp->parent != parent->child; fsnp = %p (in case gdb is screwing with you)", fsnp);

done:
	return rvalue;
}