#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
struct TYPE_8__ {int v_listflag; } ;

/* Variables and functions */
 int VLIST_ASYNC_WORK ; 
 int VLIST_DEAD ; 
 int VLIST_RAGE ; 
 scalar_t__ VONLIST (TYPE_1__*) ; 
 int /*<<< orphan*/  VREMASYNC_WORK (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  VREMDEAD (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  VREMFREE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  VREMRAGE (char*,TYPE_1__*) ; 

__attribute__((used)) static void
vnode_list_remove_locked(vnode_t vp)
{
	if (VONLIST(vp)) {
		/*
		 * the v_listflag field is
		 * protected by the vnode_list_lock
		 */
	        if (vp->v_listflag & VLIST_RAGE)
		        VREMRAGE("vnode_list_remove", vp);
		else if (vp->v_listflag & VLIST_DEAD)
		        VREMDEAD("vnode_list_remove", vp);
		else if (vp->v_listflag & VLIST_ASYNC_WORK)
		        VREMASYNC_WORK("vnode_list_remove", vp);
		else
		        VREMFREE("vnode_list_remove", vp);
	}
}