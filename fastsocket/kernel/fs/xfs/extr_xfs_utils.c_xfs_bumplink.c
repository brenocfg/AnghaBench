#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_8__ {scalar_t__ di_nlink; int di_version; } ;
struct TYPE_9__ {TYPE_1__ i_d; } ;
typedef  TYPE_2__ xfs_inode_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  EMLINK ; 
 int /*<<< orphan*/  VFS_I (TYPE_2__*) ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_ICHGTIME_CHG ; 
 int /*<<< orphan*/  XFS_ILOG_CORE ; 
 scalar_t__ XFS_MAXLINK ; 
 scalar_t__ XFS_MAXLINK_1 ; 
 int /*<<< orphan*/  inc_nlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_bump_ino_vers2 (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  xfs_trans_ichgtime (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_log_inode (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

int
xfs_bumplink(
	xfs_trans_t *tp,
	xfs_inode_t *ip)
{
	if (ip->i_d.di_nlink >= XFS_MAXLINK)
		return XFS_ERROR(EMLINK);
	xfs_trans_ichgtime(tp, ip, XFS_ICHGTIME_CHG);

	ASSERT(ip->i_d.di_nlink > 0);
	ip->i_d.di_nlink++;
	inc_nlink(VFS_I(ip));
	if ((ip->i_d.di_version == 1) &&
	    (ip->i_d.di_nlink > XFS_MAXLINK_1)) {
		/*
		 * The inode has increased its number of links beyond
		 * what can fit in an old format inode.  It now needs
		 * to be converted to a version 2 inode with a 32 bit
		 * link count.  If this is the first inode in the file
		 * system to do this, then we need to bump the superblock
		 * version number as well.
		 */
		xfs_bump_ino_vers2(tp, ip);
	}

	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);
	return 0;
}