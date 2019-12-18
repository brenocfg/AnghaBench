#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_6__ {int mnt_ioflags; int /*<<< orphan*/  mnt_max_swappin_available; } ;
struct TYPE_5__ {TYPE_3__* v_mount; } ;

/* Variables and functions */
 int MNT_IOFLAGS_SWAPPIN_SUPPORTED ; 
 int /*<<< orphan*/  mount_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  mount_unlock (TYPE_3__*) ; 

int64_t
vnode_getswappin_avail(vnode_t vp)
{
	int64_t	max_swappin_avail = 0;

	mount_lock(vp->v_mount);
	if (vp->v_mount->mnt_ioflags & MNT_IOFLAGS_SWAPPIN_SUPPORTED)
		max_swappin_avail = vp->v_mount->mnt_max_swappin_available;
	mount_unlock(vp->v_mount);

	return (max_swappin_avail);
}