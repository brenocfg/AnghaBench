#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_5__* dentry; int /*<<< orphan*/  mnt; } ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct nameidata {TYPE_4__ path; TYPE_1__ last; } ;
struct kstat {int mode; } ;
struct iattr {int ia_mode; int ia_valid; scalar_t__ ia_gid; scalar_t__ ia_uid; } ;
struct device {int dummy; } ;
struct dentry {TYPE_6__* d_inode; } ;
struct cred {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  i_mutex; } ;
struct TYPE_12__ {TYPE_2__* d_inode; } ;
struct TYPE_10__ {int /*<<< orphan*/  mnt_root; } ;
struct TYPE_9__ {int /*<<< orphan*/  i_mutex; } ;

/* Variables and functions */
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_UID ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int /*<<< orphan*/  LOOKUP_PARENT ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  delete_path (char const*) ; 
 TYPE_3__* dev_mnt ; 
 scalar_t__ dev_mynode (struct device*,TYPE_6__*,struct kstat*) ; 
 char* device_get_devnode (struct device*,int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  init_cred ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 struct dentry* lookup_one_len (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_change (struct dentry*,struct iattr*) ; 
 struct cred* override_creds (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_put (TYPE_4__*) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 
 scalar_t__ strchr (char const*,char) ; 
 int vfs_getattr (int /*<<< orphan*/ ,struct dentry*,struct kstat*) ; 
 int vfs_path_lookup (int /*<<< orphan*/ ,TYPE_3__*,char const*,int /*<<< orphan*/ ,struct nameidata*) ; 
 int vfs_unlink (TYPE_2__*,struct dentry*) ; 

int devtmpfs_delete_node(struct device *dev)
{
	const char *tmp = NULL;
	const char *nodename;
	const struct cred *curr_cred;
	struct nameidata nd;
	struct dentry *dentry;
	struct kstat stat;
	int deleted = 1;
	int err;

	if (!dev_mnt)
		return 0;

	nodename = device_get_devnode(dev, NULL, &tmp);
	if (!nodename)
		return -ENOMEM;

	curr_cred = override_creds(&init_cred);
	err = vfs_path_lookup(dev_mnt->mnt_root, dev_mnt,
			      nodename, LOOKUP_PARENT, &nd);
	if (err)
		goto out;

	mutex_lock_nested(&nd.path.dentry->d_inode->i_mutex, I_MUTEX_PARENT);
	dentry = lookup_one_len(nd.last.name, nd.path.dentry, nd.last.len);
	if (!IS_ERR(dentry)) {
		if (dentry->d_inode) {
			err = vfs_getattr(nd.path.mnt, dentry, &stat);
			if (!err && dev_mynode(dev, dentry->d_inode, &stat)) {
				struct iattr newattrs;
				/*
				 * before unlinking this node, reset permissions
				 * of possible references like hardlinks
				 */
				newattrs.ia_uid = 0;
				newattrs.ia_gid = 0;
				newattrs.ia_mode = stat.mode & ~0777;
				newattrs.ia_valid =
					ATTR_UID|ATTR_GID|ATTR_MODE;
				mutex_lock(&dentry->d_inode->i_mutex);
				notify_change(dentry, &newattrs);
				mutex_unlock(&dentry->d_inode->i_mutex);
				err = vfs_unlink(nd.path.dentry->d_inode,
						 dentry);
				if (!err || err == -ENOENT)
					deleted = 1;
			}
		} else {
			err = -ENOENT;
		}
		dput(dentry);
	} else {
		err = PTR_ERR(dentry);
	}
	mutex_unlock(&nd.path.dentry->d_inode->i_mutex);

	path_put(&nd.path);
	if (deleted && strchr(nodename, '/'))
		delete_path(nodename);
out:
	kfree(tmp);
	revert_creds(curr_cred);
	return err;
}