#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_count; int /*<<< orphan*/  i_ctime; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_8__ {int h_sync; } ;
typedef  TYPE_1__ handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME_SEC ; 
 int EMLINK ; 
 int ENOENT ; 
 int ENOSPC ; 
 scalar_t__ EXT3_DATA_TRANS_BLOCKS (int /*<<< orphan*/ ) ; 
 scalar_t__ EXT3_INDEX_EXTRA_TRANS_BLOCKS ; 
 scalar_t__ EXT3_LINK_MAX ; 
 scalar_t__ IS_DIRSYNC (struct inode*) ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int ext3_add_entry (TYPE_1__*,struct dentry*,struct inode*) ; 
 TYPE_1__* ext3_journal_start (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  ext3_journal_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  ext3_mark_inode_dirty (TYPE_1__*,struct inode*) ; 
 scalar_t__ ext3_should_retry_alloc (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 

__attribute__((used)) static int ext3_link (struct dentry * old_dentry,
		struct inode * dir, struct dentry *dentry)
{
	handle_t *handle;
	struct inode *inode = old_dentry->d_inode;
	int err, retries = 0;

	if (inode->i_nlink >= EXT3_LINK_MAX)
		return -EMLINK;
	/*
	 * Return -ENOENT if we've raced with unlink and i_nlink is 0.  Doing
	 * otherwise has the potential to corrupt the orphan inode list.
	 */
	if (inode->i_nlink == 0)
		return -ENOENT;

retry:
	handle = ext3_journal_start(dir, EXT3_DATA_TRANS_BLOCKS(dir->i_sb) +
					EXT3_INDEX_EXTRA_TRANS_BLOCKS);
	if (IS_ERR(handle))
		return PTR_ERR(handle);

	if (IS_DIRSYNC(dir))
		handle->h_sync = 1;

	inode->i_ctime = CURRENT_TIME_SEC;
	inc_nlink(inode);
	atomic_inc(&inode->i_count);

	err = ext3_add_entry(handle, dentry, inode);
	if (!err) {
		ext3_mark_inode_dirty(handle, inode);
		d_instantiate(dentry, inode);
	} else {
		drop_nlink(inode);
		iput(inode);
	}
	ext3_journal_stop(handle);
	if (err == -ENOSPC && ext3_should_retry_alloc(dir->i_sb, &retries))
		goto retry;
	return err;
}