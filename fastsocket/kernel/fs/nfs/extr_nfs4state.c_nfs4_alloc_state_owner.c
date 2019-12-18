#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  list; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; } ;
struct TYPE_3__ {TYPE_2__* sequence; } ;
struct nfs4_state_owner {int /*<<< orphan*/  so_lru; int /*<<< orphan*/  so_delegreturn_mutex; int /*<<< orphan*/  so_reclaim_seqcount; int /*<<< orphan*/  so_count; TYPE_2__ so_sequence; TYPE_1__ so_seqid; int /*<<< orphan*/  so_states; int /*<<< orphan*/  so_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct nfs4_state_owner* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_init_wait_queue (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  seqcount_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs4_state_owner *
nfs4_alloc_state_owner(void)
{
	struct nfs4_state_owner *sp;

	sp = kzalloc(sizeof(*sp),GFP_NOFS);
	if (!sp)
		return NULL;
	spin_lock_init(&sp->so_lock);
	INIT_LIST_HEAD(&sp->so_states);
	rpc_init_wait_queue(&sp->so_sequence.wait, "Seqid_waitqueue");
	sp->so_seqid.sequence = &sp->so_sequence;
	spin_lock_init(&sp->so_sequence.lock);
	INIT_LIST_HEAD(&sp->so_sequence.list);
	atomic_set(&sp->so_count, 1);
	seqcount_init(&sp->so_reclaim_seqcount);
	mutex_init(&sp->so_delegreturn_mutex);
	INIT_LIST_HEAD(&sp->so_lru);
	return sp;
}