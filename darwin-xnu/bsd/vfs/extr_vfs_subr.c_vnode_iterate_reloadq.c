#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* tqe_next; } ;
struct vnode {TYPE_2__ v_mntvnodes; } ;
typedef  TYPE_4__* mount_t ;
struct TYPE_13__ {TYPE_3__* tqh_first; TYPE_3__** tqh_last; } ;
struct TYPE_12__ {TYPE_6__ mnt_newvnodes; TYPE_6__ mnt_vnodelist; TYPE_6__ mnt_workerqueue; } ;
struct TYPE_9__ {TYPE_3__** tqe_prev; } ;
struct TYPE_11__ {TYPE_1__ v_mntvnodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_EMPTY (TYPE_6__*) ; 
 int /*<<< orphan*/  TAILQ_INIT (TYPE_6__*) ; 
 struct vnode* TAILQ_LAST (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnodelst ; 

int 
vnode_iterate_reloadq(mount_t mp)
{
	int moved = 0;

	/* add the remaining entries in workerq to the end of mount vnode list */
	if (!TAILQ_EMPTY(&mp->mnt_workerqueue)) {
		struct vnode * mvp;
		mvp = TAILQ_LAST(&mp->mnt_vnodelist, vnodelst);
		
		/* Joining the workerque entities to mount vnode list */
		if (mvp)
			mvp->v_mntvnodes.tqe_next = mp->mnt_workerqueue.tqh_first;
		else
			mp->mnt_vnodelist.tqh_first = mp->mnt_workerqueue.tqh_first;
		mp->mnt_workerqueue.tqh_first->v_mntvnodes.tqe_prev = mp->mnt_vnodelist.tqh_last;
		mp->mnt_vnodelist.tqh_last = mp->mnt_workerqueue.tqh_last;
		TAILQ_INIT(&mp->mnt_workerqueue);
	}

	/* add the newvnodes to the head of mount vnode list */
	if (!TAILQ_EMPTY(&mp->mnt_newvnodes)) {
		struct vnode * nlvp;
		nlvp = TAILQ_LAST(&mp->mnt_newvnodes, vnodelst);
		
		mp->mnt_newvnodes.tqh_first->v_mntvnodes.tqe_prev = &mp->mnt_vnodelist.tqh_first;
		nlvp->v_mntvnodes.tqe_next = mp->mnt_vnodelist.tqh_first;
		if(mp->mnt_vnodelist.tqh_first) 
			mp->mnt_vnodelist.tqh_first->v_mntvnodes.tqe_prev = &nlvp->v_mntvnodes.tqe_next;
		else
			mp->mnt_vnodelist.tqh_last = mp->mnt_newvnodes.tqh_last;
		mp->mnt_vnodelist.tqh_first = mp->mnt_newvnodes.tqh_first;
		TAILQ_INIT(&mp->mnt_newvnodes);
		moved = 1;
	}

	return(moved);
}