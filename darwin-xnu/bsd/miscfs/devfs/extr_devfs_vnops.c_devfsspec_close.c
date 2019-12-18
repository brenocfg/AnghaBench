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
struct vnop_close_args {struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
typedef  int /*<<< orphan*/  devnode_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFS_LOCK () ; 
 int /*<<< orphan*/  DEVFS_UNLOCK () ; 
 int VOCALL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnop_close_args*) ; 
 int /*<<< orphan*/  VOFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * VTODN (struct vnode*) ; 
 int /*<<< orphan*/  dn_times_now (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spec_vnodeop_p ; 
 scalar_t__ vnode_isinuse (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnop_close ; 

__attribute__((used)) static int
devfsspec_close(struct vnop_close_args *ap)
        /* struct vnop_close_args {
		struct vnode *a_vp;
		int  a_fflag;
		vfs_context_t a_context;
	} */
{
    	struct vnode *	    	vp = ap->a_vp;
	devnode_t * 	dnp;

	if (vnode_isinuse(vp, 0)) {
	    DEVFS_LOCK();
	    dnp = VTODN(vp);
	    if (dnp)
	        dn_times_now(dnp, 0);
	    DEVFS_UNLOCK();
	}

	return (VOCALL (spec_vnodeop_p, VOFFSET(vnop_close), ap));
}