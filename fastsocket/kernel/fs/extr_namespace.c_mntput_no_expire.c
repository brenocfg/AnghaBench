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
struct vfsmount {scalar_t__ mnt_pinned; int /*<<< orphan*/  mnt_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mntput (struct vfsmount*) ; 
 int /*<<< orphan*/  acct_auto_close_mnt (struct vfsmount*) ; 
 int /*<<< orphan*/  atomic_add (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  security_sb_umount_close (struct vfsmount*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfsmount_lock ; 

void mntput_no_expire(struct vfsmount *mnt)
{
repeat:
	if (atomic_dec_and_lock(&mnt->mnt_count, &vfsmount_lock)) {
		if (likely(!mnt->mnt_pinned)) {
			spin_unlock(&vfsmount_lock);
			__mntput(mnt);
			return;
		}
		atomic_add(mnt->mnt_pinned + 1, &mnt->mnt_count);
		mnt->mnt_pinned = 0;
		spin_unlock(&vfsmount_lock);
		acct_auto_close_mnt(mnt);
		security_sb_umount_close(mnt);
		goto repeat;
	}
}