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
typedef  scalar_t__ u64 ;
struct rq {int dummy; } ;
struct cfs_rq {int load_stamp; scalar_t__ min_vruntime; struct rq* rq; int /*<<< orphan*/  tasks; int /*<<< orphan*/  tasks_timeline; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 

__attribute__((used)) static void init_cfs_rq(struct cfs_rq *cfs_rq, struct rq *rq)
{
	cfs_rq->tasks_timeline = RB_ROOT;
	INIT_LIST_HEAD(&cfs_rq->tasks);
#ifdef CONFIG_FAIR_GROUP_SCHED
	cfs_rq->rq = rq;
	/* allow initial update_cfs_load() to truncate */
	cfs_rq->load_stamp = 1;
#endif
	cfs_rq->min_vruntime = (u64)(-(1LL << 20));
}