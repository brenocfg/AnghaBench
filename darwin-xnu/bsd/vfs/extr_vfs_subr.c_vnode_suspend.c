#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_5__ {int v_lflag; int /*<<< orphan*/ * v_owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int VL_SUSPENDED ; 
 int /*<<< orphan*/ * current_thread () ; 
 int /*<<< orphan*/  vnode_lock_spin (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_unlock (TYPE_1__*) ; 

errno_t
vnode_suspend(vnode_t vp)
{
	if (vp->v_lflag & VL_SUSPENDED) {
		return(EBUSY);
	}

	vnode_lock_spin(vp);

	/* 
	 * xxx is this sufficient to check if a vnode_drain is 
	 * progress?
	 */

	if (vp->v_owner == NULL) {
		vp->v_lflag |= VL_SUSPENDED;
		vp->v_owner = current_thread();
	}
	vnode_unlock(vp);

	return(0);
}