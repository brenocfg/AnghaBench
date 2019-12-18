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
struct inode {int /*<<< orphan*/  i_mutex; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int S_IRWXUGO ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  mntget (struct vfsmount*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int simple_rmdir (struct inode*,struct dentry*) ; 
 int spufs_gang_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spufs_mkgang (struct inode*,struct dentry*,int) ; 

__attribute__((used)) static int spufs_create_gang(struct inode *inode,
			struct dentry *dentry,
			struct vfsmount *mnt, int mode)
{
	int ret;

	ret = spufs_mkgang(inode, dentry, mode & S_IRWXUGO);
	if (ret)
		goto out;

	/*
	 * get references for dget and mntget, will be released
	 * in error path of *_open().
	 */
	ret = spufs_gang_open(dget(dentry), mntget(mnt));
	if (ret < 0) {
		int err = simple_rmdir(inode, dentry);
		WARN_ON(err);
	}

out:
	mutex_unlock(&inode->i_mutex);
	dput(dentry);
	return ret;
}