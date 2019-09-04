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
typedef  int /*<<< orphan*/  vnode_t ;
struct vnop_reclaim_args {int /*<<< orphan*/  a_vp; } ;
typedef  scalar_t__ mockfs_fsnode_t ;

/* Variables and functions */
 int mockfs_fsnode_drop_vnode (scalar_t__) ; 
 scalar_t__ vnode_fsnode (int /*<<< orphan*/ ) ; 

int mockfs_reclaim(struct vnop_reclaim_args * ap)
{
	int rvalue;
	vnode_t vp;
	mockfs_fsnode_t fsnode;

	vp = ap->a_vp;
	fsnode = (mockfs_fsnode_t) vnode_fsnode(vp);
	rvalue = mockfs_fsnode_drop_vnode(fsnode);

	return rvalue;
}