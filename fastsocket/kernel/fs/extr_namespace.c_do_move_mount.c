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
struct vfsmount {int /*<<< orphan*/  mnt_expire; struct vfsmount* mnt_parent; TYPE_1__* mnt_root; } ;
struct path {TYPE_1__* dentry; struct vfsmount* mnt; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_mode; } ;
struct TYPE_3__ {TYPE_2__* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int ELOOP ; 
 int ENOENT ; 
 int EPERM ; 
 scalar_t__ IS_DEADDIR (TYPE_2__*) ; 
 scalar_t__ IS_MNT_SHARED (struct vfsmount*) ; 
 int /*<<< orphan*/  LOOKUP_FOLLOW ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int __follow_down (struct path*,int) ; 
 int attach_recursive_mnt (struct vfsmount*,struct path*,struct path*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_mnt (struct vfsmount*) ; 
 scalar_t__ d_unlinked (TYPE_1__*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int kern_path (char*,int /*<<< orphan*/ ,struct path*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  namespace_sem ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 scalar_t__ tree_contains_unbindable (struct vfsmount*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_move_mount(struct path *path, char *old_name)
{
	struct path old_path, parent_path;
	struct vfsmount *p;
	int err = 0;
	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;
	if (!old_name || !*old_name)
		return -EINVAL;
	err = kern_path(old_name, LOOKUP_FOLLOW, &old_path);
	if (err)
		return err;

	down_write(&namespace_sem);
	err = __follow_down(path, true);
	if (err < 0)
		goto out;

	err = -EINVAL;
	if (!check_mnt(path->mnt) || !check_mnt(old_path.mnt))
		goto out;

	err = -ENOENT;
	mutex_lock(&path->dentry->d_inode->i_mutex);
	if (IS_DEADDIR(path->dentry->d_inode))
		goto out1;

	if (d_unlinked(path->dentry))
		goto out1;

	err = -EINVAL;
	if (old_path.dentry != old_path.mnt->mnt_root)
		goto out1;

	if (old_path.mnt == old_path.mnt->mnt_parent)
		goto out1;

	if (S_ISDIR(path->dentry->d_inode->i_mode) !=
	      S_ISDIR(old_path.dentry->d_inode->i_mode))
		goto out1;
	/*
	 * Don't move a mount residing in a shared parent.
	 */
	if (old_path.mnt->mnt_parent &&
	    IS_MNT_SHARED(old_path.mnt->mnt_parent))
		goto out1;
	/*
	 * Don't move a mount tree containing unbindable mounts to a destination
	 * mount which is shared.
	 */
	if (IS_MNT_SHARED(path->mnt) &&
	    tree_contains_unbindable(old_path.mnt))
		goto out1;
	err = -ELOOP;
	for (p = path->mnt; p->mnt_parent != p; p = p->mnt_parent)
		if (p == old_path.mnt)
			goto out1;

	err = attach_recursive_mnt(old_path.mnt, path, &parent_path);
	if (err)
		goto out1;

	/* if the mount is moved, it should no longer be expire
	 * automatically */
	list_del_init(&old_path.mnt->mnt_expire);
out1:
	mutex_unlock(&path->dentry->d_inode->i_mutex);
out:
	up_write(&namespace_sem);
	if (!err)
		path_put(&parent_path);
	path_put(&old_path);
	return err;
}