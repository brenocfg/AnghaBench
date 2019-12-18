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
typedef  int /*<<< orphan*/  caddr_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_11__ {scalar_t__ v_usecount; scalar_t__ v_iocount; int v_lflag; int v_flag; int /*<<< orphan*/  v_listflag; int /*<<< orphan*/  v_dirtyblkhd; int /*<<< orphan*/  v_cleanblkhd; int /*<<< orphan*/  v_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_INVALIDATE_LOCKED ; 
 scalar_t__ FALSE ; 
 scalar_t__ ISSET (int,int) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int VAGE ; 
 int /*<<< orphan*/  VLIST_DEAD ; 
 int /*<<< orphan*/  VLIST_RAGE ; 
 int VL_DEAD ; 
 int VL_TERMINATE ; 
 scalar_t__ VONLIST (TYPE_1__*) ; 
 int VRAGE ; 
 int /*<<< orphan*/  buf_invalidateblks (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dead_vnode_wanted ; 
 int /*<<< orphan*/  deadvnodes ; 
 int /*<<< orphan*/  freevnodes ; 
 int /*<<< orphan*/  lck_mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  microuptime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rage_tv ; 
 int /*<<< orphan*/  ragevnodes ; 
 int /*<<< orphan*/  record_vp (TYPE_1__*,int) ; 
 int /*<<< orphan*/  v_freelist ; 
 int /*<<< orphan*/  vnode_dead_list ; 
 int /*<<< orphan*/  vnode_dropiocount (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_free_list ; 
 int /*<<< orphan*/  vnode_list_lock () ; 
 int /*<<< orphan*/  vnode_list_unlock () ; 
 int /*<<< orphan*/  vnode_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_rage_list ; 
 int /*<<< orphan*/  vnode_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  wakeup_one (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vnode_list_add(vnode_t vp)
{
	boolean_t need_dead_wakeup = FALSE;

#if DIAGNOSTIC
	lck_mtx_assert(&vp->v_lock, LCK_MTX_ASSERT_OWNED);
#endif

again:

	/*
	 * if it is already on a list or non zero references return 
	 */
	if (VONLIST(vp) || (vp->v_usecount != 0) || (vp->v_iocount != 0) || (vp->v_lflag & VL_TERMINATE))
		return;

	/*
	 * In vclean, we might have deferred ditching locked buffers
	 * because something was still referencing them (indicated by
	 * usecount).  We can ditch them now.
	 */
	if (ISSET(vp->v_lflag, VL_DEAD)
		&& (!LIST_EMPTY(&vp->v_cleanblkhd) || !LIST_EMPTY(&vp->v_dirtyblkhd))) {
		++vp->v_iocount;	// Probably not necessary, but harmless
#ifdef JOE_DEBUG
		record_vp(vp, 1);
#endif
		vnode_unlock(vp);
		buf_invalidateblks(vp, BUF_INVALIDATE_LOCKED, 0, 0);
		vnode_lock(vp);
		vnode_dropiocount(vp);
		goto again;
	}

	vnode_list_lock();

	if ((vp->v_flag & VRAGE) && !(vp->v_lflag & VL_DEAD)) {
		/*
		 * add the new guy to the appropriate end of the RAGE list
		 */
		if ((vp->v_flag & VAGE))
		        TAILQ_INSERT_HEAD(&vnode_rage_list, vp, v_freelist);
		else
		        TAILQ_INSERT_TAIL(&vnode_rage_list, vp, v_freelist);

		vp->v_listflag |= VLIST_RAGE;
		ragevnodes++;

		/*
		 * reset the timestamp for the last inserted vp on the RAGE
		 * queue to let new_vnode know that its not ok to start stealing
		 * from this list... as long as we're actively adding to this list
		 * we'll push out the vnodes we want to donate to the real free list
		 * once we stop pushing, we'll let some time elapse before we start
		 * stealing them in the new_vnode routine
		 */
		microuptime(&rage_tv);
	} else {
	        /*
		 * if VL_DEAD, insert it at head of the dead list
		 * else insert at tail of LRU list or at head if VAGE is set
		 */
	        if ( (vp->v_lflag & VL_DEAD)) {
		        TAILQ_INSERT_HEAD(&vnode_dead_list, vp, v_freelist);
			vp->v_listflag |= VLIST_DEAD;
			deadvnodes++;

			if (dead_vnode_wanted) {
				dead_vnode_wanted--;
				need_dead_wakeup = TRUE;
			}

		} else if ( (vp->v_flag & VAGE) ) {
		        TAILQ_INSERT_HEAD(&vnode_free_list, vp, v_freelist);
			vp->v_flag &= ~VAGE;
			freevnodes++;
		} else {
		        TAILQ_INSERT_TAIL(&vnode_free_list, vp, v_freelist);
			freevnodes++;
		}
	}
	vnode_list_unlock();

	if (need_dead_wakeup == TRUE)
		wakeup_one((caddr_t)&dead_vnode_wanted);
}