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
struct vnode {scalar_t__ v_iocount; int v_lflag; } ;

/* Variables and functions */
 int ENOENT ; 
 int VL_DEAD ; 
 int VL_TERMINATE ; 

int
vnode_get_locked(struct vnode *vp)
{
#if DIAGNOSTIC
	lck_mtx_assert(&vp->v_lock, LCK_MTX_ASSERT_OWNED);
#endif
	if ((vp->v_iocount == 0) && (vp->v_lflag & (VL_TERMINATE | VL_DEAD))) {
		return(ENOENT);	
	}
	vp->v_iocount++;
#ifdef JOE_DEBUG
	record_vp(vp, 1);
#endif
	return (0);
}