#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vfs_context_t ;
struct vnode {TYPE_2__* v_mount; } ;
struct TYPE_4__ {TYPE_1__* mnt_op; } ;
struct TYPE_3__ {int (* vfs_vptofh ) (struct vnode*,int*,unsigned char*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ENOTSUP ; 
 TYPE_2__* dead_mountp ; 
 int stub1 (struct vnode*,int*,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vfs_context_current () ; 

int 
VFS_VPTOFH(struct vnode *vp, int *fhlenp, unsigned char *fhp, vfs_context_t ctx)
{
	int error;

	if ((vp->v_mount == dead_mountp) || (vp->v_mount->mnt_op->vfs_vptofh == 0))
		return(ENOTSUP);

	if (ctx == NULL) {
		ctx = vfs_context_current();
	}

	error = (*vp->v_mount->mnt_op->vfs_vptofh)(vp, fhlenp, fhp, ctx);

	return(error);
}