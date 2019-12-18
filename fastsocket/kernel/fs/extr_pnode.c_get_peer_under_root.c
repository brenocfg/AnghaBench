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
struct vfsmount {int /*<<< orphan*/  mnt_root; struct mnt_namespace* mnt_ns; } ;
struct path {int dummy; } ;
struct mnt_namespace {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_path_reachable (struct vfsmount*,int /*<<< orphan*/ ,struct path const*) ; 
 struct vfsmount* next_peer (struct vfsmount*) ; 

__attribute__((used)) static struct vfsmount *get_peer_under_root(struct vfsmount *mnt,
					    struct mnt_namespace *ns,
					    const struct path *root)
{
	struct vfsmount *m = mnt;

	do {
		/* Check the namespace first for optimization */
		if (m->mnt_ns == ns && is_path_reachable(m, m->mnt_root, root))
			return m;

		m = next_peer(m);
	} while (m != mnt);

	return NULL;
}