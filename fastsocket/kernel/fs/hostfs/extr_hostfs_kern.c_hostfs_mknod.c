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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 char* dentry_name (struct dentry*,int /*<<< orphan*/ ) ; 
 int do_mknod (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* hostfs_iget (int /*<<< orphan*/ ) ; 
 int init_inode (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int read_name (struct inode*,char*) ; 

int hostfs_mknod(struct inode *dir, struct dentry *dentry, int mode, dev_t dev)
{
	struct inode *inode;
	char *name;
	int err;

	inode = hostfs_iget(dir->i_sb);
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

	init_special_inode(inode, mode, dev);
	err = do_mknod(name, mode, MAJOR(dev), MINOR(dev));
	if (err)
		goto out_free;

	err = read_name(inode, name);
	kfree(name);
	if (err)
		goto out_put;

	d_instantiate(dentry, inode);
	return 0;

 out_free:
	kfree(name);
 out_put:
	iput(inode);
 out:
	return err;
}