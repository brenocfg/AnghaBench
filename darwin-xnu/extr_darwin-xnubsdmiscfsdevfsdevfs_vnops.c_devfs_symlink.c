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
struct vnop_symlink_args {int /*<<< orphan*/  a_context; int /*<<< orphan*/  a_vpp; int /*<<< orphan*/  a_target; TYPE_2__* a_vap; TYPE_1__* a_cnp; int /*<<< orphan*/  a_dvp; } ;
struct TYPE_7__ {int /*<<< orphan*/  de_dnp; } ;
typedef  TYPE_3__ devdirent_t ;
struct TYPE_6__ {int /*<<< orphan*/  va_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  cn_nameptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFS_LOCK () ; 
 int /*<<< orphan*/  DEVFS_UNLOCK () ; 
 int /*<<< orphan*/  VTODN (int /*<<< orphan*/ ) ; 
 int devfs_dntovn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devfs_make_symlink (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  vfs_context_proc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
devfs_symlink(struct vnop_symlink_args *ap)
        /*struct vnop_symlink_args {
                struct vnode *a_dvp;
                struct vnode **a_vpp;
                struct componentname *a_cnp;
                struct vnode_attr *a_vap;
                char *a_target;
		vfs_context_t a_context;
        } */
{
	int error;
	devdirent_t *newent;

	DEVFS_LOCK();
	error = devfs_make_symlink(VTODN(ap->a_dvp), ap->a_cnp->cn_nameptr, ap->a_vap->va_mode, ap->a_target, &newent);
	
	if (error == 0) {
		error = devfs_dntovn(newent->de_dnp, ap->a_vpp, vfs_context_proc(ap->a_context));
	}

	DEVFS_UNLOCK();

	return error;

}