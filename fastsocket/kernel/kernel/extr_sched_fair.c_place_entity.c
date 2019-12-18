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
typedef  unsigned long u64 ;
struct sched_entity {unsigned long vruntime; } ;
struct cfs_rq {unsigned long min_vruntime; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENTLE_FAIR_SLEEPERS ; 
 int /*<<< orphan*/  START_DEBIT ; 
 unsigned long max_vruntime (unsigned long,unsigned long) ; 
 scalar_t__ sched_feat (int /*<<< orphan*/ ) ; 
 scalar_t__ sched_vslice (struct cfs_rq*,struct sched_entity*) ; 
 unsigned long sysctl_sched_latency ; 

__attribute__((used)) static void
place_entity(struct cfs_rq *cfs_rq, struct sched_entity *se, int initial)
{
	u64 vruntime = cfs_rq->min_vruntime;

	/*
	 * The 'current' period is already promised to the current tasks,
	 * however the extra weight of the new task will slow them down a
	 * little, place the new task so that it fits in the slot that
	 * stays open at the end.
	 */
	if (initial && sched_feat(START_DEBIT))
		vruntime += sched_vslice(cfs_rq, se);

	/* sleeps up to a single latency don't count. */
	if (!initial) {
		unsigned long thresh = sysctl_sched_latency;

		/*
		 * Halve their sleep time's effect, to allow
		 * for a gentler effect of sleepers:
		 */
		if (sched_feat(GENTLE_FAIR_SLEEPERS))
			thresh >>= 1;

		vruntime -= thresh;
	}

	/* ensure we never gain time by being placed backwards. */
	vruntime = max_vruntime(se->vruntime, vruntime);

	se->vruntime = vruntime;
}