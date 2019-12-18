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
struct TYPE_2__ {int /*<<< orphan*/ * dir_attr; } ;
struct nfs_unlinkdata {int /*<<< orphan*/  cred; int /*<<< orphan*/  dir_attr; TYPE_1__ res; } ;
struct inode {int dummy; } ;
struct dentry {int d_flags; int /*<<< orphan*/  d_lock; struct nfs_unlinkdata* d_fsdata; } ;

/* Variables and functions */
 int DCACHE_NFSFS_RENAMED ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfs_unlinkdata*) ; 
 struct nfs_unlinkdata* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_rpccred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_lookup_cred () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfs_async_unlink(struct inode *dir, struct dentry *dentry)
{
	struct nfs_unlinkdata *data;
	int status = -ENOMEM;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (data == NULL)
		goto out;

	data->cred = rpc_lookup_cred();
	if (IS_ERR(data->cred)) {
		status = PTR_ERR(data->cred);
		goto out_free;
	}
	data->res.dir_attr = &data->dir_attr;

	status = -EBUSY;
	spin_lock(&dentry->d_lock);
	if (dentry->d_flags & DCACHE_NFSFS_RENAMED)
		goto out_unlock;
	dentry->d_flags |= DCACHE_NFSFS_RENAMED;
	dentry->d_fsdata = data;
	spin_unlock(&dentry->d_lock);
	return 0;
out_unlock:
	spin_unlock(&dentry->d_lock);
	put_rpccred(data->cred);
out_free:
	kfree(data);
out:
	return status;
}