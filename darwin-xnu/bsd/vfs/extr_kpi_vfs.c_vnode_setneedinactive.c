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
struct TYPE_6__ {int /*<<< orphan*/  v_lflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  VL_NEEDINACTIVE ; 
 int /*<<< orphan*/  cache_purge (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_lock_spin (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_unlock (TYPE_1__*) ; 

void
vnode_setneedinactive(vnode_t vp)
{
        cache_purge(vp);

        vnode_lock_spin(vp);
	vp->v_lflag |= VL_NEEDINACTIVE;
	vnode_unlock(vp);
}