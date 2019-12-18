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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/ * mount_t ;
typedef  int ino64_t ;
struct TYPE_3__ {int /*<<< orphan*/ * val; } ;
typedef  TYPE_1__ fsid_t ;

/* Variables and functions */
 int EINVAL ; 
 int VFS_ROOT (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int VFS_VGET (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mount_lookupby_volfsid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfs_unbusy (int /*<<< orphan*/ *) ; 

int
vfs_getbyid(fsid_t *fsid, ino64_t ino, vnode_t *vpp, vfs_context_t ctx)
{
	mount_t mp;
	int error;
	
	mp = mount_lookupby_volfsid(fsid->val[0], 1);
	if (mp == NULL) {
		return EINVAL;
	}

	/* Get the target vnode. */
	if (ino == 2) {
		error = VFS_ROOT(mp, vpp, ctx);
	} else {
		error = VFS_VGET(mp, ino, vpp, ctx);
	}

	vfs_unbusy(mp);
	return error;
}