#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vfs_context_t ;
typedef  int /*<<< orphan*/  u_long ;
struct mount {TYPE_1__* mnt_op; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {int (* vfs_ioctl ) (struct mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOTSUP ; 
 struct mount* dead_mountp ; 
 int stub1 (struct mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_current () ; 

int VFS_IOCTL(struct mount *mp, u_long command, caddr_t data,
			  int flags, vfs_context_t context)
{
	if (mp == dead_mountp || !mp->mnt_op->vfs_ioctl)
		return ENOTSUP;

	return mp->mnt_op->vfs_ioctl(mp, command, data, flags,
								 context ?: vfs_context_current());
}