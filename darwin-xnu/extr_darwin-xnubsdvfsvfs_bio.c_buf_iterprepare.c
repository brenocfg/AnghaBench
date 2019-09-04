#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* vnode_t ;
struct buflists {TYPE_2__* lh_first; } ;
struct TYPE_7__ {int v_iterblkflags; struct buflists v_cleanblkhd; struct buflists v_dirtyblkhd; } ;
struct TYPE_5__ {TYPE_2__** le_prev; } ;
struct TYPE_6__ {TYPE_1__ b_vnbufs; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ LIST_EMPTY (struct buflists*) ; 
 int /*<<< orphan*/  LIST_INIT (struct buflists*) ; 
 int VBI_DIRTY ; 
 int VBI_ITER ; 
 int VBI_ITERWANT ; 
 int /*<<< orphan*/  buf_mtxp ; 
 int /*<<< orphan*/  msleep (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
buf_iterprepare(vnode_t vp, struct buflists *iterheadp, int flags)
{
	struct buflists * listheadp;

	if (flags & VBI_DIRTY)
		listheadp = &vp->v_dirtyblkhd;
	else
		listheadp = &vp->v_cleanblkhd;
		
	while (vp->v_iterblkflags & VBI_ITER) 	{
	        vp->v_iterblkflags |= VBI_ITERWANT;
		msleep(&vp->v_iterblkflags, buf_mtxp, 0, "buf_iterprepare", NULL);	
	}
	if (LIST_EMPTY(listheadp)) {
	        LIST_INIT(iterheadp);
		return(EINVAL);
	}
	vp->v_iterblkflags |= VBI_ITER;

	iterheadp->lh_first = listheadp->lh_first;
	listheadp->lh_first->b_vnbufs.le_prev = &iterheadp->lh_first;	
	LIST_INIT(listheadp);

	return(0);
}