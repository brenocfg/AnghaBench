#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vnode {int v_usecount; int v_kusecount; } ;

/* Variables and functions */
 int /*<<< orphan*/  vnode_lock_spin (struct vnode*) ; 
 int /*<<< orphan*/  vnode_unlock (struct vnode*) ; 

int
ubc_isinuse_locked(struct vnode *vp, int busycount, int locked)
{
	int retval = 0;


	if (!locked)
		vnode_lock_spin(vp);

	if ((vp->v_usecount - vp->v_kusecount) > busycount)
		retval = 1;

	if (!locked)
		vnode_unlock(vp);
	return (retval);
}