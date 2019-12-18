#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ di_aformat; } ;
struct TYPE_13__ {TYPE_1__ i_d; int /*<<< orphan*/  i_mount; } ;
typedef  TYPE_2__ xfs_inode_t ;
struct TYPE_14__ {TYPE_2__* dp; } ;
typedef  TYPE_3__ xfs_attr_list_context_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  XFS_ATTR_FORK ; 
 scalar_t__ XFS_DINODE_FMT_LOCAL ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_ILOCK_SHARED ; 
 int /*<<< orphan*/  XFS_STATS_INC (int /*<<< orphan*/ ) ; 
 int xfs_attr_leaf_list (TYPE_3__*) ; 
 int xfs_attr_node_list (TYPE_3__*) ; 
 int xfs_attr_shortform_list (TYPE_3__*) ; 
 scalar_t__ xfs_bmap_one_block (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_ilock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_inode_hasattr (TYPE_2__*) ; 
 int /*<<< orphan*/  xfs_iunlock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xs_attr_list ; 

int
xfs_attr_list_int(xfs_attr_list_context_t *context)
{
	int error;
	xfs_inode_t *dp = context->dp;

	XFS_STATS_INC(xs_attr_list);

	if (XFS_FORCED_SHUTDOWN(dp->i_mount))
		return EIO;

	xfs_ilock(dp, XFS_ILOCK_SHARED);

	/*
	 * Decide on what work routines to call based on the inode size.
	 */
	if (!xfs_inode_hasattr(dp)) {
		error = 0;
	} else if (dp->i_d.di_aformat == XFS_DINODE_FMT_LOCAL) {
		error = xfs_attr_shortform_list(context);
	} else if (xfs_bmap_one_block(dp, XFS_ATTR_FORK)) {
		error = xfs_attr_leaf_list(context);
	} else {
		error = xfs_attr_node_list(context);
	}

	xfs_iunlock(dp, XFS_ILOCK_SHARED);

	return error;
}