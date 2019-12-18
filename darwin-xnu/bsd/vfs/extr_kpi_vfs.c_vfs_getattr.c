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
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vfs_attr {int /*<<< orphan*/  f_create_time; } ;
typedef  int /*<<< orphan*/  mount_t ;

/* Variables and functions */
 scalar_t__ VFSATTR_IS_ACTIVE (struct vfs_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ VFSATTR_IS_SUPPORTED (struct vfs_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFSATTR_RETURN (struct vfs_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VFS_GETATTR (int /*<<< orphan*/ ,struct vfs_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_create_time ; 
 int /*<<< orphan*/  f_modify_time ; 

int
vfs_getattr(mount_t mp, struct vfs_attr *vfa, vfs_context_t ctx)
{
	int		error;

	if ((error = VFS_GETATTR(mp, vfa, ctx)) != 0)
		return(error);

	/*
 	 * If we have a filesystem create time, use it to default some others.
 	 */
 	if (VFSATTR_IS_SUPPORTED(vfa, f_create_time)) {
 		if (VFSATTR_IS_ACTIVE(vfa, f_modify_time) && !VFSATTR_IS_SUPPORTED(vfa, f_modify_time))
 			VFSATTR_RETURN(vfa, f_modify_time, vfa->f_create_time);
 	}

	return(0);
}