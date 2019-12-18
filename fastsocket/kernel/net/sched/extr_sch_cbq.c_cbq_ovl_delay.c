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
struct cbq_sched_data {int now; int pmask; int wd_expires; int /*<<< orphan*/  delay_timer; } ;
struct TYPE_3__ {int /*<<< orphan*/  overactions; } ;
struct cbq_class {int undertime; int delayed; int avgidle; int ewma_log; int minidle; int penalized; int cpriority; TYPE_1__ xstats; scalar_t__ penalty; scalar_t__ offtime; int /*<<< orphan*/  qdisc; } ;
typedef  int psched_time_t ;
typedef  int psched_tdiff_t ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSCHED_TICKS2NS (int) ; 
 int TC_CBQ_MAXPRIO ; 
 int /*<<< orphan*/  __QDISC_STATE_DEACTIVATED ; 
 int /*<<< orphan*/  hrtimer_get_expires (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_restart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_set_expires (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hrtimer_try_to_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 struct cbq_sched_data* qdisc_priv (int /*<<< orphan*/ ) ; 
 TYPE_2__* qdisc_root_sleeping (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cbq_ovl_delay(struct cbq_class *cl)
{
	struct cbq_sched_data *q = qdisc_priv(cl->qdisc);
	psched_tdiff_t delay = cl->undertime - q->now;

	if (test_bit(__QDISC_STATE_DEACTIVATED,
		     &qdisc_root_sleeping(cl->qdisc)->state))
		return;

	if (!cl->delayed) {
		psched_time_t sched = q->now;
		ktime_t expires;

		delay += cl->offtime;
		if (cl->avgidle < 0)
			delay -= (-cl->avgidle) - ((-cl->avgidle) >> cl->ewma_log);
		if (cl->avgidle < cl->minidle)
			cl->avgidle = cl->minidle;
		cl->undertime = q->now + delay;

		if (delay > 0) {
			sched += delay + cl->penalty;
			cl->penalized = sched;
			cl->cpriority = TC_CBQ_MAXPRIO;
			q->pmask |= (1<<TC_CBQ_MAXPRIO);

			expires = ktime_set(0, 0);
			expires = ktime_add_ns(expires, PSCHED_TICKS2NS(sched));
			if (hrtimer_try_to_cancel(&q->delay_timer) &&
			    ktime_to_ns(ktime_sub(
					hrtimer_get_expires(&q->delay_timer),
					expires)) > 0)
				hrtimer_set_expires(&q->delay_timer, expires);
			hrtimer_restart(&q->delay_timer);
			cl->delayed = 1;
			cl->xstats.overactions++;
			return;
		}
		delay = 1;
	}
	if (q->wd_expires == 0 || q->wd_expires > delay)
		q->wd_expires = delay;
}