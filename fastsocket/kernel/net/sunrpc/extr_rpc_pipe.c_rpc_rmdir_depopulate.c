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
struct inode {int /*<<< orphan*/  i_mutex; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int __rpc_rmdir (struct inode*,struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rpc_rmdir_depopulate(struct dentry *dentry,
		void (*depopulate)(struct dentry *))
{
	struct dentry *parent;
	struct inode *dir;
	int error;

	parent = dget_parent(dentry);
	dir = parent->d_inode;
	mutex_lock_nested(&dir->i_mutex, I_MUTEX_PARENT);
	if (depopulate != NULL)
		depopulate(dentry);
	error = __rpc_rmdir(dir, dentry);
	mutex_unlock(&dir->i_mutex);
	dput(parent);
	return error;
}