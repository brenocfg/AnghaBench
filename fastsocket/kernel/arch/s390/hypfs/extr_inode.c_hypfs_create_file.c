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
struct super_block {int dummy; } ;
struct inode {char* i_private; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; scalar_t__ i_size; } ;
struct dentry {TYPE_1__* d_inode; } ;
typedef  int mode_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_nlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int S_IFDIR ; 
 int S_IFREG ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  hypfs_file_ops ; 
 struct inode* hypfs_make_inode (struct super_block*,int) ; 
 struct dentry* lookup_one_len (char const*,struct dentry*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_dir_inode_operations ; 
 int /*<<< orphan*/  simple_dir_operations ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static struct dentry *hypfs_create_file(struct super_block *sb,
					struct dentry *parent, const char *name,
					char *data, mode_t mode)
{
	struct dentry *dentry;
	struct inode *inode;

	mutex_lock(&parent->d_inode->i_mutex);
	dentry = lookup_one_len(name, parent, strlen(name));
	if (IS_ERR(dentry)) {
		dentry = ERR_PTR(-ENOMEM);
		goto fail;
	}
	inode = hypfs_make_inode(sb, mode);
	if (!inode) {
		dput(dentry);
		dentry = ERR_PTR(-ENOMEM);
		goto fail;
	}
	if (mode & S_IFREG) {
		inode->i_fop = &hypfs_file_ops;
		if (data)
			inode->i_size = strlen(data);
		else
			inode->i_size = 0;
	} else if (mode & S_IFDIR) {
		inode->i_op = &simple_dir_inode_operations;
		inode->i_fop = &simple_dir_operations;
		parent->d_inode->i_nlink++;
	} else
		BUG();
	inode->i_private = data;
	d_instantiate(dentry, inode);
	dget(dentry);
fail:
	mutex_unlock(&parent->d_inode->i_mutex);
	return dentry;
}