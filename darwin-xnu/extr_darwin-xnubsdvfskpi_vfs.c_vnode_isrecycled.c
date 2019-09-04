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
struct TYPE_5__ {int v_lflag; } ;

/* Variables and functions */
 int VL_DEAD ; 
 int VL_TERMINATE ; 
 int /*<<< orphan*/  vnode_lock_spin (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_unlock (TYPE_1__*) ; 

int 
vnode_isrecycled(vnode_t vp)
{
	int ret;

	vnode_lock_spin(vp);
	ret =  (vp->v_lflag & (VL_TERMINATE|VL_DEAD))? 1 : 0;
	vnode_unlock(vp);
	return(ret);
}