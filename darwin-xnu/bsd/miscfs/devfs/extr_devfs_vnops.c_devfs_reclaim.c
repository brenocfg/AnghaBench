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
struct vnop_reclaim_args {struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * dn_vn; } ;
typedef  TYPE_1__ devnode_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFS_LOCK () ; 
 int /*<<< orphan*/  DEVFS_UNLOCK () ; 
 TYPE_1__* VTODN (struct vnode*) ; 
 int /*<<< orphan*/  devfs_rele_node (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_clearfsnode (struct vnode*) ; 

__attribute__((used)) static int
devfs_reclaim(struct vnop_reclaim_args *ap)
        /*struct vnop_reclaim_args {
		struct vnode *a_vp;
        } */
{
    struct vnode *	vp = ap->a_vp;
    devnode_t * 	dnp;
    
    DEVFS_LOCK();

    dnp = VTODN(vp);

    if (dnp) {
	/* If this is a cloning device, it didn't have a dn_vn anyway */
	dnp->dn_vn = NULL;
	vnode_clearfsnode(vp);

	/* This could delete the node, if we are the last vnode */
	devfs_rele_node(dnp);
    }
    DEVFS_UNLOCK();

    return(0);
}