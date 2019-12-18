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
struct super_block {int dummy; } ;
struct inode {int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; struct super_block* i_sb; } ;
struct fat_slot_info {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_name; struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME_SEC ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  fat_detach (struct inode*) ; 
 int fat_dir_empty (struct inode*) ; 
 int fat_remove_entries (struct inode*,struct fat_slot_info*) ; 
 int /*<<< orphan*/  lock_super (struct super_block*) ; 
 int /*<<< orphan*/  unlock_super (struct super_block*) ; 
 int vfat_find (struct inode*,int /*<<< orphan*/ *,struct fat_slot_info*) ; 

__attribute__((used)) static int vfat_rmdir(struct inode *dir, struct dentry *dentry)
{
	struct inode *inode = dentry->d_inode;
	struct super_block *sb = dir->i_sb;
	struct fat_slot_info sinfo;
	int err;

	lock_super(sb);

	err = fat_dir_empty(inode);
	if (err)
		goto out;
	err = vfat_find(dir, &dentry->d_name, &sinfo);
	if (err)
		goto out;

	err = fat_remove_entries(dir, &sinfo);	/* and releases bh */
	if (err)
		goto out;
	drop_nlink(dir);

	clear_nlink(inode);
	inode->i_mtime = inode->i_atime = CURRENT_TIME_SEC;
	fat_detach(inode);
out:
	unlock_super(sb);

	return err;
}