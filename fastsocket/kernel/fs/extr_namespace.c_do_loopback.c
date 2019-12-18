#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vfsmount {int dummy; } ;
struct path {int /*<<< orphan*/  dentry; int /*<<< orphan*/  mnt; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_MNT_UNBINDABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int LOOKUP_AUTOMOUNT ; 
 int LOOKUP_FOLLOW ; 
 int /*<<< orphan*/  check_mnt (int /*<<< orphan*/ ) ; 
 struct vfsmount* clone_mnt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vfsmount* copy_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int graft_tree (struct vfsmount*,struct path*) ; 
 int kern_path (char*,int,struct path*) ; 
 scalar_t__ mnt_ns_loop (struct path*) ; 
 int mount_is_safe (struct path*) ; 
 int /*<<< orphan*/  namespace_sem ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  release_mounts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umount_list ; 
 int /*<<< orphan*/  umount_tree (struct vfsmount*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfsmount_lock ; 

__attribute__((used)) static int do_loopback(struct path *path, char *old_name,
				int recurse)
{
	struct path old_path;
	struct vfsmount *mnt = NULL;
	int err = mount_is_safe(path);
	if (err)
		return err;
	if (!old_name || !*old_name)
		return -EINVAL;
	err = kern_path(old_name, LOOKUP_FOLLOW|LOOKUP_AUTOMOUNT, &old_path);
	if (err)
		return err;

	err = -EINVAL;
	if (mnt_ns_loop(&old_path))
		goto out;

	down_write(&namespace_sem);
	err = -EINVAL;
	if (IS_MNT_UNBINDABLE(old_path.mnt))
		goto out;

	if (!check_mnt(path->mnt) || !check_mnt(old_path.mnt))
		goto out;

	err = -ENOMEM;
	if (recurse)
		mnt = copy_tree(old_path.mnt, old_path.dentry, 0);
	else
		mnt = clone_mnt(old_path.mnt, old_path.dentry, 0);

	if (!mnt)
		goto out;

	err = graft_tree(mnt, path);
	if (err) {
		LIST_HEAD(umount_list);
		spin_lock(&vfsmount_lock);
		umount_tree(mnt, 0, &umount_list);
		spin_unlock(&vfsmount_lock);
		release_mounts(&umount_list);
	}

out:
	up_write(&namespace_sem);
	path_put(&old_path);
	return err;
}