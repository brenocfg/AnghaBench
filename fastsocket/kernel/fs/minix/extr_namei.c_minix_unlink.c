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
struct minix_dir_entry {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ctime; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 int minix_delete_entry (struct minix_dir_entry*,struct page*) ; 
 struct minix_dir_entry* minix_find_entry (struct dentry*,struct page**) ; 

__attribute__((used)) static int minix_unlink(struct inode * dir, struct dentry *dentry)
{
	int err = -ENOENT;
	struct inode * inode = dentry->d_inode;
	struct page * page;
	struct minix_dir_entry * de;

	de = minix_find_entry(dentry, &page);
	if (!de)
		goto end_unlink;

	err = minix_delete_entry(de, page);
	if (err)
		goto end_unlink;

	inode->i_ctime = dir->i_ctime;
	inode_dec_link_count(inode);
end_unlink:
	return err;
}