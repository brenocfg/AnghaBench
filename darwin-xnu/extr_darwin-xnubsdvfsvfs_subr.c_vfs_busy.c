#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mount_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_5__ {int mnt_lflag; int /*<<< orphan*/  mnt_rwlock; int /*<<< orphan*/  mnt_mlock; } ;

/* Variables and functions */
 int ENOENT ; 
 int LK_NOWAIT ; 
 int MNT_LDEAD ; 
 int MNT_LUNMOUNT ; 
 int MNT_LWAIT ; 
 int PDROP ; 
 int PVFS ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mount_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  mount_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *) ; 

int
vfs_busy(mount_t mp, int flags)
{

restart:
	if (mp->mnt_lflag & MNT_LDEAD)
		return (ENOENT);

	mount_lock(mp);

	if (mp->mnt_lflag & MNT_LUNMOUNT) {
		if (flags & LK_NOWAIT || mp->mnt_lflag & MNT_LDEAD) {
		        mount_unlock(mp);
			return (ENOENT);
		}

		/*
		 * Since all busy locks are shared except the exclusive
		 * lock granted when unmounting, the only place that a
		 * wakeup needs to be done is at the release of the
		 * exclusive lock at the end of dounmount.
		 */
		mp->mnt_lflag |= MNT_LWAIT;
		msleep((caddr_t)mp, &mp->mnt_mlock, (PVFS | PDROP), "vfsbusy", NULL);
		return (ENOENT);
	}

	mount_unlock(mp);

	lck_rw_lock_shared(&mp->mnt_rwlock);

	/* 
	 * Until we are granted the rwlock, it's possible for the mount point to
	 * change state, so re-evaluate before granting the vfs_busy.
	 */
	if (mp->mnt_lflag & (MNT_LDEAD | MNT_LUNMOUNT)) {
		lck_rw_done(&mp->mnt_rwlock);
		goto restart;
	}
	return (0);
}