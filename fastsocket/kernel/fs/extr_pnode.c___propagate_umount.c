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
struct vfsmount {int /*<<< orphan*/  mnt_hash; int /*<<< orphan*/  mnt_mounts; int /*<<< orphan*/  mnt_mountpoint; struct vfsmount* mnt_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct vfsmount* __lookup_mnt (struct vfsmount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct vfsmount* propagation_next (struct vfsmount*,struct vfsmount*) ; 

__attribute__((used)) static void __propagate_umount(struct vfsmount *mnt)
{
	struct vfsmount *parent = mnt->mnt_parent;
	struct vfsmount *m;

	BUG_ON(parent == mnt);

	for (m = propagation_next(parent, parent); m;
			m = propagation_next(m, parent)) {

		struct vfsmount *child = __lookup_mnt(m,
					mnt->mnt_mountpoint, 0);
		/*
		 * umount the child only if the child has no
		 * other children
		 */
		if (child && list_empty(&child->mnt_mounts))
			list_move_tail(&child->mnt_hash, &mnt->mnt_hash);
	}
}