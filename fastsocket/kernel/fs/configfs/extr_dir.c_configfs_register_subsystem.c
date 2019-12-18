#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qstr {int /*<<< orphan*/  len; scalar_t__ name; int /*<<< orphan*/  hash; } ;
struct dentry {int /*<<< orphan*/  d_fsdata; } ;
struct TYPE_8__ {scalar_t__ ci_name; scalar_t__ ci_namebuf; } ;
struct config_group {TYPE_4__ cg_item; } ;
struct configfs_subsystem {struct config_group su_group; } ;
struct configfs_dirent {int /*<<< orphan*/  s_element; } ;
struct TYPE_7__ {TYPE_2__* s_root; } ;
struct TYPE_6__ {TYPE_1__* d_inode; struct configfs_dirent* d_fsdata; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_mutex; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int configfs_attach_group (int /*<<< orphan*/ ,TYPE_4__*,struct dentry*) ; 
 int /*<<< orphan*/  configfs_dir_set_ready (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configfs_dirent_lock ; 
 int configfs_pin_fs () ; 
 int /*<<< orphan*/  configfs_release_fs () ; 
 TYPE_3__* configfs_sb ; 
 int /*<<< orphan*/  d_add (struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* d_alloc (TYPE_2__*,struct qstr*) ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  full_name_hash (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_group (int /*<<< orphan*/ ,struct config_group*) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 
 int /*<<< orphan*/  to_config_group (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink_group (struct config_group*) ; 

int configfs_register_subsystem(struct configfs_subsystem *subsys)
{
	int err;
	struct config_group *group = &subsys->su_group;
	struct qstr name;
	struct dentry *dentry;
	struct configfs_dirent *sd;

	err = configfs_pin_fs();
	if (err)
		return err;

	if (!group->cg_item.ci_name)
		group->cg_item.ci_name = group->cg_item.ci_namebuf;

	sd = configfs_sb->s_root->d_fsdata;
	link_group(to_config_group(sd->s_element), group);

	mutex_lock_nested(&configfs_sb->s_root->d_inode->i_mutex,
			I_MUTEX_PARENT);

	name.name = group->cg_item.ci_name;
	name.len = strlen(name.name);
	name.hash = full_name_hash(name.name, name.len);

	err = -ENOMEM;
	dentry = d_alloc(configfs_sb->s_root, &name);
	if (dentry) {
		d_add(dentry, NULL);

		err = configfs_attach_group(sd->s_element, &group->cg_item,
					    dentry);
		if (err) {
			d_delete(dentry);
			dput(dentry);
		} else {
			spin_lock(&configfs_dirent_lock);
			configfs_dir_set_ready(dentry->d_fsdata);
			spin_unlock(&configfs_dirent_lock);
		}
	}

	mutex_unlock(&configfs_sb->s_root->d_inode->i_mutex);

	if (err) {
		unlink_group(group);
		configfs_release_fs();
	}

	return err;
}