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
typedef  int umode_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct dentry {struct configfs_dirent* d_fsdata; int /*<<< orphan*/ * d_op; int /*<<< orphan*/  d_inode; TYPE_1__ d_name; } ;
struct configfs_dirent {int /*<<< orphan*/  s_sibling; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 int CONFIGFS_DIR ; 
 int CONFIGFS_USET_CREATING ; 
 int S_IFDIR ; 
 int S_IRUGO ; 
 int S_IRWXU ; 
 int S_IXUGO ; 
 int configfs_create (struct dentry*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configfs_dentry_ops ; 
 int configfs_dirent_exists (struct configfs_dirent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configfs_dirent_lock ; 
 int configfs_make_dirent (struct configfs_dirent*,struct dentry*,struct config_item*,int,int) ; 
 int /*<<< orphan*/  configfs_put (struct configfs_dirent*) ; 
 int /*<<< orphan*/  configfs_set_dir_dirent_depth (struct configfs_dirent*,struct configfs_dirent*) ; 
 int /*<<< orphan*/  inc_nlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_dir ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_dir(struct config_item * k, struct dentry * p,
		      struct dentry * d)
{
	int error;
	umode_t mode = S_IFDIR| S_IRWXU | S_IRUGO | S_IXUGO;

	error = configfs_dirent_exists(p->d_fsdata, d->d_name.name);
	if (!error)
		error = configfs_make_dirent(p->d_fsdata, d, k, mode,
					     CONFIGFS_DIR | CONFIGFS_USET_CREATING);
	if (!error) {
		configfs_set_dir_dirent_depth(p->d_fsdata, d->d_fsdata);
		error = configfs_create(d, mode, init_dir);
		if (!error) {
			inc_nlink(p->d_inode);
			(d)->d_op = &configfs_dentry_ops;
		} else {
			struct configfs_dirent *sd = d->d_fsdata;
			if (sd) {
				spin_lock(&configfs_dirent_lock);
				list_del_init(&sd->s_sibling);
				spin_unlock(&configfs_dirent_lock);
				configfs_put(sd);
			}
		}
	}
	return error;
}