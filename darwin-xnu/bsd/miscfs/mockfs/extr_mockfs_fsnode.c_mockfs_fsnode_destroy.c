#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* mockfs_mount_t ;
typedef  TYPE_3__* mockfs_fsnode_t ;
struct TYPE_10__ {scalar_t__ parent; struct TYPE_10__* child_b; struct TYPE_10__* child_a; scalar_t__ vp; TYPE_1__* mnt; } ;
struct TYPE_9__ {TYPE_3__* mockfs_root; } ;
struct TYPE_8__ {scalar_t__ mnt_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FREE (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int mockfs_fsnode_orphan (TYPE_3__*) ; 
 int /*<<< orphan*/  panic (char*,TYPE_3__*,...) ; 

int mockfs_fsnode_destroy(mockfs_fsnode_t fsnp)
{
	int rvalue;

	rvalue = 0;

	/*
	 * We will not destroy a root node that is actively pointed to by the mount structure; the
	 *   mount must drop the reference to the mockfs tree before we can deallocate it.
	 */
	if (!fsnp || (((mockfs_mount_t)fsnp->mnt->mnt_data)->mockfs_root == fsnp)) {
		rvalue = EINVAL;
		goto done;
	}

	/*
	 * For now, panic in this case; I don't expect anyone to ask us to destroy a node with a live
	 *   vfs reference, but this will tell me if that assumption is untrue.
	 */
	if (fsnp->vp)
		panic("mockfs_fsnode_destroy called on node with live vnode; fsnp = %p (in case gdb is screwing with you)", fsnp);

	/*
	 * If this node has children, we need to destroy them.
	 *
	 * At least for now, we aren't guaranteeing destroy will be clean; we may get partway through
	 *   and encounter an error, in which case we will panic (we may still have a sane tree, but
	 *   we've failed to destroy the subtree, which means someone called destroy when they should
	 *   not have done so).
	 */
	if (fsnp->child_a)
		if ((rvalue = mockfs_fsnode_destroy(fsnp->child_a)))
			panic("mockfs_fsnode_destroy failed on child_a; fsnp = %p (in case gdb is screwing with you), rvalue = %d", fsnp, rvalue);

	if (fsnp->child_b)
		if ((rvalue = mockfs_fsnode_destroy(fsnp->child_b)))
			panic("mockfs_fsnode_destroy failed on child_b; fsnp = %p (in case gdb is screwing with you), rvalue = %d", fsnp, rvalue);

	/*
	 * We need to orphan this node before we destroy it.
	 */
	if (fsnp->parent)
		if ((rvalue = mockfs_fsnode_orphan(fsnp)))
			panic("mockfs_fsnode_orphan failed during destroy; fsnp = %p (in case gdb is screwing with you), rvalue = %d", fsnp, rvalue);

	FREE(fsnp, M_TEMP);
done:
	return rvalue;
}