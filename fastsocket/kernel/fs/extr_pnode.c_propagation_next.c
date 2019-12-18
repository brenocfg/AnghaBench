#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * next; } ;
struct vfsmount {int /*<<< orphan*/  mnt_slave_list; TYPE_1__ mnt_slave; struct vfsmount* mnt_master; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_MNT_NEW (struct vfsmount*) ; 
 struct vfsmount* first_slave (struct vfsmount*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct vfsmount* next_peer (struct vfsmount*) ; 
 struct vfsmount* next_slave (struct vfsmount*) ; 

__attribute__((used)) static struct vfsmount *propagation_next(struct vfsmount *m,
					 struct vfsmount *origin)
{
	/* are there any slaves of this mount? */
	if (!IS_MNT_NEW(m) && !list_empty(&m->mnt_slave_list))
		return first_slave(m);

	while (1) {
		struct vfsmount *next;
		struct vfsmount *master = m->mnt_master;

		if (master == origin->mnt_master) {
			next = next_peer(m);
			return ((next == origin) ? NULL : next);
		} else if (m->mnt_slave.next != &master->mnt_slave_list)
			return next_slave(m);

		/* back at master */
		m = master;
	}
}