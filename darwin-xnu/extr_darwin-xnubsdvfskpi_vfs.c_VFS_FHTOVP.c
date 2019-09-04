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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/ * vfs_context_t ;
typedef  TYPE_2__* mount_t ;
struct TYPE_7__ {TYPE_1__* mnt_op; } ;
struct TYPE_6__ {int (* vfs_fhtovp ) (TYPE_2__*,int,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ENOTSUP ; 
 TYPE_2__* dead_mountp ; 
 int stub1 (TYPE_2__*,int,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vfs_context_current () ; 

int 
VFS_FHTOVP(mount_t mp, int fhlen, unsigned char *fhp, vnode_t *vpp, vfs_context_t ctx) 
{
	int error;

	if ((mp == dead_mountp) || (mp->mnt_op->vfs_fhtovp == 0))
		return(ENOTSUP);

	if (ctx == NULL) {
		ctx = vfs_context_current();
	}

	error = (*mp->mnt_op->vfs_fhtovp)(mp, fhlen, fhp, vpp, ctx);

	return(error);
}