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
struct inode {int /*<<< orphan*/  i_ctime; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 int ufs_delete_entry (struct inode*,struct ufs_dir_entry*,struct page*) ; 
 struct ufs_dir_entry* ufs_find_entry (struct inode*,struct dentry*,struct page**) ; 

__attribute__((used)) static int ufs_unlink(struct inode *dir, struct dentry *dentry)
{
	struct inode * inode = dentry->d_inode;
	struct ufs_dir_entry *de;
	struct page *page;
	int err = -ENOENT;

	de = ufs_find_entry(dir, dentry, &page);
	if (!de)
		goto out;

	err = ufs_delete_entry(dir, de, page);
	if (err)
		goto out;

	inode->i_ctime = dir->i_ctime;
	inode_dec_link_count(inode);
	err = 0;
out:
	return err;
}