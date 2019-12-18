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
struct task_struct {int dummy; } ;
struct rq {struct task_struct* idle; } ;

/* Variables and functions */
 int /*<<< orphan*/  calc_load_account_active (struct rq*) ; 
 int /*<<< orphan*/  sched_goidle ; 
 int /*<<< orphan*/  schedstat_inc (struct rq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct task_struct *pick_next_task_idle(struct rq *rq)
{
	schedstat_inc(rq, sched_goidle);
	/* adjust the active tasks as we might go into a long sleep */
	calc_load_account_active(rq);
	return rq->idle;
}