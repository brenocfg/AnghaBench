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
struct ufs_dir_entry {int dummy; } ;
struct page {int dummy; } ;
struct inode {scalar_t__ i_nlink; void* i_ctime; int /*<<< orphan*/  i_mode; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 void* CURRENT_TIME_SEC ; 
 int EIO ; 
 int EMLINK ; 
 int ENOENT ; 
 int ENOTEMPTY ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ UFS_LINK_MAX ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 int /*<<< orphan*/  inode_inc_link_count (struct inode*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int ufs_add_link (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  ufs_delete_entry (struct inode*,struct ufs_dir_entry*,struct page*) ; 
 struct ufs_dir_entry* ufs_dotdot (struct inode*,struct page**) ; 
 int /*<<< orphan*/  ufs_empty_dir (struct inode*) ; 
 struct ufs_dir_entry* ufs_find_entry (struct inode*,struct dentry*,struct page**) ; 
 int /*<<< orphan*/  ufs_set_link (struct inode*,struct ufs_dir_entry*,struct page*,struct inode*) ; 

__attribute__((used)) static int ufs_rename(struct inode *old_dir, struct dentry *old_dentry,
		      struct inode *new_dir, struct dentry *new_dentry)
{
	struct inode *old_inode = old_dentry->d_inode;
	struct inode *new_inode = new_dentry->d_inode;
	struct page *dir_page = NULL;
	struct ufs_dir_entry * dir_de = NULL;
	struct page *old_page;
	struct ufs_dir_entry *old_de;
	int err = -ENOENT;

	old_de = ufs_find_entry(old_dir, old_dentry, &old_page);
	if (!old_de)
		goto out;

	if (S_ISDIR(old_inode->i_mode)) {
		err = -EIO;
		dir_de = ufs_dotdot(old_inode, &dir_page);
		if (!dir_de)
			goto out_old;
	}

	if (new_inode) {
		struct page *new_page;
		struct ufs_dir_entry *new_de;

		err = -ENOTEMPTY;
		if (dir_de && !ufs_empty_dir(new_inode))
			goto out_dir;

		err = -ENOENT;
		new_de = ufs_find_entry(new_dir, new_dentry, &new_page);
		if (!new_de)
			goto out_dir;
		inode_inc_link_count(old_inode);
		ufs_set_link(new_dir, new_de, new_page, old_inode);
		new_inode->i_ctime = CURRENT_TIME_SEC;
		if (dir_de)
			drop_nlink(new_inode);
		inode_dec_link_count(new_inode);
	} else {
		if (dir_de) {
			err = -EMLINK;
			if (new_dir->i_nlink >= UFS_LINK_MAX)
				goto out_dir;
		}
		inode_inc_link_count(old_inode);
		err = ufs_add_link(new_dentry, old_inode);
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

	ufs_delete_entry(old_dir, old_de, old_page);
	inode_dec_link_count(old_inode);

	if (dir_de) {
		ufs_set_link(old_inode, dir_de, dir_page, new_dir);
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