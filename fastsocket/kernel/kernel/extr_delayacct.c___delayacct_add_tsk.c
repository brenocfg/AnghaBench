#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timespec {int dummy; } ;
struct taskstats {unsigned long cpu_count; scalar_t__ blkio_delay_total; scalar_t__ swapin_delay_total; scalar_t__ freepages_delay_total; int /*<<< orphan*/  freepages_count; int /*<<< orphan*/  swapin_count; int /*<<< orphan*/  blkio_count; scalar_t__ cpu_run_virtual_total; scalar_t__ cpu_delay_total; scalar_t__ cpu_scaled_run_real_total; scalar_t__ cpu_run_real_total; } ;
struct TYPE_5__ {unsigned long long sum_exec_runtime; } ;
struct TYPE_4__ {unsigned long pcount; unsigned long long run_delay; } ;
struct task_struct {TYPE_3__* delays; TYPE_2__ se; TYPE_1__ sched_info; scalar_t__ stimescaled; scalar_t__ utimescaled; scalar_t__ stime; scalar_t__ utime; } ;
typedef  scalar_t__ s64 ;
struct TYPE_6__ {scalar_t__ blkio_delay; scalar_t__ swapin_delay; scalar_t__ freepages_delay; int /*<<< orphan*/  lock; scalar_t__ freepages_count; scalar_t__ swapin_count; scalar_t__ blkio_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  cputime_to_timespec (scalar_t__,struct timespec*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ timespec_to_ns (struct timespec*) ; 

int __delayacct_add_tsk(struct taskstats *d, struct task_struct *tsk)
{
	s64 tmp;
	unsigned long t1;
	unsigned long long t2, t3;
	unsigned long flags;
	struct timespec ts;

	/* Though tsk->delays accessed later, early exit avoids
	 * unnecessary returning of other data
	 */
	if (!tsk->delays)
		goto done;

	tmp = (s64)d->cpu_run_real_total;
	cputime_to_timespec(tsk->utime + tsk->stime, &ts);
	tmp += timespec_to_ns(&ts);
	d->cpu_run_real_total = (tmp < (s64)d->cpu_run_real_total) ? 0 : tmp;

	tmp = (s64)d->cpu_scaled_run_real_total;
	cputime_to_timespec(tsk->utimescaled + tsk->stimescaled, &ts);
	tmp += timespec_to_ns(&ts);
	d->cpu_scaled_run_real_total =
		(tmp < (s64)d->cpu_scaled_run_real_total) ? 0 : tmp;

	/*
	 * No locking available for sched_info (and too expensive to add one)
	 * Mitigate by taking snapshot of values
	 */
	t1 = tsk->sched_info.pcount;
	t2 = tsk->sched_info.run_delay;
	t3 = tsk->se.sum_exec_runtime;

	d->cpu_count += t1;

	tmp = (s64)d->cpu_delay_total + t2;
	d->cpu_delay_total = (tmp < (s64)d->cpu_delay_total) ? 0 : tmp;

	tmp = (s64)d->cpu_run_virtual_total + t3;
	d->cpu_run_virtual_total =
		(tmp < (s64)d->cpu_run_virtual_total) ?	0 : tmp;

	/* zero XXX_total, non-zero XXX_count implies XXX stat overflowed */

	spin_lock_irqsave(&tsk->delays->lock, flags);
	tmp = d->blkio_delay_total + tsk->delays->blkio_delay;
	d->blkio_delay_total = (tmp < d->blkio_delay_total) ? 0 : tmp;
	tmp = d->swapin_delay_total + tsk->delays->swapin_delay;
	d->swapin_delay_total = (tmp < d->swapin_delay_total) ? 0 : tmp;
	tmp = d->freepages_delay_total + tsk->delays->freepages_delay;
	d->freepages_delay_total = (tmp < d->freepages_delay_total) ? 0 : tmp;
	d->blkio_count += tsk->delays->blkio_count;
	d->swapin_count += tsk->delays->swapin_count;
	d->freepages_count += tsk->delays->freepages_count;
	spin_unlock_irqrestore(&tsk->delays->lock, flags);

done:
	return 0;
}