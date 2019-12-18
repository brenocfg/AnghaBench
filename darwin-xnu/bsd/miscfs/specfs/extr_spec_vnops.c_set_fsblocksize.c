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
typedef  scalar_t__ u_int ;
struct vnode {scalar_t__ v_type; int /*<<< orphan*/  v_rdev; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 scalar_t__ VBLK ; 
 int major (int /*<<< orphan*/ ) ; 
 scalar_t__ nblkdev ; 
 int /*<<< orphan*/  set_blocksize (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_lock (struct vnode*) ; 
 int /*<<< orphan*/  vnode_unlock (struct vnode*) ; 

void
set_fsblocksize(struct vnode *vp)
{
	
	if (vp->v_type == VBLK) {
		dev_t dev = (dev_t)vp->v_rdev;
		int maj = major(dev);

		if ((u_int)maj >= (u_int)nblkdev)
			return;

		vnode_lock(vp);
		set_blocksize(vp, dev);
		vnode_unlock(vp);
	}

}