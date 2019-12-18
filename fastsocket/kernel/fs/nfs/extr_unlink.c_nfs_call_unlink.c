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
struct nfs_unlinkdata {int /*<<< orphan*/  list; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  silly_list; int /*<<< orphan*/  silly_count; } ;

/* Variables and functions */
 TYPE_1__* NFS_I (struct inode*) ; 
 scalar_t__ atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nfs_do_call_unlink (struct dentry*,struct inode*,struct nfs_unlinkdata*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs_call_unlink(struct dentry *dentry, struct nfs_unlinkdata *data)
{
	struct dentry *parent;
	struct inode *dir;
	int ret = 0;


	parent = dget_parent(dentry);
	if (parent == NULL)
		goto out_free;
	dir = parent->d_inode;
	/* Non-exclusive lock protects against concurrent lookup() calls */
	spin_lock(&dir->i_lock);
	if (atomic_inc_not_zero(&NFS_I(dir)->silly_count) == 0) {
		/* Deferred delete */
		hlist_add_head(&data->list, &NFS_I(dir)->silly_list);
		spin_unlock(&dir->i_lock);
		ret = 1;
		goto out_dput;
	}
	spin_unlock(&dir->i_lock);
	ret = nfs_do_call_unlink(parent, dir, data);
out_dput:
	dput(parent);
out_free:
	return ret;
}