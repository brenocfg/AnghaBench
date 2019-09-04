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
struct vnop_write_args {int /*<<< orphan*/  a_vp; } ;
typedef  int /*<<< orphan*/  devnode_t ;

/* Variables and functions */
 int DEVFS_UPDATE_CHANGE ; 
 int DEVFS_UPDATE_MOD ; 
 int VOCALL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnop_write_args*) ; 
 int /*<<< orphan*/  VOFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * VTODN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devfs_consider_time_update (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spec_vnodeop_p ; 
 int /*<<< orphan*/  vnop_write ; 

__attribute__((used)) static int
devfsspec_write(struct vnop_write_args *ap)
        /* struct vnop_write_args  {
                struct vnode *a_vp;
                struct uio *a_uio;
                int  a_ioflag;
		vfs_context_t a_context;
        } */
{
	devnode_t * 	dnp = VTODN(ap->a_vp);

	devfs_consider_time_update(dnp, DEVFS_UPDATE_CHANGE | DEVFS_UPDATE_MOD);

	return (VOCALL (spec_vnodeop_p, VOFFSET(vnop_write), ap));
}