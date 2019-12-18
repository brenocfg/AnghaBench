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
struct qdisc_watchdog {int /*<<< orphan*/  timer; TYPE_2__* qdisc; } ;
typedef  int /*<<< orphan*/  psched_time_t ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 int /*<<< orphan*/  PSCHED_TICKS2NS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCQ_F_THROTTLED ; 
 int /*<<< orphan*/  __QDISC_STATE_DEACTIVATED ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* qdisc_root_sleeping (TYPE_2__*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qdisc_watchdog_schedule(struct qdisc_watchdog *wd, psched_time_t expires)
{
	ktime_t time;

	if (test_bit(__QDISC_STATE_DEACTIVATED,
		     &qdisc_root_sleeping(wd->qdisc)->state))
		return;

	wd->qdisc->flags |= TCQ_F_THROTTLED;
	time = ktime_set(0, 0);
	time = ktime_add_ns(time, PSCHED_TICKS2NS(expires));
	hrtimer_start(&wd->timer, time, HRTIMER_MODE_ABS);
}