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
typedef  int /*<<< orphan*/  tid_t ;
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  commit_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_Dirty ; 
 int /*<<< orphan*/  COMMIT_INODE ; 
 int /*<<< orphan*/  COMMIT_SYNC ; 
 TYPE_1__* JFS_IP (struct inode*) ; 
 scalar_t__ isReadOnly (struct inode*) ; 
 int /*<<< orphan*/  jfs_err (char*,...) ; 
 int /*<<< orphan*/  jfs_info (char*,struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  special_file (int /*<<< orphan*/ ) ; 
 scalar_t__ test_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  txBegin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int txCommit (int /*<<< orphan*/ ,int,struct inode**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txEnd (int /*<<< orphan*/ ) ; 

int jfs_commit_inode(struct inode *inode, int wait)
{
	int rc = 0;
	tid_t tid;
	static int noisy = 5;

	jfs_info("In jfs_commit_inode, inode = 0x%p", inode);

	/*
	 * Don't commit if inode has been committed since last being
	 * marked dirty, or if it has been deleted.
	 */
	if (inode->i_nlink == 0 || !test_cflag(COMMIT_Dirty, inode))
		return 0;

	if (isReadOnly(inode)) {
		/* kernel allows writes to devices on read-only
		 * partitions and may think inode is dirty
		 */
		if (!special_file(inode->i_mode) && noisy) {
			jfs_err("jfs_commit_inode(0x%p) called on "
				   "read-only volume", inode);
			jfs_err("Is remount racy?");
			noisy--;
		}
		return 0;
	}

	tid = txBegin(inode->i_sb, COMMIT_INODE);
	mutex_lock(&JFS_IP(inode)->commit_mutex);

	/*
	 * Retest inode state after taking commit_mutex
	 */
	if (inode->i_nlink && test_cflag(COMMIT_Dirty, inode))
		rc = txCommit(tid, 1, &inode, wait ? COMMIT_SYNC : 0);

	txEnd(tid);
	mutex_unlock(&JFS_IP(inode)->commit_mutex);
	return rc;
}