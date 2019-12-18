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
struct object_info {int dummy; } ;
struct nameidata {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int /*<<< orphan*/  d_name; int /*<<< orphan*/ * d_op; } ;

/* Variables and functions */
 int EACCES ; 
 struct dentry* ERR_PTR (int) ; 
 int /*<<< orphan*/  adfs_dentry_operations ; 
 int adfs_dir_lookup_byname (struct inode*,int /*<<< orphan*/ *,struct object_info*) ; 
 struct inode* adfs_iget (int /*<<< orphan*/ ,struct object_info*) ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static struct dentry *
adfs_lookup(struct inode *dir, struct dentry *dentry, struct nameidata *nd)
{
	struct inode *inode = NULL;
	struct object_info obj;
	int error;

	dentry->d_op = &adfs_dentry_operations;	
	lock_kernel();
	error = adfs_dir_lookup_byname(dir, &dentry->d_name, &obj);
	if (error == 0) {
		error = -EACCES;
		/*
		 * This only returns NULL if get_empty_inode
		 * fails.
		 */
		inode = adfs_iget(dir->i_sb, &obj);
		if (inode)
			error = 0;
	}
	unlock_kernel();
	d_add(dentry, inode);
	return ERR_PTR(error);
}