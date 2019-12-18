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
struct vfsmount {int /*<<< orphan*/  mnt_flags; int /*<<< orphan*/ * mnt_master; int /*<<< orphan*/  mnt_slave; } ;

/* Variables and functions */
 int /*<<< orphan*/  MNT_UNBINDABLE ; 
 int MS_SHARED ; 
 int MS_SLAVE ; 
 int MS_UNBINDABLE ; 
 int /*<<< orphan*/  do_make_slave (struct vfsmount*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_mnt_shared (struct vfsmount*) ; 

void change_mnt_propagation(struct vfsmount *mnt, int type)
{
	if (type == MS_SHARED) {
		set_mnt_shared(mnt);
		return;
	}
	do_make_slave(mnt);
	if (type != MS_SLAVE) {
		list_del_init(&mnt->mnt_slave);
		mnt->mnt_master = NULL;
		if (type == MS_UNBINDABLE)
			mnt->mnt_flags |= MNT_UNBINDABLE;
		else
			mnt->mnt_flags &= ~MNT_UNBINDABLE;
	}
}