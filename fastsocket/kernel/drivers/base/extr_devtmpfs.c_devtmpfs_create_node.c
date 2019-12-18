#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* dentry; } ;
struct nameidata {TYPE_5__ path; } ;
struct device {int /*<<< orphan*/  devt; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct cred {int dummy; } ;
typedef  int mode_t ;
struct TYPE_10__ {int /*<<< orphan*/  i_mutex; } ;
struct TYPE_9__ {int /*<<< orphan*/  mnt_root; } ;
struct TYPE_8__ {TYPE_4__* d_inode; } ;
struct TYPE_7__ {TYPE_3__** i_private; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  LOOKUP_PARENT ; 
 int PTR_ERR (struct dentry*) ; 
 int S_IFBLK ; 
 int S_IFCHR ; 
 int /*<<< orphan*/  create_path (char const*) ; 
 TYPE_3__* dev_mnt ; 
 char* device_get_devnode (struct device*,int*,char const**) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  init_cred ; 
 scalar_t__ is_blockdev (struct device*) ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 struct dentry* lookup_create (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cred* override_creds (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_put (TYPE_5__*) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 
 int sys_umask (int) ; 
 int vfs_mknod (TYPE_4__*,struct dentry*,int,int /*<<< orphan*/ ) ; 
 int vfs_path_lookup (int /*<<< orphan*/ ,TYPE_3__*,char const*,int /*<<< orphan*/ ,struct nameidata*) ; 

int devtmpfs_create_node(struct device *dev)
{
	const char *tmp = NULL;
	const char *nodename;
	const struct cred *curr_cred;
	mode_t mode = 0;
	struct nameidata nd;
	struct dentry *dentry;
	int err;

	if (!dev_mnt)
		return 0;

	nodename = device_get_devnode(dev, &mode, &tmp);
	if (!nodename)
		return -ENOMEM;

	if (mode == 0)
		mode = 0600;
	if (is_blockdev(dev))
		mode |= S_IFBLK;
	else
		mode |= S_IFCHR;

	curr_cred = override_creds(&init_cred);
	err = vfs_path_lookup(dev_mnt->mnt_root, dev_mnt,
			      nodename, LOOKUP_PARENT, &nd);
	if (err == -ENOENT) {
		/* create missing parent directories */
		create_path(nodename);
		err = vfs_path_lookup(dev_mnt->mnt_root, dev_mnt,
				      nodename, LOOKUP_PARENT, &nd);
		if (err)
			goto out;
	}

	dentry = lookup_create(&nd, 0);
	if (!IS_ERR(dentry)) {
		int umask;

		umask = sys_umask(0000);
		err = vfs_mknod(nd.path.dentry->d_inode,
				dentry, mode, dev->devt);
		sys_umask(umask);
		/* mark as kernel created inode */
		if (!err)
			dentry->d_inode->i_private = &dev_mnt;
		dput(dentry);
	} else {
		err = PTR_ERR(dentry);
	}
	mutex_unlock(&nd.path.dentry->d_inode->i_mutex);

	path_put(&nd.path);
out:
	kfree(tmp);
	revert_creds(curr_cred);
	return err;
}