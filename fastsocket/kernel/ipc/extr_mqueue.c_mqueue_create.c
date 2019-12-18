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
struct nameidata {int dummy; } ;
struct mq_attr {int dummy; } ;
struct ipc_namespace {scalar_t__ mq_queues_count; scalar_t__ mq_queues_max; } ;
struct inode {int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_sb; } ;
struct dentry {struct mq_attr* d_fsdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_RESOURCE ; 
 int /*<<< orphan*/  CURRENT_TIME ; 
 scalar_t__ DIRENT_SIZE ; 
 int EACCES ; 
 int ENOMEM ; 
 int ENOSPC ; 
 scalar_t__ HARD_QUEUESMAX ; 
 struct ipc_namespace* __get_ns_from_inode (struct inode*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  mq_lock ; 
 struct inode* mqueue_get_inode (int /*<<< orphan*/ ,struct ipc_namespace*,int,struct mq_attr*) ; 
 int /*<<< orphan*/  put_ipc_ns (struct ipc_namespace*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mqueue_create(struct inode *dir, struct dentry *dentry,
				int mode, struct nameidata *nd)
{
	struct inode *inode;
	struct mq_attr *attr = dentry->d_fsdata;
	int error;
	struct ipc_namespace *ipc_ns;

	spin_lock(&mq_lock);
	ipc_ns = __get_ns_from_inode(dir);
	if (!ipc_ns) {
		error = -EACCES;
		goto out_unlock;
	}
	if (ipc_ns->mq_queues_count >= HARD_QUEUESMAX ||
	    (ipc_ns->mq_queues_count >= ipc_ns->mq_queues_max &&
	     !capable(CAP_SYS_RESOURCE))) {
		error = -ENOSPC;
		goto out_unlock;
	}
	ipc_ns->mq_queues_count++;
	spin_unlock(&mq_lock);

	inode = mqueue_get_inode(dir->i_sb, ipc_ns, mode, attr);
	if (!inode) {
		error = -ENOMEM;
		spin_lock(&mq_lock);
		ipc_ns->mq_queues_count--;
		goto out_unlock;
	}

	put_ipc_ns(ipc_ns);
	dir->i_size += DIRENT_SIZE;
	dir->i_ctime = dir->i_mtime = dir->i_atime = CURRENT_TIME;

	d_instantiate(dentry, inode);
	dget(dentry);
	return 0;
out_unlock:
	spin_unlock(&mq_lock);
	if (ipc_ns)
		put_ipc_ns(ipc_ns);
	return error;
}