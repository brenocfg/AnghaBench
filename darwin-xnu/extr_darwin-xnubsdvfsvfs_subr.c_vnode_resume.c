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
struct TYPE_5__ {int v_lflag; scalar_t__ v_owner; int /*<<< orphan*/  v_iocount; } ;

/* Variables and functions */
 int VL_SUSPENDED ; 
 scalar_t__ current_thread () ; 
 int /*<<< orphan*/  vnode_lock_spin (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

errno_t 
vnode_resume(vnode_t vp)
{
	if ((vp->v_lflag & VL_SUSPENDED) && vp->v_owner == current_thread()) {

		vnode_lock_spin(vp);
	        vp->v_lflag &= ~VL_SUSPENDED;
		vp->v_owner = NULL;
		vnode_unlock(vp);

		wakeup(&vp->v_iocount);
	}
	return(0);
}