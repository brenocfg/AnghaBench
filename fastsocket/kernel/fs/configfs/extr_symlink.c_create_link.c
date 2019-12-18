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
struct dentry {int dummy; } ;
struct configfs_symlink {int /*<<< orphan*/  sl_list; int /*<<< orphan*/  sl_target; } ;
struct configfs_dirent {int s_type; int /*<<< orphan*/  s_links; } ;
struct config_item {TYPE_1__* ci_dentry; } ;
struct TYPE_2__ {struct configfs_dirent* d_fsdata; } ;

/* Variables and functions */
 int CONFIGFS_USET_DROPPING ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  config_item_get (struct config_item*) ; 
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 int configfs_create_link (struct configfs_symlink*,TYPE_1__*,struct dentry*) ; 
 int /*<<< orphan*/  configfs_dirent_is_ready (struct configfs_dirent*) ; 
 int /*<<< orphan*/  configfs_dirent_lock ; 
 int /*<<< orphan*/  kfree (struct configfs_symlink*) ; 
 struct configfs_symlink* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_link(struct config_item *parent_item,
		       struct config_item *item,
		       struct dentry *dentry)
{
	struct configfs_dirent *target_sd = item->ci_dentry->d_fsdata;
	struct configfs_symlink *sl;
	int ret;

	ret = -ENOENT;
	if (!configfs_dirent_is_ready(target_sd))
		goto out;
	ret = -ENOMEM;
	sl = kmalloc(sizeof(struct configfs_symlink), GFP_KERNEL);
	if (sl) {
		sl->sl_target = config_item_get(item);
		spin_lock(&configfs_dirent_lock);
		if (target_sd->s_type & CONFIGFS_USET_DROPPING) {
			spin_unlock(&configfs_dirent_lock);
			config_item_put(item);
			kfree(sl);
			return -ENOENT;
		}
		list_add(&sl->sl_list, &target_sd->s_links);
		spin_unlock(&configfs_dirent_lock);
		ret = configfs_create_link(sl, parent_item->ci_dentry,
					   dentry);
		if (ret) {
			spin_lock(&configfs_dirent_lock);
			list_del_init(&sl->sl_list);
			spin_unlock(&configfs_dirent_lock);
			config_item_put(item);
			kfree(sl);
		}
	}

out:
	return ret;
}