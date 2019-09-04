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
struct vnode {int /*<<< orphan*/  v_lflag; scalar_t__ v_usecount; scalar_t__ v_iocount; } ;

/* Variables and functions */
 int /*<<< orphan*/  VL_MARKTERM ; 
 int /*<<< orphan*/  vnode_lock_convert (struct vnode*) ; 
 int /*<<< orphan*/  vnode_lock_spin (struct vnode*) ; 
 int /*<<< orphan*/  vnode_reclaim_internal (struct vnode*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_unlock (struct vnode*) ; 

int
vnode_recycle(struct vnode *vp)
{
	vnode_lock_spin(vp);

	if (vp->v_iocount || vp->v_usecount) {
		vp->v_lflag |= VL_MARKTERM;
		vnode_unlock(vp);
		return(0);
	} 
	vnode_lock_convert(vp);
	vnode_reclaim_internal(vp, 1, 0, 0);

	vnode_unlock(vp);

	return (1);
}