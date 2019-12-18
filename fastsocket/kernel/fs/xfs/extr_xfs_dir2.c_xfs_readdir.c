#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_off_t ;
struct TYPE_9__ {int di_mode; scalar_t__ di_format; } ;
struct TYPE_10__ {TYPE_1__ i_d; int /*<<< orphan*/  i_mount; } ;
typedef  TYPE_2__ xfs_inode_t ;
typedef  int /*<<< orphan*/  filldir_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  EIO ; 
 int S_IFDIR ; 
 int S_IFMT ; 
 scalar_t__ XFS_DINODE_FMT_LOCAL ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_STATS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_readdir (TYPE_2__*) ; 
 int xfs_dir2_block_getdents (TYPE_2__*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xfs_dir2_isblock (int /*<<< orphan*/ *,TYPE_2__*,int*) ; 
 int xfs_dir2_leaf_getdents (TYPE_2__*,void*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xfs_dir2_sf_getdents (TYPE_2__*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xs_dir_getdents ; 

int
xfs_readdir(
	xfs_inode_t	*dp,
	void		*dirent,
	size_t		bufsize,
	xfs_off_t	*offset,
	filldir_t	filldir)
{
	int		rval;		/* return value */
	int		v;		/* type-checking value */

	trace_xfs_readdir(dp);

	if (XFS_FORCED_SHUTDOWN(dp->i_mount))
		return XFS_ERROR(EIO);

	ASSERT((dp->i_d.di_mode & S_IFMT) == S_IFDIR);
	XFS_STATS_INC(xs_dir_getdents);

	if (dp->i_d.di_format == XFS_DINODE_FMT_LOCAL)
		rval = xfs_dir2_sf_getdents(dp, dirent, offset, filldir);
	else if ((rval = xfs_dir2_isblock(NULL, dp, &v)))
		;
	else if (v)
		rval = xfs_dir2_block_getdents(dp, dirent, offset, filldir);
	else
		rval = xfs_dir2_leaf_getdents(dp, dirent, bufsize, offset,
					      filldir);
	return rval;
}