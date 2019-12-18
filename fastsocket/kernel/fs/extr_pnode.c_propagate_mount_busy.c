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
struct vfsmount {int /*<<< orphan*/  mnt_mounts; int /*<<< orphan*/  mnt_mountpoint; struct vfsmount* mnt_parent; } ;

/* Variables and functions */
 struct vfsmount* __lookup_mnt (struct vfsmount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int do_refcount_check (struct vfsmount*,int) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 struct vfsmount* propagation_next (struct vfsmount*,struct vfsmount*) ; 

int propagate_mount_busy(struct vfsmount *mnt, int refcnt)
{
	struct vfsmount *m, *child;
	struct vfsmount *parent = mnt->mnt_parent;
	int ret = 0;

	if (mnt == parent)
		return do_refcount_check(mnt, refcnt);

	/*
	 * quickly check if the current mount can be unmounted.
	 * If not, we don't have to go checking for all other
	 * mounts
	 */
	if (!list_empty(&mnt->mnt_mounts) || do_refcount_check(mnt, refcnt))
		return 1;

	for (m = propagation_next(parent, parent); m;
	     		m = propagation_next(m, parent)) {
		child = __lookup_mnt(m, mnt->mnt_mountpoint, 0);
		if (child && list_empty(&child->mnt_mounts) &&
		    (ret = do_refcount_check(child, 1)))
			break;
	}
	return ret;
}