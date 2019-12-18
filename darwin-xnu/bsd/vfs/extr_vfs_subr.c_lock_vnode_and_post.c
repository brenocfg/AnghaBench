#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
struct TYPE_7__ {int /*<<< orphan*/ * slh_first; } ;
struct TYPE_6__ {TYPE_5__ v_knotes; } ;

/* Variables and functions */
 int /*<<< orphan*/  KNOTE (TYPE_5__*,int) ; 
 int /*<<< orphan*/  vnode_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_unlock (TYPE_1__*) ; 

void 
lock_vnode_and_post(vnode_t vp, int kevent_num) 
{
	/* Only take the lock if there's something there! */
	if (vp->v_knotes.slh_first != NULL) {
		vnode_lock(vp);
		KNOTE(&vp->v_knotes, kevent_num);
		vnode_unlock(vp);
	}
}