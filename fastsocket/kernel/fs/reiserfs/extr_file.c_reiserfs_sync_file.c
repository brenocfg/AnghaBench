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
struct inode {TYPE_1__* i_sb; int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_mode; } ;
struct file {int dummy; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkdev_issue_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ reiserfs_barrier_flush (TYPE_1__*) ; 
 int reiserfs_commit_for_inode (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_write_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (TYPE_1__*) ; 
 int sync_mapping_buffers (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reiserfs_sync_file(struct file *filp,
			      struct dentry *dentry, int datasync)
{
	struct inode *inode = dentry->d_inode;
	int err;
	int barrier_done;

	BUG_ON(!S_ISREG(inode->i_mode));
	err = sync_mapping_buffers(inode->i_mapping);
	reiserfs_write_lock(inode->i_sb);
	barrier_done = reiserfs_commit_for_inode(inode);
	reiserfs_write_unlock(inode->i_sb);
	if (barrier_done != 1 && reiserfs_barrier_flush(inode->i_sb))
		blkdev_issue_flush(inode->i_sb->s_bdev, NULL);
	if (barrier_done < 0)
		return barrier_done;
	return (err < 0) ? -EIO : 0;
}