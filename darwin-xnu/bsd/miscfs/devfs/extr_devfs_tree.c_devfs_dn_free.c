#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dn_links; scalar_t__ dn_refcount; int /*<<< orphan*/  dn_lflags; struct TYPE_4__** dn_prevsiblingp; struct TYPE_4__* dn_nextsibling; } ;
typedef  TYPE_1__ devnode_t ;

/* Variables and functions */
 int /*<<< orphan*/  DN_DELETE ; 
 int /*<<< orphan*/  devnode_free (TYPE_1__*) ; 

__attribute__((used)) static void
devfs_dn_free(devnode_t * dnp)
{
	if(--dnp->dn_links <= 0 ) /* can be -1 for initial free, on error */
	{
		/*probably need to do other cleanups XXX */
		if (dnp->dn_nextsibling != dnp) {
			devnode_t * * 	prevp = dnp->dn_prevsiblingp;
			*prevp = dnp->dn_nextsibling;
			dnp->dn_nextsibling->dn_prevsiblingp = prevp;
			
		}

		/* Can only free if there are no references; otherwise, wait for last vnode to be reclaimed */
		if (dnp->dn_refcount == 0) {
		    devnode_free(dnp); 
		}
		else {
		    dnp->dn_lflags |= DN_DELETE;
		}
	}
}