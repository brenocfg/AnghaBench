#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* vnode_t ;
struct cl_writebehind {scalar_t__ cl_scmap; scalar_t__ cl_number; } ;
struct TYPE_6__ {scalar_t__ lh_first; } ;
struct TYPE_8__ {TYPE_2__* v_ubcinfo; TYPE_1__ v_dirtyblkhd; } ;
struct TYPE_7__ {struct cl_writebehind* cl_wbehind; } ;

/* Variables and functions */
 int /*<<< orphan*/  UBCINFOEXISTS (TYPE_3__*) ; 

int
vnode_hasdirtyblks(vnode_t vp)
{
        struct cl_writebehind *wbp;

	/*
	 * Not taking the buf_mtxp as there is little
	 * point doing it. Even if the lock is taken the
	 * state can change right after that. If their 
	 * needs to be a synchronization, it must be driven
	 * by the caller
	 */ 
        if (vp->v_dirtyblkhd.lh_first)
	        return (1);
	
	if (!UBCINFOEXISTS(vp))
	        return (0);

	wbp = vp->v_ubcinfo->cl_wbehind;

	if (wbp && (wbp->cl_number || wbp->cl_scmap))
	        return (1);

	return (0);
}