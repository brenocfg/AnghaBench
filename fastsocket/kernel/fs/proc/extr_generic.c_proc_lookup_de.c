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
struct proc_dir_entry {scalar_t__ namelen; unsigned int low_ino; int /*<<< orphan*/  name; struct proc_dir_entry* next; struct proc_dir_entry* subdir; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {scalar_t__ len; int /*<<< orphan*/  name; } ;
struct dentry {int /*<<< orphan*/ * d_op; TYPE_1__ d_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 struct dentry* ERR_PTR (int) ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  de_get (struct proc_dir_entry*) ; 
 int /*<<< orphan*/  de_put (struct proc_dir_entry*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  proc_dentry_operations ; 
 struct inode* proc_get_inode (int /*<<< orphan*/ ,unsigned int,struct proc_dir_entry*) ; 
 int /*<<< orphan*/  proc_subdir_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct dentry *proc_lookup_de(struct proc_dir_entry *de, struct inode *dir,
		struct dentry *dentry)
{
	struct inode *inode = NULL;
	int error = -ENOENT;

	spin_lock(&proc_subdir_lock);
	for (de = de->subdir; de ; de = de->next) {
		if (de->namelen != dentry->d_name.len)
			continue;
		if (!memcmp(dentry->d_name.name, de->name, de->namelen)) {
			unsigned int ino;

			ino = de->low_ino;
			de_get(de);
			spin_unlock(&proc_subdir_lock);
			error = -EINVAL;
			inode = proc_get_inode(dir->i_sb, ino, de);
			goto out_unlock;
		}
	}
	spin_unlock(&proc_subdir_lock);
out_unlock:

	if (inode) {
		dentry->d_op = &proc_dentry_operations;
		d_add(dentry, inode);
		return NULL;
	}
	if (de)
		de_put(de);
	return ERR_PTR(error);
}