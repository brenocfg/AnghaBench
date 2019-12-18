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
struct timespec {int dummy; } ;
struct sys_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* read ) (TYPE_2__*) ;int /*<<< orphan*/  cycle_last; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; scalar_t__ ntp_error; TYPE_2__* clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_EVT_NOTIFY_RESUME ; 
 int /*<<< orphan*/  __timekeeping_inject_sleeptime (struct timespec*) ; 
 int /*<<< orphan*/  clockevents_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clocksource_resume () ; 
 int /*<<< orphan*/  hrtimers_resume () ; 
 int /*<<< orphan*/  read_persistent_clock (struct timespec*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 TYPE_1__ timekeeper ; 
 int /*<<< orphan*/  timekeeping_suspend_time ; 
 scalar_t__ timekeeping_suspended ; 
 int /*<<< orphan*/  timekeeping_update (int) ; 
 scalar_t__ timespec_compare (struct timespec*,int /*<<< orphan*/ *) ; 
 struct timespec timespec_sub (struct timespec,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touch_softlockup_watchdog () ; 
 int /*<<< orphan*/  write_seqlock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_sequnlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int timekeeping_resume(struct sys_device *dev)
{
	unsigned long flags;
	struct timespec ts;

	read_persistent_clock(&ts);

	clocksource_resume();

	write_seqlock_irqsave(&timekeeper.lock, flags);

	if (timespec_compare(&ts, &timekeeping_suspend_time) > 0) {
		ts = timespec_sub(ts, timekeeping_suspend_time);
		__timekeeping_inject_sleeptime(&ts);
	}
	/* re-base the last cycle value */
	timekeeper.clock->cycle_last = timekeeper.clock->read(timekeeper.clock);
	timekeeper.ntp_error = 0;
	timekeeping_suspended = 0;
	timekeeping_update(false);
	write_sequnlock_irqrestore(&timekeeper.lock, flags);

	touch_softlockup_watchdog();

	clockevents_notify(CLOCK_EVT_NOTIFY_RESUME, NULL);

	/* Resume hrtimers */
	hrtimers_resume();

	return 0;
}