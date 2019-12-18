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
struct TYPE_2__ {scalar_t__ sum_exec_runtime; } ;
struct task_struct {TYPE_1__ se; int /*<<< orphan*/  stime; int /*<<< orphan*/  utime; struct signal_struct* signal; } ;
struct signal_struct {scalar_t__ sum_sched_runtime; int /*<<< orphan*/  stime; int /*<<< orphan*/  utime; int /*<<< orphan*/  cpu_timers; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_timers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cputime_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void posix_cpu_timers_exit_group(struct task_struct *tsk)
{
	struct signal_struct *const sig = tsk->signal;

	cleanup_timers(tsk->signal->cpu_timers,
		       cputime_add(tsk->utime, sig->utime),
		       cputime_add(tsk->stime, sig->stime),
		       tsk->se.sum_exec_runtime + sig->sum_sched_runtime);
}