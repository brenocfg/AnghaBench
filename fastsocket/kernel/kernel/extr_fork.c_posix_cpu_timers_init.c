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
struct TYPE_2__ {scalar_t__ sched_exp; void* virt_exp; void* prof_exp; } ;
struct task_struct {int /*<<< orphan*/ * cpu_timers; TYPE_1__ cputime_expires; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* cputime_zero ; 

__attribute__((used)) static void posix_cpu_timers_init(struct task_struct *tsk)
{
	tsk->cputime_expires.prof_exp = cputime_zero;
	tsk->cputime_expires.virt_exp = cputime_zero;
	tsk->cputime_expires.sched_exp = 0;
	INIT_LIST_HEAD(&tsk->cpu_timers[0]);
	INIT_LIST_HEAD(&tsk->cpu_timers[1]);
	INIT_LIST_HEAD(&tsk->cpu_timers[2]);
}