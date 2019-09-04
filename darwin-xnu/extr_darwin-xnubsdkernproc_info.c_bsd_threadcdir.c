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
struct uthread {TYPE_1__* uu_cdir; } ;
struct TYPE_3__ {int v_id; } ;

/* Variables and functions */
 TYPE_1__* NULLVP ; 

void
bsd_threadcdir(void * uth, void *vptr, int *vidp)
{
	struct uthread * ut = (struct uthread *)uth;
	vnode_t vp;
	vnode_t *vpp = (vnode_t *)vptr;

	vp = ut->uu_cdir;
	if (vp  != NULLVP) {
		if (vpp != NULL) {
			*vpp = vp;
			if (vidp != NULL)
				*vidp = vp->v_id;
		}
	}
}