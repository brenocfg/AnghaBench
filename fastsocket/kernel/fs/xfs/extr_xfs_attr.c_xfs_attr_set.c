#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  i_mount; } ;
typedef  TYPE_1__ xfs_inode_t ;
struct xfs_name {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_STATS_INC (int /*<<< orphan*/ ) ; 
 int xfs_attr_name_to_xname (struct xfs_name*,unsigned char const*) ; 
 int xfs_attr_set_int (TYPE_1__*,struct xfs_name*,unsigned char*,int,int) ; 
 int /*<<< orphan*/  xs_attr_set ; 

int
xfs_attr_set(
	xfs_inode_t	*dp,
	const unsigned char *name,
	unsigned char	*value,
	int		valuelen,
	int		flags)
{
	int             error;
	struct xfs_name	xname;

	XFS_STATS_INC(xs_attr_set);

	if (XFS_FORCED_SHUTDOWN(dp->i_mount))
		return (EIO);

	error = xfs_attr_name_to_xname(&xname, name);
	if (error)
		return error;

	return xfs_attr_set_int(dp, &xname, value, valuelen, flags);
}