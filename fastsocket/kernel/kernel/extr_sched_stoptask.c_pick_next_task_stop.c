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
struct task_struct {scalar_t__ state; } ;
struct rq {struct task_struct* stop; } ;

/* Variables and functions */
 scalar_t__ TASK_RUNNING ; 

__attribute__((used)) static struct task_struct *pick_next_task_stop(struct rq *rq)
{
	struct task_struct *stop = rq->stop;

	if (stop && stop->state == TASK_RUNNING)
		return stop;

	return NULL;
}