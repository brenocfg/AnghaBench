#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/  s_umount; } ;
struct path {scalar_t__ dentry; TYPE_1__* mnt; } ;
struct TYPE_4__ {scalar_t__ mnt_root; int mnt_flags; int /*<<< orphan*/  mnt_ns; struct super_block* mnt_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int EPERM ; 
 int MS_BIND ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int change_mount_flags (TYPE_1__*,int) ; 
 int /*<<< orphan*/  check_mnt (TYPE_1__*) ; 
 int do_remount_sb (struct super_block*,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  security_sb_post_remount (TYPE_1__*,int,void*) ; 
 int security_sb_remount (struct super_block*,void*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  touch_mnt_namespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfsmount_lock ; 

__attribute__((used)) static int do_remount(struct path *path, int flags, int mnt_flags,
		      void *data)
{
	int err;
	struct super_block *sb = path->mnt->mnt_sb;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	if (!check_mnt(path->mnt))
		return -EINVAL;

	if (path->dentry != path->mnt->mnt_root)
		return -EINVAL;

	err = security_sb_remount(sb, data);
	if (err)
		return err;

	down_write(&sb->s_umount);
	if (flags & MS_BIND)
		err = change_mount_flags(path->mnt, flags);
	else
		err = do_remount_sb(sb, flags, data, 0);
	if (!err)
		path->mnt->mnt_flags = mnt_flags;
	up_write(&sb->s_umount);
	if (!err) {
		security_sb_post_remount(path->mnt, flags, data);

		spin_lock(&vfsmount_lock);
		touch_mnt_namespace(path->mnt->mnt_ns);
		spin_unlock(&vfsmount_lock);
	}
	return err;
}