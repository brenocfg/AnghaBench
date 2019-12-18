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
struct nameidata {int dummy; } ;
struct inode {TYPE_1__* i_mapping; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int exofs_add_nondir (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  exofs_aops ; 
 int /*<<< orphan*/  exofs_file_inode_operations ; 
 int /*<<< orphan*/  exofs_file_operations ; 
 struct inode* exofs_new_inode (struct inode*,int) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 

__attribute__((used)) static int exofs_create(struct inode *dir, struct dentry *dentry, int mode,
			 struct nameidata *nd)
{
	struct inode *inode = exofs_new_inode(dir, mode);
	int err = PTR_ERR(inode);
	if (!IS_ERR(inode)) {
		inode->i_op = &exofs_file_inode_operations;
		inode->i_fop = &exofs_file_operations;
		inode->i_mapping->a_ops = &exofs_aops;
		mark_inode_dirty(inode);
		err = exofs_add_nondir(dentry, inode);
	}
	return err;
}