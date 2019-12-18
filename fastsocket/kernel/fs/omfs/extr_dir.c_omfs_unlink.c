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
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int omfs_delete_entry (struct dentry*) ; 

__attribute__((used)) static int omfs_unlink(struct inode *dir, struct dentry *dentry)
{
	int ret;
	struct inode *inode = dentry->d_inode;

	ret = omfs_delete_entry(dentry);
	if (ret)
		goto end_unlink;

	inode_dec_link_count(inode);
	mark_inode_dirty(dir);

end_unlink:
	return ret;
}