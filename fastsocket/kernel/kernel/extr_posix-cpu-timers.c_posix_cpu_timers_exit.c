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
struct TYPE_2__ {int /*<<< orphan*/  sum_exec_runtime; } ;
struct task_struct {TYPE_1__ se; int /*<<< orphan*/  stime; int /*<<< orphan*/  utime; int /*<<< orphan*/  cpu_timers; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_timers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void posix_cpu_timers_exit(struct task_struct *tsk)
{
	cleanup_timers(tsk->cpu_timers,
		       tsk->utime, tsk->stime, tsk->se.sum_exec_runtime);

}