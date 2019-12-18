#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
struct TYPE_6__ {int v_lflag; int /*<<< orphan*/  v_listflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLIST_ASYNC_WORK ; 
 int VL_DEAD ; 
 int VL_TERMINATE ; 
 scalar_t__ VONLIST (TYPE_1__*) ; 
 int /*<<< orphan*/  async_work_vnodes ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  v_freelist ; 
 int /*<<< orphan*/  vnode_async_work_list ; 
 int /*<<< orphan*/  vnode_list_lock () ; 
 int /*<<< orphan*/  vnode_list_unlock () ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vnode_async_list_add(vnode_t vp)
{
	vnode_list_lock();

	if (VONLIST(vp) || (vp->v_lflag & (VL_TERMINATE|VL_DEAD)))
		panic("vnode_async_list_add: %p is in wrong state", vp);

	TAILQ_INSERT_HEAD(&vnode_async_work_list, vp, v_freelist);
	vp->v_listflag |= VLIST_ASYNC_WORK;

	async_work_vnodes++;

	vnode_list_unlock();

	wakeup(&vnode_async_work_list);

}