#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
struct TYPE_3__ {int /*<<< orphan*/  v_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 

void
vnode_lock_spin(vnode_t vp)
{
	lck_mtx_lock_spin(&vp->v_lock);
}