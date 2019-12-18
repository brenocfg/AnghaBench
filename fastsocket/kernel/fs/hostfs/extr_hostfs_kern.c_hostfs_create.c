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
struct nameidata {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int fd; int mode; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 TYPE_1__* HOSTFS_I (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 char* dentry_name (struct dentry*,int /*<<< orphan*/ ) ; 
 int file_create (char*,int,int,int,int,int,int,int,int,int) ; 
 struct inode* hostfs_iget (int /*<<< orphan*/ ) ; 
 int init_inode (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int read_name (struct inode*,char*) ; 

int hostfs_create(struct inode *dir, struct dentry *dentry, int mode,
		  struct nameidata *nd)
{
	struct inode *inode;
	char *name;
	int error, fd;

	inode = hostfs_iget(dir->i_sb);
	if (IS_ERR(inode)) {
		error = PTR_ERR(inode);
		goto out;
	}

	error = init_inode(inode, dentry);
	if (error)
		goto out_put;

	error = -ENOMEM;
	name = dentry_name(dentry, 0);
	if (name == NULL)
		goto out_put;

	fd = file_create(name,
			 mode & S_IRUSR, mode & S_IWUSR, mode & S_IXUSR,
			 mode & S_IRGRP, mode & S_IWGRP, mode & S_IXGRP,
			 mode & S_IROTH, mode & S_IWOTH, mode & S_IXOTH);
	if (fd < 0)
		error = fd;
	else error = read_name(inode, name);

	kfree(name);
	if (error)
		goto out_put;

	HOSTFS_I(inode)->fd = fd;
	HOSTFS_I(inode)->mode = FMODE_READ | FMODE_WRITE;
	d_instantiate(dentry, inode);
	return 0;

 out_put:
	iput(inode);
 out:
	return error;
}