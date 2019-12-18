#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  i_mount; } ;
typedef  TYPE_1__ xfs_inode_t ;
typedef  int /*<<< orphan*/  xfs_ino_t ;
typedef  int /*<<< orphan*/  uint ;
struct xfs_name {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_lookup (TYPE_1__*,struct xfs_name*) ; 
 int xfs_dir_lookup (int /*<<< orphan*/ *,TYPE_1__*,struct xfs_name*,int /*<<< orphan*/ *,struct xfs_name*) ; 
 int xfs_iget (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  xfs_ilock_map_shared (TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_iunlock_map_shared (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
xfs_lookup(
	xfs_inode_t		*dp,
	struct xfs_name		*name,
	xfs_inode_t		**ipp,
	struct xfs_name		*ci_name)
{
	xfs_ino_t		inum;
	int			error;
	uint			lock_mode;

	trace_xfs_lookup(dp, name);

	if (XFS_FORCED_SHUTDOWN(dp->i_mount))
		return XFS_ERROR(EIO);

	lock_mode = xfs_ilock_map_shared(dp);
	error = xfs_dir_lookup(NULL, dp, name, &inum, ci_name);
	xfs_iunlock_map_shared(dp, lock_mode);

	if (error)
		goto out;

	error = xfs_iget(dp->i_mount, NULL, inum, 0, 0, ipp);
	if (error)
		goto out_free_name;

	return 0;

out_free_name:
	if (ci_name)
		kmem_free(ci_name->name);
out:
	*ipp = NULL;
	return error;
}