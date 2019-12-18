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
typedef  int /*<<< orphan*/  u64 ;
struct super_block {int dummy; } ;
struct qstr {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_mode; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOTDIR ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 struct dentry* d_find_alias (struct inode*) ; 
 struct dentry* d_lookup (struct dentry*,struct qstr*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  fuse_inode_eq ; 
 int /*<<< orphan*/  fuse_invalidate_attr (struct inode*) ; 
 int /*<<< orphan*/  fuse_invalidate_entry (struct dentry*) ; 
 struct inode* ilookup5 (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int fuse_reverse_inval_entry(struct super_block *sb, u64 parent_nodeid,
			     struct qstr *name)
{
	int err = -ENOTDIR;
	struct inode *parent;
	struct dentry *dir;
	struct dentry *entry;

	parent = ilookup5(sb, parent_nodeid, fuse_inode_eq, &parent_nodeid);
	if (!parent)
		return -ENOENT;

	mutex_lock(&parent->i_mutex);
	if (!S_ISDIR(parent->i_mode))
		goto unlock;

	err = -ENOENT;
	dir = d_find_alias(parent);
	if (!dir)
		goto unlock;

	entry = d_lookup(dir, name);
	dput(dir);
	if (!entry)
		goto unlock;

	fuse_invalidate_attr(parent);
	fuse_invalidate_entry(entry);
	dput(entry);
	err = 0;

 unlock:
	mutex_unlock(&parent->i_mutex);
	iput(parent);
	return err;
}