#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct inode {scalar_t__ i_ino; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; scalar_t__ i_size; int /*<<< orphan*/  i_version; int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_sb; } ;
struct ext4_dir_entry_2 {int /*<<< orphan*/  inode; } ;
struct dentry {struct inode* d_inode; int /*<<< orphan*/  d_name; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 int ENOTEMPTY ; 
 int /*<<< orphan*/  EXT4_DELETE_TRANS_BLOCKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT4_DIR_LINK_EMPTY (struct inode*) ; 
 scalar_t__ IS_DIRSYNC (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  empty_dir (struct inode*) ; 
 int /*<<< orphan*/  ext4_current_time (struct inode*) ; 
 int /*<<< orphan*/  ext4_dec_count (int /*<<< orphan*/ *,struct inode*) ; 
 int ext4_delete_entry (int /*<<< orphan*/ *,struct inode*,struct ext4_dir_entry_2*,struct buffer_head*) ; 
 struct buffer_head* ext4_find_entry (struct inode*,int /*<<< orphan*/ *,struct ext4_dir_entry_2**) ; 
 int /*<<< orphan*/  ext4_handle_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_orphan_add (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_update_dx_flag (struct inode*) ; 
 int /*<<< orphan*/  ext4_warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_dq_init (struct inode*) ; 

__attribute__((used)) static int ext4_rmdir(struct inode *dir, struct dentry *dentry)
{
	int retval;
	struct inode *inode;
	struct buffer_head *bh;
	struct ext4_dir_entry_2 *de;
	handle_t *handle;

	/* Initialize quotas before so that eventual writes go in
	 * separate transaction */
	vfs_dq_init(dentry->d_inode);
	handle = ext4_journal_start(dir, EXT4_DELETE_TRANS_BLOCKS(dir->i_sb));
	if (IS_ERR(handle))
		return PTR_ERR(handle);

	retval = -ENOENT;
	bh = ext4_find_entry(dir, &dentry->d_name, &de);
	if (!bh)
		goto end_rmdir;

	if (IS_DIRSYNC(dir))
		ext4_handle_sync(handle);

	inode = dentry->d_inode;

	retval = -EIO;
	if (le32_to_cpu(de->inode) != inode->i_ino)
		goto end_rmdir;

	retval = -ENOTEMPTY;
	if (!empty_dir(inode))
		goto end_rmdir;

	retval = ext4_delete_entry(handle, dir, de, bh);
	if (retval)
		goto end_rmdir;
	if (!EXT4_DIR_LINK_EMPTY(inode))
		ext4_warning(inode->i_sb,
			     "empty directory has too many links (%d)",
			     inode->i_nlink);
	inode->i_version++;
	clear_nlink(inode);
	/* There's no need to set i_disksize: the fact that i_nlink is
	 * zero will ensure that the right thing happens during any
	 * recovery. */
	inode->i_size = 0;
	ext4_orphan_add(handle, inode);
	inode->i_ctime = dir->i_ctime = dir->i_mtime = ext4_current_time(inode);
	ext4_mark_inode_dirty(handle, inode);
	ext4_dec_count(handle, dir);
	ext4_update_dx_flag(dir);
	ext4_mark_inode_dirty(handle, dir);

end_rmdir:
	ext4_journal_stop(handle);
	brelse(bh);
	return retval;
}