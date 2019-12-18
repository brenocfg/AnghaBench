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
struct page {int dummy; } ;
struct inode {scalar_t__ i_nlink; void* i_ctime; int /*<<< orphan*/  i_mode; } ;
struct ext2_dir_entry_2 {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_name; struct inode* d_inode; } ;

/* Variables and functions */
 void* CURRENT_TIME_SEC ; 
 int EIO ; 
 int EMLINK ; 
 int ENOENT ; 
 int ENOTEMPTY ; 
 scalar_t__ EXT2_LINK_MAX ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int ext2_add_link (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  ext2_delete_entry (struct ext2_dir_entry_2*,struct page*) ; 
 struct ext2_dir_entry_2* ext2_dotdot (struct inode*,struct page**) ; 
 int /*<<< orphan*/  ext2_empty_dir (struct inode*) ; 
 struct ext2_dir_entry_2* ext2_find_entry (struct inode*,int /*<<< orphan*/ *,struct page**) ; 
 int /*<<< orphan*/  ext2_set_link (struct inode*,struct ext2_dir_entry_2*,struct page*,struct inode*,int) ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 int /*<<< orphan*/  inode_inc_link_count (struct inode*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 

__attribute__((used)) static int ext2_rename (struct inode * old_dir, struct dentry * old_dentry,
	struct inode * new_dir,	struct dentry * new_dentry )
{
	struct inode * old_inode = old_dentry->d_inode;
	struct inode * new_inode = new_dentry->d_inode;
	struct page * dir_page = NULL;
	struct ext2_dir_entry_2 * dir_de = NULL;
	struct page * old_page;
	struct ext2_dir_entry_2 * old_de;
	int err = -ENOENT;

	old_de = ext2_find_entry (old_dir, &old_dentry->d_name, &old_page);
	if (!old_de)
		goto out;

	if (S_ISDIR(old_inode->i_mode)) {
		err = -EIO;
		dir_de = ext2_dotdot(old_inode, &dir_page);
		if (!dir_de)
			goto out_old;
	}

	if (new_inode) {
		struct page *new_page;
		struct ext2_dir_entry_2 *new_de;

		err = -ENOTEMPTY;
		if (dir_de && !ext2_empty_dir (new_inode))
			goto out_dir;

		err = -ENOENT;
		new_de = ext2_find_entry (new_dir, &new_dentry->d_name, &new_page);
		if (!new_de)
			goto out_dir;
		inode_inc_link_count(old_inode);
		ext2_set_link(new_dir, new_de, new_page, old_inode, 1);
		new_inode->i_ctime = CURRENT_TIME_SEC;
		if (dir_de)
			drop_nlink(new_inode);
		inode_dec_link_count(new_inode);
	} else {
		if (dir_de) {
			err = -EMLINK;
			if (new_dir->i_nlink >= EXT2_LINK_MAX)
				goto out_dir;
		}
		inode_inc_link_count(old_inode);
		err = ext2_add_link(new_dentry, old_inode);
		if (err) {
			inode_dec_link_count(old_inode);
			goto out_dir;
		}
		if (dir_de)
			inode_inc_link_count(new_dir);
	}

	/*
	 * Like most other Unix systems, set the ctime for inodes on a
 	 * rename.
	 * inode_dec_link_count() will mark the inode dirty.
	 */
	old_inode->i_ctime = CURRENT_TIME_SEC;

	ext2_delete_entry (old_de, old_page);
	inode_dec_link_count(old_inode);

	if (dir_de) {
		if (old_dir != new_dir)
			ext2_set_link(old_inode, dir_de, dir_page, new_dir, 0);
		else {
			kunmap(dir_page);
			page_cache_release(dir_page);
		}
		inode_dec_link_count(old_dir);
	}
	return 0;


out_dir:
	if (dir_de) {
		kunmap(dir_page);
		page_cache_release(dir_page);
	}
out_old:
	kunmap(old_page);
	page_cache_release(old_page);
out:
	return err;
}