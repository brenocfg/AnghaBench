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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct super_block {int dummy; } ;
struct inode {scalar_t__ i_ino; struct super_block* i_sb; } ;
struct TYPE_4__ {scalar_t__ len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_2__* d_inode; TYPE_1__ d_name; } ;
struct buffer_head {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 TYPE_3__* AFFS_TAIL (struct super_block*,struct buffer_head*) ; 
 int EIO ; 
 struct buffer_head* affs_bread (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  affs_brelse (struct buffer_head*) ; 
 int affs_check_name (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  affs_copy_name (int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  affs_fix_checksum (struct super_block*,struct buffer_head*) ; 
 int affs_insert_hash (struct inode*,struct buffer_head*) ; 
 int /*<<< orphan*/  affs_lock_dir (struct inode*) ; 
 int affs_remove_hash (struct inode*,struct buffer_head*) ; 
 int affs_remove_header (struct dentry*) ; 
 int /*<<< orphan*/  affs_unlock_dir (struct inode*) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (struct buffer_head*,struct inode*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
affs_rename(struct inode *old_dir, struct dentry *old_dentry,
	    struct inode *new_dir, struct dentry *new_dentry)
{
	struct super_block *sb = old_dir->i_sb;
	struct buffer_head *bh = NULL;
	int retval;

	pr_debug("AFFS: rename(old=%u,\"%*s\" to new=%u,\"%*s\")\n",
		 (u32)old_dir->i_ino, (int)old_dentry->d_name.len, old_dentry->d_name.name,
		 (u32)new_dir->i_ino, (int)new_dentry->d_name.len, new_dentry->d_name.name);

	retval = affs_check_name(new_dentry->d_name.name,new_dentry->d_name.len);
	if (retval)
		return retval;

	/* Unlink destination if it already exists */
	if (new_dentry->d_inode) {
		retval = affs_remove_header(new_dentry);
		if (retval)
			return retval;
	}

	bh = affs_bread(sb, old_dentry->d_inode->i_ino);
	if (!bh)
		return -EIO;

	/* Remove header from its parent directory. */
	affs_lock_dir(old_dir);
	retval = affs_remove_hash(old_dir, bh);
	affs_unlock_dir(old_dir);
	if (retval)
		goto done;

	/* And insert it into the new directory with the new name. */
	affs_copy_name(AFFS_TAIL(sb, bh)->name, new_dentry);
	affs_fix_checksum(sb, bh);
	affs_lock_dir(new_dir);
	retval = affs_insert_hash(new_dir, bh);
	affs_unlock_dir(new_dir);
	/* TODO: move it back to old_dir, if error? */

done:
	mark_buffer_dirty_inode(bh, retval ? old_dir : new_dir);
	affs_brelse(bh);
	return retval;
}