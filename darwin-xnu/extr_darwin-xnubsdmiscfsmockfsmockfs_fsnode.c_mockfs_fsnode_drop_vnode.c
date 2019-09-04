#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vnode_t ;
typedef  TYPE_2__* mockfs_mount_t ;
typedef  TYPE_3__* mockfs_fsnode_t ;
struct TYPE_7__ {int /*<<< orphan*/ * vp; TYPE_1__* mnt; } ;
struct TYPE_6__ {int /*<<< orphan*/  mockfs_mnt_mtx; } ;
struct TYPE_5__ {scalar_t__ mnt_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  vnode_clearfsnode (int /*<<< orphan*/ *) ; 

int mockfs_fsnode_drop_vnode(mockfs_fsnode_t fsnp)
{
	int rvalue;
	mockfs_mount_t mockfs_mnt;
	vnode_t vp;

	rvalue = 0;

	if (!fsnp) {
		rvalue = EINVAL;
		goto done;
	}

	mockfs_mnt = ((mockfs_mount_t) fsnp->mnt->mnt_data);
	lck_mtx_lock(&mockfs_mnt->mockfs_mnt_mtx);

	if (!(fsnp->vp)) {
		panic("mock_fsnode_drop_vnode: target fsnode does not have an associated vnode");
	}

	vp = fsnp->vp;
	fsnp->vp = NULL;
	vnode_clearfsnode(vp);

	lck_mtx_unlock(&mockfs_mnt->mockfs_mnt_mtx);
done:
	return rvalue;
}