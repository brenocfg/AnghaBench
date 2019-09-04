#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
struct vnop_read_args {int /*<<< orphan*/  a_ioflag; int /*<<< orphan*/  a_uio; TYPE_1__* a_vp; } ;
typedef  TYPE_2__* mockfs_fsnode_t ;
struct TYPE_5__ {int /*<<< orphan*/  size; } ;
struct TYPE_4__ {scalar_t__ v_type; scalar_t__ v_data; } ;

/* Variables and functions */
 int ENOTSUP ; 
 scalar_t__ VREG ; 
 int cluster_read (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mockfs_read(struct vnop_read_args * ap)
{
	int rvalue;
	vnode_t vp;
	mockfs_fsnode_t fsnode;

	vp = ap->a_vp;
	fsnode = (mockfs_fsnode_t) vp->v_data;

	/*
	 * We're just an ugly frontend for the devnode, so we shouldn't need to do much for reads;
	 *   pass the work to cluster_read.
	 */
	if (vp->v_type == VREG) {
		rvalue = cluster_read(vp, ap->a_uio, fsnode->size, ap->a_ioflag);
	}
	else {
		/*
		 * You've tried to read from a nonregular file; I hate you.
		 */
		rvalue = ENOTSUP;
	}

	return rvalue;
}