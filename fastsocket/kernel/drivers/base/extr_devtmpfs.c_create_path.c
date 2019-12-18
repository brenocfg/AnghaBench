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
struct TYPE_8__ {int /*<<< orphan*/  i_mutex; } ;
struct TYPE_7__ {int /*<<< orphan*/  mnt_root; } ;
struct TYPE_6__ {TYPE_3__* d_inode; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  LOOKUP_PARENT ; 
 int dev_mkdir (char*,int) ; 
 TYPE_2__* dev_mnt ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 struct dentry* lookup_create (struct nameidata*,int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_put (TYPE_4__*) ; 
 char* strchr (char*,char) ; 
 int vfs_mkdir (TYPE_3__*,struct dentry*,int) ; 
 int vfs_path_lookup (int /*<<< orphan*/ ,TYPE_2__*,char*,int /*<<< orphan*/ ,struct nameidata*) ; 

__attribute__((used)) static int create_path(const char *nodepath)
{
	char *path;
	struct nameidata nd;
	int err = 0;

	path = kstrdup(nodepath, GFP_KERNEL);
	if (!path)
		return -ENOMEM;

	err = vfs_path_lookup(dev_mnt->mnt_root, dev_mnt,
			      path, LOOKUP_PARENT, &nd);
	if (err == 0) {
		struct dentry *dentry;

		/* create directory right away */
		dentry = lookup_create(&nd, 1);
		if (!IS_ERR(dentry)) {
			err = vfs_mkdir(nd.path.dentry->d_inode,
					dentry, 0755);
			dput(dentry);
		}
		mutex_unlock(&nd.path.dentry->d_inode->i_mutex);

		path_put(&nd.path);
	} else if (err == -ENOENT) {
		char *s;

		/* parent directories do not exist, create them */
		s = path;
		while (1) {
			s = strchr(s, '/');
			if (!s)
				break;
			s[0] = '\0';
			err = dev_mkdir(path, 0755);
			if (err && err != -EEXIST)
				break;
			s[0] = '/';
			s++;
		}
	}

	kfree(path);
	return err;
}