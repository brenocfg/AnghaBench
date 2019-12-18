#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct TYPE_11__ {int v_iocount; scalar_t__ v_usecount; int v_lflag; int /*<<< orphan*/  v_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int VL_DEAD ; 
 int VL_MARKTERM ; 
 int VL_NEEDINACTIVE ; 
 int VL_TERMINATE ; 
 int /*<<< orphan*/  VNOP_INACTIVE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 int /*<<< orphan*/  vnode_dropiocount (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_list_add (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_lock_convert (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_lock_spin (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_reclaim_internal (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_unlock (TYPE_1__*) ; 

int
vnode_put_locked(vnode_t vp)
{
	vfs_context_t ctx = vfs_context_current();	/* hoist outside loop */

#if DIAGNOSTIC
	lck_mtx_assert(&vp->v_lock, LCK_MTX_ASSERT_OWNED);
#endif
retry:
	if (vp->v_iocount < 1) 
		panic("vnode_put(%p): iocount < 1", vp);

	if ((vp->v_usecount > 0) || (vp->v_iocount > 1))  {
		vnode_dropiocount(vp);
		return(0);
	}
	if ((vp->v_lflag & (VL_DEAD | VL_NEEDINACTIVE)) == VL_NEEDINACTIVE) {

	        vp->v_lflag &= ~VL_NEEDINACTIVE;
	        vnode_unlock(vp);

		VNOP_INACTIVE(vp, ctx);

		vnode_lock_spin(vp);
		/*
		 * because we had to drop the vnode lock before calling
		 * VNOP_INACTIVE, the state of this vnode may have changed...
		 * we may pick up both VL_MARTERM and either
		 * an iocount or a usecount while in the VNOP_INACTIVE call
		 * we don't want to call vnode_reclaim_internal on a vnode
		 * that has active references on it... so loop back around
		 * and reevaluate the state
		 */
		goto retry;
	}
        vp->v_lflag &= ~VL_NEEDINACTIVE;

	if ((vp->v_lflag & (VL_MARKTERM | VL_TERMINATE | VL_DEAD)) == VL_MARKTERM) {
	        vnode_lock_convert(vp);
	        vnode_reclaim_internal(vp, 1, 1, 0);
	}
	vnode_dropiocount(vp);
	vnode_list_add(vp);

	return(0);
}