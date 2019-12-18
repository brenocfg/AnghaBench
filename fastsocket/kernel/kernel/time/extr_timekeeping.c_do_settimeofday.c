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
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct timespec xtime; int /*<<< orphan*/  wall_to_monotonic; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  clock_was_set () ; 
 TYPE_1__ timekeeper ; 
 int /*<<< orphan*/  timekeeping_forward_now () ; 
 int /*<<< orphan*/  timekeeping_update (int) ; 
 int /*<<< orphan*/  timespec_sub (int /*<<< orphan*/ ,struct timespec) ; 
 int /*<<< orphan*/  timespec_valid_strict (struct timespec const*) ; 
 int /*<<< orphan*/  write_seqlock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_sequnlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int do_settimeofday(const struct timespec *tv)
{
	struct timespec ts_delta;
	unsigned long flags;

	if (!timespec_valid_strict(tv))
		return -EINVAL;

	write_seqlock_irqsave(&timekeeper.lock, flags);

	timekeeping_forward_now();

	ts_delta.tv_sec = tv->tv_sec - timekeeper.xtime.tv_sec;
	ts_delta.tv_nsec = tv->tv_nsec - timekeeper.xtime.tv_nsec;
	timekeeper.wall_to_monotonic =
			timespec_sub(timekeeper.wall_to_monotonic, ts_delta);

	timekeeper.xtime = *tv;
	timekeeping_update(true);

	write_sequnlock_irqrestore(&timekeeper.lock, flags);

	/* signal hrtimers about time change */
	clock_was_set();

	return 0;
}