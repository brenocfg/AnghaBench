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
struct vfsmount {int mnt_group_id; int /*<<< orphan*/  mnt_ns; struct vfsmount* mnt_master; } ;
struct path {int dummy; } ;

/* Variables and functions */
 struct vfsmount* get_peer_under_root (struct vfsmount*,int /*<<< orphan*/ ,struct path const*) ; 

int get_dominating_id(struct vfsmount *mnt, const struct path *root)
{
	struct vfsmount *m;

	for (m = mnt->mnt_master; m != NULL; m = m->mnt_master) {
		struct vfsmount *d = get_peer_under_root(m, mnt->mnt_ns, root);
		if (d)
			return d->mnt_group_id;
	}

	return 0;
}