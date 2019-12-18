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
struct vfsmount {int /*<<< orphan*/  mnt_group_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_MNT_SHARED (struct vfsmount*) ; 
 int /*<<< orphan*/  cleanup_group_ids (struct vfsmount*,struct vfsmount*) ; 
 int mnt_alloc_group_id (struct vfsmount*) ; 
 struct vfsmount* next_mnt (struct vfsmount*,struct vfsmount*) ; 

__attribute__((used)) static int invent_group_ids(struct vfsmount *mnt, bool recurse)
{
	struct vfsmount *p;

	for (p = mnt; p; p = recurse ? next_mnt(p, mnt) : NULL) {
		if (!p->mnt_group_id && !IS_MNT_SHARED(p)) {
			int err = mnt_alloc_group_id(p);
			if (err) {
				cleanup_group_ids(mnt, p);
				return err;
			}
		}
	}

	return 0;
}