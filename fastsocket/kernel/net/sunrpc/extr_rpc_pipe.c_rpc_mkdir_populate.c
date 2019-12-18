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
typedef  int /*<<< orphan*/  umode_t ;
struct qstr {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mutex; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 struct dentry* __rpc_lookup_create_exclusive (struct dentry*,struct qstr*) ; 
 int __rpc_mkdir (struct inode*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  __rpc_rmdir (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dentry *rpc_mkdir_populate(struct dentry *parent,
		struct qstr *name, umode_t mode, void *private,
		int (*populate)(struct dentry *, void *), void *args_populate)
{
	struct dentry *dentry;
	struct inode *dir = parent->d_inode;
	int error;

	mutex_lock_nested(&dir->i_mutex, I_MUTEX_PARENT);
	dentry = __rpc_lookup_create_exclusive(parent, name);
	if (IS_ERR(dentry))
		goto out;
	error = __rpc_mkdir(dir, dentry, mode, NULL, private);
	if (error != 0)
		goto out_err;
	if (populate != NULL) {
		error = populate(dentry, args_populate);
		if (error)
			goto err_rmdir;
	}
out:
	mutex_unlock(&dir->i_mutex);
	return dentry;
err_rmdir:
	__rpc_rmdir(dir, dentry);
out_err:
	dentry = ERR_PTR(error);
	goto out;
}