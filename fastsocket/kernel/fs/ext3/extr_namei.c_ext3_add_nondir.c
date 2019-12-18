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
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int ext3_add_entry (int /*<<< orphan*/ *,struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  ext3_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

__attribute__((used)) static int ext3_add_nondir(handle_t *handle,
		struct dentry *dentry, struct inode *inode)
{
	int err = ext3_add_entry(handle, dentry, inode);
	if (!err) {
		ext3_mark_inode_dirty(handle, inode);
		d_instantiate(dentry, inode);
		unlock_new_inode(inode);
		return 0;
	}
	drop_nlink(inode);
	unlock_new_inode(inode);
	iput(inode);
	return err;
}