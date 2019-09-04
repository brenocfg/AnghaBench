#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vnode_t ;
struct vnode {int dummy; } ;
struct TYPE_6__ {struct vnode** tqe_prev; } ;
struct TYPE_7__ {int v_lflag; TYPE_1__ v_freelist; } ;

/* Variables and functions */
 int VNAMED_FSHASH ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  vnode_lock_spin (TYPE_2__*) ; 
 int /*<<< orphan*/  vnode_unlock (TYPE_2__*) ; 

int
vnode_addfsref(vnode_t vp)
{
	vnode_lock_spin(vp);
	if (vp->v_lflag & VNAMED_FSHASH)
		panic("add_fsref: vp already has named reference");
	if ((vp->v_freelist.tqe_prev != (struct vnode **)0xdeadb))
	        panic("addfsref: vp on the free list\n");
	vp->v_lflag |= VNAMED_FSHASH;
	vnode_unlock(vp);
	return(0);

}