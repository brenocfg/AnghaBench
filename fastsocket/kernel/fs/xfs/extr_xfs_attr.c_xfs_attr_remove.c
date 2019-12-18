#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  i_mount; } ;
typedef  TYPE_1__ xfs_inode_t ;
struct xfs_name {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ENOATTR ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_ILOCK_SHARED ; 
 int /*<<< orphan*/  XFS_STATS_INC (int /*<<< orphan*/ ) ; 
 int xfs_attr_name_to_xname (struct xfs_name*,unsigned char const*) ; 
 int xfs_attr_remove_int (TYPE_1__*,struct xfs_name*,int) ; 
 int /*<<< orphan*/  xfs_ilock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_inode_hasattr (TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_iunlock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xs_attr_remove ; 

int
xfs_attr_remove(
	xfs_inode_t	*dp,
	const unsigned char *name,
	int		flags)
{
	int		error;
	struct xfs_name	xname;

	XFS_STATS_INC(xs_attr_remove);

	if (XFS_FORCED_SHUTDOWN(dp->i_mount))
		return (EIO);

	error = xfs_attr_name_to_xname(&xname, name);
	if (error)
		return error;

	xfs_ilock(dp, XFS_ILOCK_SHARED);
	if (!xfs_inode_hasattr(dp)) {
		xfs_iunlock(dp, XFS_ILOCK_SHARED);
		return XFS_ERROR(ENOATTR);
	}
	xfs_iunlock(dp, XFS_ILOCK_SHARED);

	return xfs_attr_remove_int(dp, &xname, flags);
}