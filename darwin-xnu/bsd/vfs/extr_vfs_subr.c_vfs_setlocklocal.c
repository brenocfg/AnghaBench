#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mount_t ;
struct TYPE_6__ {int /*<<< orphan*/  mnt_kern_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  MNTK_LOCK_LOCAL ; 
 int /*<<< orphan*/  mount_lock_spin (TYPE_1__*) ; 
 int /*<<< orphan*/  mount_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  setlocklocal_callback ; 
 int /*<<< orphan*/  vnode_iterate (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
vfs_setlocklocal(mount_t mp)
{
	mount_lock_spin(mp);
	mp->mnt_kern_flag |= MNTK_LOCK_LOCAL;
	mount_unlock(mp);

	/*
	 * The number of active vnodes is expected to be
	 * very small when vfs_setlocklocal is invoked.
	 */
	vnode_iterate(mp, 0, setlocklocal_callback, NULL);
}