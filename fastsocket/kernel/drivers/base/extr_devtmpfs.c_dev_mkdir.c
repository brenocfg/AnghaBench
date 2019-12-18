#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* dentry; } ;
struct nameidata {TYPE_4__ path; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_mutex; } ;
struct TYPE_7__ {int /*<<< orphan*/  mnt_root; } ;
struct TYPE_6__ {TYPE_3__* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  LOOKUP_PARENT ; 
 int PTR_ERR (struct dentry*) ; 
 TYPE_2__* dev_mnt ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct dentry* lookup_create (struct nameidata*,int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_put (TYPE_4__*) ; 
 int vfs_mkdir (TYPE_3__*,struct dentry*,int /*<<< orphan*/ ) ; 
 int vfs_path_lookup (int /*<<< orphan*/ ,TYPE_2__*,char const*,int /*<<< orphan*/ ,struct nameidata*) ; 

__attribute__((used)) static int dev_mkdir(const char *name, mode_t mode)
{
	struct nameidata nd;
	struct dentry *dentry;
	int err;

	err = vfs_path_lookup(dev_mnt->mnt_root, dev_mnt,
			      name, LOOKUP_PARENT, &nd);
	if (err)
		return err;

	dentry = lookup_create(&nd, 1);
	if (!IS_ERR(dentry)) {
		err = vfs_mkdir(nd.path.dentry->d_inode, dentry, mode);
		dput(dentry);
	} else {
		err = PTR_ERR(dentry);
	}
	mutex_unlock(&nd.path.dentry->d_inode->i_mutex);

	path_put(&nd.path);
	return err;
}