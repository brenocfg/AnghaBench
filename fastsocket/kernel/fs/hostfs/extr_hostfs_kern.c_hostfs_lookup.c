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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int /*<<< orphan*/ * d_op; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 char* dentry_name (struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostfs_dentry_ops ; 
 struct inode* hostfs_iget (int /*<<< orphan*/ ) ; 
 int init_inode (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int read_name (struct inode*,char*) ; 

struct dentry *hostfs_lookup(struct inode *ino, struct dentry *dentry,
			     struct nameidata *nd)
{
	struct inode *inode;
	char *name;
	int err;

	inode = hostfs_iget(ino->i_sb);
	if (IS_ERR(inode)) {
		err = PTR_ERR(inode);
		goto out;
	}

	err = init_inode(inode, dentry);
	if (err)
		goto out_put;

	err = -ENOMEM;
	name = dentry_name(dentry, 0);
	if (name == NULL)
		goto out_put;

	err = read_name(inode, name);
	kfree(name);
	if (err == -ENOENT) {
		iput(inode);
		inode = NULL;
	}
	else if (err)
		goto out_put;

	d_add(dentry, inode);
	dentry->d_op = &hostfs_dentry_ops;
	return NULL;

 out_put:
	iput(inode);
 out:
	return ERR_PTR(err);
}