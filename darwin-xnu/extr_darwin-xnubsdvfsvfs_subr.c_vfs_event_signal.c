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
typedef  scalar_t__ u_int32_t ;
struct mount {int /*<<< orphan*/  mnt_kern_flag; } ;
typedef  int /*<<< orphan*/  fsid_t ;

/* Variables and functions */
 int /*<<< orphan*/  KNOTE (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  MNT_LNOTRESP ; 
 scalar_t__ VQ_DEAD ; 
 scalar_t__ VQ_NOTRESP ; 
 int /*<<< orphan*/  fs_klist ; 
 int /*<<< orphan*/  fs_klist_lock ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mount_lock_spin (struct mount*) ; 
 int /*<<< orphan*/  mount_unlock (struct mount*) ; 
 struct mount* vfs_getvfs (int /*<<< orphan*/ *) ; 

void
vfs_event_signal(fsid_t *fsid, u_int32_t event, intptr_t data)
{
	if (event == VQ_DEAD || event == VQ_NOTRESP) {
		struct mount *mp = vfs_getvfs(fsid);
		if (mp) {
			mount_lock_spin(mp);
			if (data)
				mp->mnt_kern_flag &= ~MNT_LNOTRESP;	// Now responding
			else
				mp->mnt_kern_flag |= MNT_LNOTRESP;	// Not responding
			mount_unlock(mp);
		}
	}

	lck_mtx_lock(fs_klist_lock);
	KNOTE(&fs_klist, event);
	lck_mtx_unlock(fs_klist_lock);
}