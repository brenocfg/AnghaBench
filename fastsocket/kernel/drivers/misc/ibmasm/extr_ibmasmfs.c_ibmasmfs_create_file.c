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
struct super_block {int dummy; } ;
struct inode {void* i_private; struct file_operations const* i_fop; } ;
struct file_operations {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int S_IFREG ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 struct dentry* d_alloc_name (struct dentry*,char const*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct inode* ibmasmfs_make_inode (struct super_block*,int) ; 

__attribute__((used)) static struct dentry *ibmasmfs_create_file (struct super_block *sb,
			struct dentry *parent,
			const char *name,
			const struct file_operations *fops,
			void *data,
			int mode)
{
	struct dentry *dentry;
	struct inode *inode;

	dentry = d_alloc_name(parent, name);
	if (!dentry)
		return NULL;

	inode = ibmasmfs_make_inode(sb, S_IFREG | mode);
	if (!inode) {
		dput(dentry);
		return NULL;
	}

	inode->i_fop = fops;
	inode->i_private = data;

	d_add(dentry, inode);
	return dentry;
}