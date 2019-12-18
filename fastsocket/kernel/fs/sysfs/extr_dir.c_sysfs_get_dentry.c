#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sysfs_dirent {int /*<<< orphan*/  s_name; struct sysfs_dirent* s_parent; } ;
struct dentry {TYPE_1__* d_inode; struct sysfs_dirent* d_fsdata; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_root; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_mutex; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 struct dentry* dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct dentry* lookup_one_noperm (int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* sysfs_sb ; 

struct dentry *sysfs_get_dentry(struct sysfs_dirent *sd)
{
	struct dentry *dentry = dget(sysfs_sb->s_root);

	while (dentry->d_fsdata != sd) {
		struct sysfs_dirent *cur;
		struct dentry *parent;

		/* find the first ancestor which hasn't been looked up */
		cur = sd;
		while (cur->s_parent != dentry->d_fsdata)
			cur = cur->s_parent;

		/* look it up */
		parent = dentry;
		mutex_lock(&parent->d_inode->i_mutex);
		dentry = lookup_one_noperm(cur->s_name, parent);
		mutex_unlock(&parent->d_inode->i_mutex);
		dput(parent);

		if (IS_ERR(dentry))
			break;
	}
	return dentry;
}