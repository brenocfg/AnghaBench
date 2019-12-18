#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct jfs_sb_info {scalar_t__ state; TYPE_3__* ipbmap; TYPE_1__* ipimap; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_mapping; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FM_CLEAN ; 
 int /*<<< orphan*/  FM_MOUNT ; 
 struct jfs_sb_info* JFS_SBI (struct super_block*) ; 
 scalar_t__ chkSuper (struct super_block*) ; 
 int dbMount (TYPE_3__*) ; 
 int /*<<< orphan*/  dbUnmount (TYPE_3__*,int) ; 
 int diMount (TYPE_1__*) ; 
 int /*<<< orphan*/  diUnmount (TYPE_1__*,int) ; 
 int /*<<< orphan*/  jfs_err (char*,...) ; 
 int /*<<< orphan*/  lmLogClose (struct super_block*) ; 
 int lmLogOpen (struct super_block*) ; 
 int /*<<< orphan*/  logMOUNT (struct super_block*) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int updateSuper (struct super_block*,int /*<<< orphan*/ ) ; 

int jfs_mount_rw(struct super_block *sb, int remount)
{
	struct jfs_sb_info *sbi = JFS_SBI(sb);
	int rc;

	/*
	 * If we are re-mounting a previously read-only volume, we want to
	 * re-read the inode and block maps, since fsck.jfs may have updated
	 * them.
	 */
	if (remount) {
		if (chkSuper(sb) || (sbi->state != FM_CLEAN))
			return -EINVAL;

		truncate_inode_pages(sbi->ipimap->i_mapping, 0);
		truncate_inode_pages(sbi->ipbmap->i_mapping, 0);
		diUnmount(sbi->ipimap, 1);
		if ((rc = diMount(sbi->ipimap))) {
			jfs_err("jfs_mount_rw: diMount failed!");
			return rc;
		}

		dbUnmount(sbi->ipbmap, 1);
		if ((rc = dbMount(sbi->ipbmap))) {
			jfs_err("jfs_mount_rw: dbMount failed!");
			return rc;
		}
	}

	/*
	 * open/initialize log
	 */
	if ((rc = lmLogOpen(sb)))
		return rc;

	/*
	 * update file system superblock;
	 */
	if ((rc = updateSuper(sb, FM_MOUNT))) {
		jfs_err("jfs_mount: updateSuper failed w/rc = %d", rc);
		lmLogClose(sb);
		return rc;
	}

	/*
	 * write MOUNT log record of the file system
	 */
	logMOUNT(sb);

	return rc;
}