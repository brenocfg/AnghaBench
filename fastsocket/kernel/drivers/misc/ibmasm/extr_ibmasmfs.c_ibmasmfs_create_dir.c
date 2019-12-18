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
struct inode {int /*<<< orphan*/  i_fop; int /*<<< orphan*/ * i_op; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int S_IFDIR ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 struct dentry* d_alloc_name (struct dentry*,char const*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  ibmasmfs_dir_ops ; 
 struct inode* ibmasmfs_make_inode (struct super_block*,int) ; 
 int /*<<< orphan*/  simple_dir_inode_operations ; 

__attribute__((used)) static struct dentry *ibmasmfs_create_dir (struct super_block *sb,
				struct dentry *parent,
				const char *name)
{
	struct dentry *dentry;
	struct inode *inode;

	dentry = d_alloc_name(parent, name);
	if (!dentry)
		return NULL;

	inode = ibmasmfs_make_inode(sb, S_IFDIR | 0500);
	if (!inode) {
		dput(dentry);
		return NULL;
	}

	inode->i_op = &simple_dir_inode_operations;
	inode->i_fop = ibmasmfs_dir_ops;

	d_add(dentry, inode);
	return dentry;
}