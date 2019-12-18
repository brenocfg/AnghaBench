#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ prev_sum_exec_runtime; scalar_t__ sum_exec_runtime; scalar_t__ nr_wakeups_idle; scalar_t__ nr_wakeups_passive; scalar_t__ nr_wakeups_affine_attempts; scalar_t__ nr_wakeups_affine; scalar_t__ nr_wakeups_remote; scalar_t__ nr_wakeups_local; scalar_t__ nr_wakeups_migrate; scalar_t__ nr_wakeups_sync; scalar_t__ nr_wakeups; scalar_t__ nr_forced_migrations; scalar_t__ nr_failed_migrations_hot; scalar_t__ nr_failed_migrations_running; scalar_t__ nr_failed_migrations_affine; scalar_t__ nr_migrations_cold; scalar_t__ nr_migrations; scalar_t__ slice_max; scalar_t__ exec_max; scalar_t__ block_max; scalar_t__ sum_sleep_runtime; scalar_t__ sleep_max; scalar_t__ iowait_count; scalar_t__ iowait_sum; scalar_t__ wait_count; scalar_t__ wait_sum; scalar_t__ wait_max; } ;
struct TYPE_3__ {scalar_t__ bkl_count; } ;
struct task_struct {scalar_t__ nivcsw; scalar_t__ nvcsw; TYPE_2__ se; TYPE_1__ sched_info; } ;

/* Variables and functions */

void proc_sched_set_task(struct task_struct *p)
{
#ifdef CONFIG_SCHEDSTATS
	p->se.wait_max				= 0;
	p->se.wait_sum				= 0;
	p->se.wait_count			= 0;
	p->se.iowait_sum			= 0;
	p->se.iowait_count			= 0;
	p->se.sleep_max				= 0;
	p->se.sum_sleep_runtime			= 0;
	p->se.block_max				= 0;
	p->se.exec_max				= 0;
	p->se.slice_max				= 0;
	p->se.nr_migrations			= 0;
	p->se.nr_migrations_cold		= 0;
	p->se.nr_failed_migrations_affine	= 0;
	p->se.nr_failed_migrations_running	= 0;
	p->se.nr_failed_migrations_hot		= 0;
	p->se.nr_forced_migrations		= 0;
	p->se.nr_wakeups			= 0;
	p->se.nr_wakeups_sync			= 0;
	p->se.nr_wakeups_migrate		= 0;
	p->se.nr_wakeups_local			= 0;
	p->se.nr_wakeups_remote			= 0;
	p->se.nr_wakeups_affine			= 0;
	p->se.nr_wakeups_affine_attempts	= 0;
	p->se.nr_wakeups_passive		= 0;
	p->se.nr_wakeups_idle			= 0;
	p->sched_info.bkl_count			= 0;
#endif
	p->se.sum_exec_runtime			= 0;
	p->se.prev_sum_exec_runtime		= 0;
	p->nvcsw				= 0;
	p->nivcsw				= 0;
}