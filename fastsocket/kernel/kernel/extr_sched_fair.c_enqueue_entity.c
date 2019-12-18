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
struct sched_entity {int on_rq; int /*<<< orphan*/  vruntime; } ;
struct cfs_rq {int nr_running; struct sched_entity* curr; scalar_t__ min_vruntime; } ;

/* Variables and functions */
 int ENQUEUE_WAKEUP ; 
 int ENQUEUE_WAKING ; 
 int /*<<< orphan*/  __enqueue_entity (struct cfs_rq*,struct sched_entity*) ; 
 int /*<<< orphan*/  account_entity_enqueue (struct cfs_rq*,struct sched_entity*) ; 
 int /*<<< orphan*/  check_enqueue_throttle (struct cfs_rq*) ; 
 int /*<<< orphan*/  check_spread (struct cfs_rq*,struct sched_entity*) ; 
 int /*<<< orphan*/  enqueue_sleeper (struct cfs_rq*,struct sched_entity*) ; 
 int /*<<< orphan*/  list_add_leaf_cfs_rq (struct cfs_rq*) ; 
 int /*<<< orphan*/  place_entity (struct cfs_rq*,struct sched_entity*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_cfs_load (struct cfs_rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_cfs_shares (struct cfs_rq*) ; 
 int /*<<< orphan*/  update_curr (struct cfs_rq*) ; 
 int /*<<< orphan*/  update_stats_enqueue (struct cfs_rq*,struct sched_entity*) ; 

__attribute__((used)) static void
enqueue_entity(struct cfs_rq *cfs_rq, struct sched_entity *se, int flags)
{
	/*
	 * Update the normalized vruntime before updating min_vruntime
	 * through callig update_curr().
	 */
	if (!(flags & ENQUEUE_WAKEUP) || (flags & ENQUEUE_WAKING))
		se->vruntime += cfs_rq->min_vruntime;

	/*
	 * Update run-time statistics of the 'current'.
	 */
	update_curr(cfs_rq);
	update_cfs_load(cfs_rq, 0);
	account_entity_enqueue(cfs_rq, se);
	update_cfs_shares(cfs_rq);

	if (flags & ENQUEUE_WAKEUP) {
		place_entity(cfs_rq, se, 0);
		enqueue_sleeper(cfs_rq, se);
	}

	update_stats_enqueue(cfs_rq, se);
	check_spread(cfs_rq, se);
	if (se != cfs_rq->curr)
		__enqueue_entity(cfs_rq, se);
	se->on_rq = 1;

	if (cfs_rq->nr_running == 1) {
		list_add_leaf_cfs_rq(cfs_rq);
		check_enqueue_throttle(cfs_rq);
	}
}