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
typedef  int /*<<< orphan*/  uint ;
struct xfs_inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 int /*<<< orphan*/  xfs_ilock (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iunlock (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_qm_dqattach_locked (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_qm_need_dqattach (struct xfs_inode*) ; 

int
xfs_qm_dqattach(
	struct xfs_inode	*ip,
	uint			flags)
{
	int			error;

	if (!xfs_qm_need_dqattach(ip))
		return 0;

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	error = xfs_qm_dqattach_locked(ip, flags);
	xfs_iunlock(ip, XFS_ILOCK_EXCL);

	return error;
}