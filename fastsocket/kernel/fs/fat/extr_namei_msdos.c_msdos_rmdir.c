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
struct super_block {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ctime; struct super_block* i_sb; } ;
struct fat_slot_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME_SEC ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  fat_detach (struct inode*) ; 
 int fat_dir_empty (struct inode*) ; 
 int fat_flush_inodes (struct super_block*,struct inode*,struct inode*) ; 
 int fat_remove_entries (struct inode*,struct fat_slot_info*) ; 
 int /*<<< orphan*/  lock_super (struct super_block*) ; 
 int msdos_find (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fat_slot_info*) ; 
 int /*<<< orphan*/  unlock_super (struct super_block*) ; 

__attribute__((used)) static int msdos_rmdir(struct inode *dir, struct dentry *dentry)
{
	struct super_block *sb = dir->i_sb;
	struct inode *inode = dentry->d_inode;
	struct fat_slot_info sinfo;
	int err;

	lock_super(sb);
	/*
	 * Check whether the directory is not in use, then check
	 * whether it is empty.
	 */
	err = fat_dir_empty(inode);
	if (err)
		goto out;
	err = msdos_find(dir, dentry->d_name.name, dentry->d_name.len, &sinfo);
	if (err)
		goto out;

	err = fat_remove_entries(dir, &sinfo);	/* and releases bh */
	if (err)
		goto out;
	drop_nlink(dir);

	clear_nlink(inode);
	inode->i_ctime = CURRENT_TIME_SEC;
	fat_detach(inode);
out:
	unlock_super(sb);
	if (!err)
		err = fat_flush_inodes(sb, dir, inode);

	return err;
}