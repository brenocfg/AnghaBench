#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* vnode_t ;
typedef  TYPE_4__* mount_t ;
struct TYPE_14__ {int /*<<< orphan*/ * tqh_first; int /*<<< orphan*/  tqh_last; } ;
struct TYPE_11__ {int /*<<< orphan*/  tqh_last; int /*<<< orphan*/ * tqh_first; } ;
struct TYPE_13__ {TYPE_6__ mnt_newvnodes; TYPE_6__ mnt_vnodelist; TYPE_2__ mnt_workerqueue; } ;
struct TYPE_10__ {int /*<<< orphan*/ ** tqe_prev; } ;
struct TYPE_12__ {TYPE_1__ v_mntvnodes; } ;

/* Variables and functions */
 scalar_t__ TAILQ_EMPTY (TYPE_6__*) ; 
 TYPE_3__* TAILQ_FIRST (TYPE_6__*) ; 
 int /*<<< orphan*/  TAILQ_INIT (TYPE_6__*) ; 
 int /*<<< orphan*/  panic (char*) ; 

int
vnode_iterate_prepare(mount_t mp)
{
	vnode_t vp;

	if (TAILQ_EMPTY(&mp->mnt_vnodelist)) {
		/* nothing to do */
		return (0);
	} 

	vp = TAILQ_FIRST(&mp->mnt_vnodelist);
	vp->v_mntvnodes.tqe_prev = &(mp->mnt_workerqueue.tqh_first);
	mp->mnt_workerqueue.tqh_first = mp->mnt_vnodelist.tqh_first;
	mp->mnt_workerqueue.tqh_last = mp->mnt_vnodelist.tqh_last;

	TAILQ_INIT(&mp->mnt_vnodelist);
	if (mp->mnt_newvnodes.tqh_first != NULL)
		panic("vnode_iterate_prepare: newvnode when entering vnode");
	TAILQ_INIT(&mp->mnt_newvnodes);

	return (1);
}