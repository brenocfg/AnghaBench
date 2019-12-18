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
struct TYPE_2__ {scalar_t__ ksp; } ;
struct task_struct {TYPE_1__ thread; } ;
struct switch_stack {unsigned long retpc; scalar_t__ a6; } ;

/* Variables and functions */
 scalar_t__ in_sched_functions (unsigned long) ; 

unsigned long thread_saved_pc(struct task_struct *tsk)
{
	struct switch_stack *sw = (struct switch_stack *)tsk->thread.ksp;

	/* Check whether the thread is blocked in resume() */
	if (in_sched_functions(sw->retpc))
		return ((unsigned long *)sw->a6)[1];
	else
		return sw->retpc;
}