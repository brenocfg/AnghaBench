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
struct timespec {int /*<<< orphan*/  tv_sec; } ;
struct sys_device {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct timespec xtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_EVT_NOTIFY_SUSPEND ; 
 int abs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clockevents_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clocksource_suspend () ; 
 int /*<<< orphan*/  read_persistent_clock (struct timespec*) ; 
 TYPE_1__ timekeeper ; 
 int /*<<< orphan*/  timekeeping_forward_now () ; 
 struct timespec timekeeping_suspend_time ; 
 int timekeeping_suspended ; 
 struct timespec timespec_add (struct timespec,struct timespec) ; 
 struct timespec timespec_sub (struct timespec,struct timespec) ; 
 int /*<<< orphan*/  write_seqlock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_sequnlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int timekeeping_suspend(struct sys_device *dev, pm_message_t state)
{
	unsigned long flags;
	struct timespec		delta, delta_delta;
	static struct timespec	old_delta;

	read_persistent_clock(&timekeeping_suspend_time);

	write_seqlock_irqsave(&timekeeper.lock, flags);
	timekeeping_forward_now();
	timekeeping_suspended = 1;

	/*
	 * To avoid drift caused by repeated suspend/resumes,
	 * which each can add ~1 second drift error,
	 * try to compensate so the difference in system time
	 * and persistent_clock time stays close to constant.
	 */
	delta = timespec_sub(timekeeper.xtime, timekeeping_suspend_time);
	delta_delta = timespec_sub(delta, old_delta);
	if (abs(delta_delta.tv_sec)  >= 2) {
		/*
		 * if delta_delta is too large, assume time correction
		 * has occured and set old_delta to the current delta.
		 */
		old_delta = delta;
	} else {
		/* Otherwise try to adjust old_system to compensate */
		timekeeping_suspend_time =
			timespec_add(timekeeping_suspend_time, delta_delta);
	}
	write_sequnlock_irqrestore(&timekeeper.lock, flags);

	clockevents_notify(CLOCK_EVT_NOTIFY_SUSPEND, NULL);
	clocksource_suspend();

	return 0;
}