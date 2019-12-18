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
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_5__ {int v_flag; int /*<<< orphan*/  v_lock; } ;

/* Variables and functions */
 int VISUNION ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_lock_spin (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_unlock (TYPE_1__*) ; 

void
vn_checkunionwait(vnode_t vp)
{
	vnode_lock_spin(vp);
	while ((vp->v_flag & VISUNION) == VISUNION)
		msleep((caddr_t)&vp->v_flag, &vp->v_lock, 0, 0, 0);
	vnode_unlock(vp);
}