#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sched_entity {int /*<<< orphan*/  exec_start; } ;
struct cfs_rq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  clock; } ;

/* Variables and functions */
 TYPE_1__* rq_of (struct cfs_rq*) ; 

__attribute__((used)) static inline void
update_stats_curr_start(struct cfs_rq *cfs_rq, struct sched_entity *se)
{
	/*
	 * We are starting a new run period:
	 */
	se->exec_start = rq_of(cfs_rq)->clock;
}