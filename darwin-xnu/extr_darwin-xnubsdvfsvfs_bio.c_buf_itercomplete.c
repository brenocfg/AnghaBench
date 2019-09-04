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
struct buflists {int dummy; } ;
typedef  int /*<<< orphan*/  buf_t ;
struct TYPE_3__ {int v_iterblkflags; struct buflists v_cleanblkhd; struct buflists v_dirtyblkhd; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_EMPTY (struct buflists*) ; 
 int /*<<< orphan*/  LIST_FIRST (struct buflists*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct buflists*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VBI_DIRTY ; 
 int VBI_ITER ; 
 int VBI_ITERWANT ; 
 int /*<<< orphan*/  b_vnbufs ; 
 int /*<<< orphan*/  wakeup (int*) ; 

__attribute__((used)) static void
buf_itercomplete(vnode_t vp, struct buflists *iterheadp, int flags)
{
	struct buflists * listheadp;
	buf_t bp;

	if (flags & VBI_DIRTY)
		listheadp = &vp->v_dirtyblkhd;
	else
		listheadp = &vp->v_cleanblkhd;

	while (!LIST_EMPTY(iterheadp)) {
		bp = LIST_FIRST(iterheadp);
		LIST_REMOVE(bp, b_vnbufs);
		LIST_INSERT_HEAD(listheadp, bp, b_vnbufs);
	}
	vp->v_iterblkflags &= ~VBI_ITER;

	if  (vp->v_iterblkflags & VBI_ITERWANT) 	{
		vp->v_iterblkflags &= ~VBI_ITERWANT;
		wakeup(&vp->v_iterblkflags);
	}
}