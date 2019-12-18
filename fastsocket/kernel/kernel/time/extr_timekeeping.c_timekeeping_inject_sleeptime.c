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
struct timespec {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __timekeeping_inject_sleeptime (struct timespec*) ; 
 int /*<<< orphan*/  clock_was_set () ; 
 int /*<<< orphan*/  read_persistent_clock (struct timespec*) ; 
 TYPE_1__ timekeeper ; 
 int /*<<< orphan*/  timekeeping_forward_now () ; 
 int /*<<< orphan*/  timekeeping_update (int) ; 
 int /*<<< orphan*/  write_seqlock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_sequnlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void timekeeping_inject_sleeptime(struct timespec *delta)
{
	unsigned long flags;
	struct timespec ts;

	/* Make sure we don't set the clock twice */
	read_persistent_clock(&ts);
	if (!(ts.tv_sec == 0 && ts.tv_nsec == 0))
		return;

	write_seqlock_irqsave(&timekeeper.lock, flags);

	timekeeping_forward_now();

	__timekeeping_inject_sleeptime(delta);

	timekeeping_update(true);

	write_sequnlock_irqrestore(&timekeeper.lock, flags);

	/* signal hrtimers about time change */
	clock_was_set();
}