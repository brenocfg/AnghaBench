#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct inode {scalar_t__ i_ino; int i_nlink; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; scalar_t__ i_size; int /*<<< orphan*/  i_version; int /*<<< orphan*/  i_sb; } ;
struct ext3_dir_entry_2 {int /*<<< orphan*/  inode; } ;
struct dentry {struct inode* d_inode; int /*<<< orphan*/  d_name; } ;
struct buffer_head {int dummy; } ;
struct TYPE_9__ {int h_sync; } ;
typedef  TYPE_1__ handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME_SEC ; 
 int EIO ; 
 int ENOENT ; 
 int ENOTEMPTY ; 
 int /*<<< orphan*/  EXT3_DELETE_TRANS_BLOCKS (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_DIRSYNC (struct inode*) ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  empty_dir (struct inode*) ; 
 int ext3_delete_entry (TYPE_1__*,struct inode*,struct ext3_dir_entry_2*,struct buffer_head*) ; 
 struct buffer_head* ext3_find_entry (struct inode*,int /*<<< orphan*/ *,struct ext3_dir_entry_2**) ; 
 TYPE_1__* ext3_journal_start (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext3_journal_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  ext3_mark_inode_dirty (TYPE_1__*,struct inode*) ; 
 int /*<<< orphan*/  ext3_orphan_add (TYPE_1__*,struct inode*) ; 
 int /*<<< orphan*/  ext3_update_dx_flag (struct inode*) ; 
 int /*<<< orphan*/  ext3_warning (int /*<<< orphan*/ ,char*,char*,int) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_dq_init (struct inode*) ; 

__attribute__((used)) static int ext3_rmdir (struct inode * dir, struct dentry *dentry)
{
	int retval;
	struct inode * inode;
	struct buffer_head * bh;
	struct ext3_dir_entry_2 * de;
	handle_t *handle;

	/* Initialize quotas before so that eventual writes go in
	 * separate transaction */
	vfs_dq_init(dentry->d_inode);
	handle = ext3_journal_start(dir, EXT3_DELETE_TRANS_BLOCKS(dir->i_sb));
	if (IS_ERR(handle))
		return PTR_ERR(handle);

	retval = -ENOENT;
	bh = ext3_find_entry(dir, &dentry->d_name, &de);
	if (!bh)
		goto end_rmdir;

	if (IS_DIRSYNC(dir))
		handle->h_sync = 1;

	inode = dentry->d_inode;

	retval = -EIO;
	if (le32_to_cpu(de->inode) != inode->i_ino)
		goto end_rmdir;

	retval = -ENOTEMPTY;
	if (!empty_dir (inode))
		goto end_rmdir;

	retval = ext3_delete_entry(handle, dir, de, bh);
	if (retval)
		goto end_rmdir;
	if (inode->i_nlink != 2)
		ext3_warning (inode->i_sb, "ext3_rmdir",
			      "empty directory has nlink!=2 (%d)",
			      inode->i_nlink);
	inode->i_version++;
	clear_nlink(inode);
	/* There's no need to set i_disksize: the fact that i_nlink is
	 * zero will ensure that the right thing happens during any
	 * recovery. */
	inode->i_size = 0;
	ext3_orphan_add(handle, inode);
	inode->i_ctime = dir->i_ctime = dir->i_mtime = CURRENT_TIME_SEC;
	ext3_mark_inode_dirty(handle, inode);
	drop_nlink(dir);
	ext3_update_dx_flag(dir);
	ext3_mark_inode_dirty(handle, dir);

end_rmdir:
	ext3_journal_stop(handle);
	brelse (bh);
	return retval;
}