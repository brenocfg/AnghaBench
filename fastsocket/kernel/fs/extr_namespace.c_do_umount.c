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
struct vfsmount {int /*<<< orphan*/  mnt_list; int /*<<< orphan*/  mnt_expiry_mark; int /*<<< orphan*/  mnt_count; struct super_block* mnt_sb; } ;
struct super_block {int s_flags; int /*<<< orphan*/  s_umount; TYPE_1__* s_op; } ;
struct TYPE_8__ {TYPE_3__* fs; } ;
struct TYPE_6__ {struct vfsmount* mnt; } ;
struct TYPE_7__ {TYPE_2__ root; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* umount_begin ) (struct super_block*) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int MNT_DETACH ; 
 int MNT_EXPIRE ; 
 int MNT_FORCE ; 
 int MS_RDONLY ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_4__* current ; 
 int do_remount_sb (struct super_block*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  namespace_sem ; 
 int /*<<< orphan*/  propagate_mount_busy (struct vfsmount*,int) ; 
 int /*<<< orphan*/  release_mounts (int /*<<< orphan*/ *) ; 
 int security_sb_umount (struct vfsmount*,int) ; 
 int /*<<< orphan*/  security_sb_umount_busy (struct vfsmount*) ; 
 int /*<<< orphan*/  shrink_submounts (struct vfsmount*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct super_block*) ; 
 int /*<<< orphan*/  umount_list ; 
 int /*<<< orphan*/  umount_tree (struct vfsmount*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfsmount_lock ; 
 int /*<<< orphan*/  xchg (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int do_umount(struct vfsmount *mnt, int flags)
{
	struct super_block *sb = mnt->mnt_sb;
	int retval;
	LIST_HEAD(umount_list);

	retval = security_sb_umount(mnt, flags);
	if (retval)
		return retval;

	/*
	 * Allow userspace to request a mountpoint be expired rather than
	 * unmounting unconditionally. Unmount only happens if:
	 *  (1) the mark is already set (the mark is cleared by mntput())
	 *  (2) the usage count == 1 [parent vfsmount] + 1 [sys_umount]
	 */
	if (flags & MNT_EXPIRE) {
		if (mnt == current->fs->root.mnt ||
		    flags & (MNT_FORCE | MNT_DETACH))
			return -EINVAL;

		if (atomic_read(&mnt->mnt_count) != 2)
			return -EBUSY;

		if (!xchg(&mnt->mnt_expiry_mark, 1))
			return -EAGAIN;
	}

	/*
	 * If we may have to abort operations to get out of this
	 * mount, and they will themselves hold resources we must
	 * allow the fs to do things. In the Unix tradition of
	 * 'Gee thats tricky lets do it in userspace' the umount_begin
	 * might fail to complete on the first run through as other tasks
	 * must return, and the like. Thats for the mount program to worry
	 * about for the moment.
	 */

	if (flags & MNT_FORCE && sb->s_op->umount_begin) {
		sb->s_op->umount_begin(sb);
	}

	/*
	 * No sense to grab the lock for this test, but test itself looks
	 * somewhat bogus. Suggestions for better replacement?
	 * Ho-hum... In principle, we might treat that as umount + switch
	 * to rootfs. GC would eventually take care of the old vfsmount.
	 * Actually it makes sense, especially if rootfs would contain a
	 * /reboot - static binary that would close all descriptors and
	 * call reboot(9). Then init(8) could umount root and exec /reboot.
	 */
	if (mnt == current->fs->root.mnt && !(flags & MNT_DETACH)) {
		/*
		 * Special case for "unmounting" root ...
		 * we just try to remount it readonly.
		 */
		down_write(&sb->s_umount);
		if (!(sb->s_flags & MS_RDONLY))
			retval = do_remount_sb(sb, MS_RDONLY, NULL, 0);
		up_write(&sb->s_umount);
		return retval;
	}

	down_write(&namespace_sem);
	spin_lock(&vfsmount_lock);
	event++;

	if (!(flags & MNT_DETACH))
		shrink_submounts(mnt, &umount_list);

	retval = -EBUSY;
	if (flags & MNT_DETACH || !propagate_mount_busy(mnt, 2)) {
		if (!list_empty(&mnt->mnt_list))
			umount_tree(mnt, 1, &umount_list);
		retval = 0;
	}
	spin_unlock(&vfsmount_lock);
	if (retval)
		security_sb_umount_busy(mnt);
	up_write(&namespace_sem);
	release_mounts(&umount_list);
	return retval;
}