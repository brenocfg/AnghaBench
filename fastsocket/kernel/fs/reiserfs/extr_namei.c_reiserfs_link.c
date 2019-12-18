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
struct reiserfs_transaction_handle {int dummy; } ;
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_count; int /*<<< orphan*/  i_ctime; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME_SEC ; 
 int EMLINK ; 
 int ENOENT ; 
 int JOURNAL_PER_BALANCE_CNT ; 
 scalar_t__ REISERFS_LINK_MAX ; 
 int REISERFS_QUOTA_TRANS_BLOCKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int journal_begin (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ,int) ; 
 int journal_end (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ,int) ; 
 int reiserfs_add_entry (struct reiserfs_transaction_handle*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inode*,int) ; 
 int /*<<< orphan*/  reiserfs_update_inode_transaction (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_update_sd (struct reiserfs_transaction_handle*,struct inode*) ; 
 int /*<<< orphan*/  reiserfs_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reiserfs_link(struct dentry *old_dentry, struct inode *dir,
			 struct dentry *dentry)
{
	int retval;
	struct inode *inode = old_dentry->d_inode;
	struct reiserfs_transaction_handle th;
	/* We need blocks for transaction + update of quotas for the owners of the directory */
	int jbegin_count =
	    JOURNAL_PER_BALANCE_CNT * 3 +
	    2 * REISERFS_QUOTA_TRANS_BLOCKS(dir->i_sb);

	reiserfs_write_lock(dir->i_sb);
	if (inode->i_nlink >= REISERFS_LINK_MAX) {
		//FIXME: sd_nlink is 32 bit for new files
		reiserfs_write_unlock(dir->i_sb);
		return -EMLINK;
	}
	if (inode->i_nlink == 0) {
		reiserfs_write_unlock(dir->i_sb);
		return -ENOENT;
	}

	/* inc before scheduling so reiserfs_unlink knows we are here */
	inc_nlink(inode);

	retval = journal_begin(&th, dir->i_sb, jbegin_count);
	if (retval) {
		inode->i_nlink--;
		reiserfs_write_unlock(dir->i_sb);
		return retval;
	}

	/* create new entry */
	retval =
	    reiserfs_add_entry(&th, dir, dentry->d_name.name,
			       dentry->d_name.len, inode, 1 /*visible */ );

	reiserfs_update_inode_transaction(inode);
	reiserfs_update_inode_transaction(dir);

	if (retval) {
		int err;
		inode->i_nlink--;
		err = journal_end(&th, dir->i_sb, jbegin_count);
		reiserfs_write_unlock(dir->i_sb);
		return err ? err : retval;
	}

	inode->i_ctime = CURRENT_TIME_SEC;
	reiserfs_update_sd(&th, inode);

	atomic_inc(&inode->i_count);
	d_instantiate(dentry, inode);
	retval = journal_end(&th, dir->i_sb, jbegin_count);
	reiserfs_write_unlock(dir->i_sb);
	return retval;
}