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
struct inode {struct file_operations const* i_fop; } ;
struct file_operations {int dummy; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct TYPE_2__ {void* i_private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int S_IFREG ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 struct dentry* d_alloc_name (struct dentry*,char const*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct inode* oprofilefs_get_inode (struct super_block*,int) ; 

__attribute__((used)) static int __oprofilefs_create_file(struct super_block *sb,
	struct dentry *root, char const *name, const struct file_operations *fops,
	int perm, void *priv)
{
	struct dentry *dentry;
	struct inode *inode;

	dentry = d_alloc_name(root, name);
	if (!dentry)
		return -ENOMEM;
	inode = oprofilefs_get_inode(sb, S_IFREG | perm);
	if (!inode) {
		dput(dentry);
		return -ENOMEM;
	}
	inode->i_fop = fops;
	d_add(dentry, inode);
	dentry->d_inode->i_private = priv;
	return 0;
}