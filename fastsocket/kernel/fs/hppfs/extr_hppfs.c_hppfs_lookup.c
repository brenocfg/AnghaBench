#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nameidata {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {TYPE_2__* d_inode; int /*<<< orphan*/  d_name; } ;
struct TYPE_6__ {struct dentry* proc_dentry; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_mutex; TYPE_1__* i_op; } ;
struct TYPE_4__ {struct dentry* (* lookup ) (TYPE_2__*,struct dentry*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 struct dentry* ERR_PTR (int) ; 
 TYPE_3__* HPPFS_I (struct inode*) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 struct dentry* d_alloc (struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* d_lookup (struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int file_removed (struct dentry*,int /*<<< orphan*/ *) ; 
 struct inode* get_inode (int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct dentry* stub1 (TYPE_2__*,struct dentry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dentry *hppfs_lookup(struct inode *ino, struct dentry *dentry,
				   struct nameidata *nd)
{
	struct dentry *proc_dentry, *new, *parent;
	struct inode *inode;
	int err, deleted;

	deleted = file_removed(dentry, NULL);
	if (deleted < 0)
		return ERR_PTR(deleted);
	else if (deleted)
		return ERR_PTR(-ENOENT);

	err = -ENOMEM;
	parent = HPPFS_I(ino)->proc_dentry;
	mutex_lock(&parent->d_inode->i_mutex);
	proc_dentry = d_lookup(parent, &dentry->d_name);
	if (proc_dentry == NULL) {
		proc_dentry = d_alloc(parent, &dentry->d_name);
		if (proc_dentry == NULL) {
			mutex_unlock(&parent->d_inode->i_mutex);
			goto out;
		}
		new = (*parent->d_inode->i_op->lookup)(parent->d_inode,
						       proc_dentry, NULL);
		if (new) {
			dput(proc_dentry);
			proc_dentry = new;
		}
	}
	mutex_unlock(&parent->d_inode->i_mutex);

	if (IS_ERR(proc_dentry))
		return proc_dentry;

	err = -ENOMEM;
	inode = get_inode(ino->i_sb, proc_dentry);
	if (!inode)
		goto out_dput;

 	d_add(dentry, inode);
	return NULL;

 out_dput:
	dput(proc_dentry);
 out:
	return ERR_PTR(err);
}