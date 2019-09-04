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
struct TYPE_6__ {scalar_t__ v_type; int v_usecount; int v_kusecount; } ;

/* Variables and functions */
 scalar_t__ VREG ; 
 int ubc_isinuse_locked (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  vnode_lock_spin (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_unlock (TYPE_1__*) ; 

__attribute__((used)) static int 
vnode_isinuse_locked(vnode_t vp, int refcnt, int locked)
{
	int retval = 0;

	if (!locked)
		vnode_lock_spin(vp);
	if ((vp->v_type != VREG) && ((vp->v_usecount - vp->v_kusecount) >  refcnt)) {
		retval = 1;
		goto out;
	}
	if (vp->v_type == VREG)  {
		retval = ubc_isinuse_locked(vp, refcnt, 1);
	}
		
out:
	if (!locked)
		vnode_unlock(vp);
	return(retval);
}