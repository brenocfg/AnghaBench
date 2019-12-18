#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
struct mount {int dummy; } ;
typedef  TYPE_2__* mount_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_11__ {scalar_t__ mnt_crossref; } ;
struct TYPE_10__ {TYPE_2__* v_mountedhere; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_ZONE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_MOUNT ; 
 int /*<<< orphan*/  mac_mount_label_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  mount_lock_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  vnode_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_put_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_unlock (TYPE_1__*) ; 

void
mount_dropcrossref(mount_t mp, vnode_t dp, int need_put)
{
	vnode_lock(dp);
	mp->mnt_crossref--;

	if (mp->mnt_crossref < 0)
		panic("mount cross refs -ve");

	if ((mp != dp->v_mountedhere) && (mp->mnt_crossref == 0)) {

		if (need_put)
			vnode_put_locked(dp);
		vnode_unlock(dp);

		mount_lock_destroy(mp);
#if CONFIG_MACF
		mac_mount_label_destroy(mp);
#endif
		FREE_ZONE((caddr_t)mp, sizeof (struct mount), M_MOUNT);
		return;
	}
	if (need_put)
		vnode_put_locked(dp);
	vnode_unlock(dp);
}