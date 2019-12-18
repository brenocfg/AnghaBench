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
struct vfsmount {int dummy; } ;
struct file {int /*<<< orphan*/ * f_op; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct file*) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PTR_ERR (struct file*) ; 
 int /*<<< orphan*/  current_cred () ; 
 struct file* dentry_open (struct dentry*,struct vfsmount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  fd_install (int,struct file*) ; 
 int get_unused_fd () ; 
 int /*<<< orphan*/  mntput (struct vfsmount*) ; 
 int /*<<< orphan*/  put_unused_fd (int) ; 
 int /*<<< orphan*/  simple_dir_operations ; 

__attribute__((used)) static int spufs_gang_open(struct dentry *dentry, struct vfsmount *mnt)
{
	int ret;
	struct file *filp;

	ret = get_unused_fd();
	if (ret < 0) {
		dput(dentry);
		mntput(mnt);
		goto out;
	}

	filp = dentry_open(dentry, mnt, O_RDONLY, current_cred());
	if (IS_ERR(filp)) {
		put_unused_fd(ret);
		ret = PTR_ERR(filp);
		goto out;
	}

	filp->f_op = &simple_dir_operations;
	fd_install(ret, filp);
out:
	return ret;
}