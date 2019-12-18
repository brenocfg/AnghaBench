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
struct TYPE_5__ {int v_iocount; int /*<<< orphan*/  v_lflag; scalar_t__ v_usecount; } ;

/* Variables and functions */
 int /*<<< orphan*/  VL_MARKTERM ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  vnode_lock_spin (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_unlock (TYPE_1__*) ; 

__attribute__((used)) static int
vnode_reload(vnode_t vp)
{
	vnode_lock_spin(vp);

	if ((vp->v_iocount > 1) || vp->v_usecount) {
		vnode_unlock(vp);
		return(0);
	} 
	if (vp->v_iocount <= 0)
		panic("vnode_reload with no iocount %d", vp->v_iocount);

	/* mark for release when iocount is dopped */
	vp->v_lflag |= VL_MARKTERM;
	vnode_unlock(vp);

	return (1);
}