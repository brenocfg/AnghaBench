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
struct inode {int dummy; } ;
struct dentry {scalar_t__ d_parent; struct configfs_dirent* d_fsdata; } ;
struct configfs_symlink {struct config_item* sl_target; int /*<<< orphan*/  sl_list; } ;
struct configfs_dirent {int s_type; int /*<<< orphan*/  s_sibling; struct configfs_symlink* s_element; } ;
struct config_item_type {TYPE_1__* ct_item_ops; } ;
struct config_item {struct config_item_type* ci_type; } ;
struct TYPE_4__ {scalar_t__ s_root; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* drop_link ) (struct config_item*,struct config_item*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CONFIGFS_ITEM_LINK ; 
 int EPERM ; 
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 int /*<<< orphan*/  configfs_dirent_lock ; 
 int /*<<< orphan*/  configfs_drop_dentry (struct configfs_dirent*,scalar_t__) ; 
 struct config_item* configfs_get_config_item (scalar_t__) ; 
 int /*<<< orphan*/  configfs_put (struct configfs_dirent*) ; 
 TYPE_2__* configfs_sb ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  kfree (struct configfs_symlink*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct config_item*,struct config_item*) ; 

int configfs_unlink(struct inode *dir, struct dentry *dentry)
{
	struct configfs_dirent *sd = dentry->d_fsdata;
	struct configfs_symlink *sl;
	struct config_item *parent_item;
	struct config_item_type *type;
	int ret;

	ret = -EPERM;  /* What lack-of-symlink returns */
	if (!(sd->s_type & CONFIGFS_ITEM_LINK))
		goto out;

	BUG_ON(dentry->d_parent == configfs_sb->s_root);

	sl = sd->s_element;

	parent_item = configfs_get_config_item(dentry->d_parent);
	type = parent_item->ci_type;

	spin_lock(&configfs_dirent_lock);
	list_del_init(&sd->s_sibling);
	spin_unlock(&configfs_dirent_lock);
	configfs_drop_dentry(sd, dentry->d_parent);
	dput(dentry);
	configfs_put(sd);

	/*
	 * drop_link() must be called before
	 * list_del_init(&sl->sl_list), so that the order of
	 * drop_link(this, target) and drop_item(target) is preserved.
	 */
	if (type && type->ct_item_ops &&
	    type->ct_item_ops->drop_link)
		type->ct_item_ops->drop_link(parent_item,
					       sl->sl_target);

	spin_lock(&configfs_dirent_lock);
	list_del_init(&sl->sl_list);
	spin_unlock(&configfs_dirent_lock);

	/* Put reference from create_link() */
	config_item_put(sl->sl_target);
	kfree(sl);

	config_item_put(parent_item);

	ret = 0;

out:
	return ret;
}