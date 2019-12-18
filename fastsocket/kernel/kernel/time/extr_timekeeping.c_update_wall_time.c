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
struct clocksource {int (* read ) (struct clocksource*) ;int cycle_last; int mask; } ;
typedef  scalar_t__ s64 ;
typedef  int cycle_t ;
struct TYPE_5__ {int tv_sec; } ;
struct TYPE_4__ {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_6__ {int cycle_interval; scalar_t__ xtime_nsec; scalar_t__ shift; scalar_t__ ntp_error; scalar_t__ ntp_error_shift; int /*<<< orphan*/  lock; TYPE_2__ wall_to_monotonic; TYPE_1__ xtime; struct clocksource* clock; } ;

/* Variables and functions */
 scalar_t__ NSEC_PER_SEC ; 
 int /*<<< orphan*/  clock_was_set_delayed () ; 
 int ilog2 (int) ; 
 int logarithmic_accumulation (int,int) ; 
 int max (int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int ntp_tick_length () ; 
 int second_overflow (scalar_t__) ; 
 int stub1 (struct clocksource*) ; 
 TYPE_3__ timekeeper ; 
 int /*<<< orphan*/  timekeeping_adjust (int) ; 
 int timekeeping_suspended ; 
 int /*<<< orphan*/  timekeeping_update (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  write_seqlock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_sequnlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void update_wall_time(void)
{
	struct clocksource *clock;
	cycle_t offset;
	int shift = 0, maxshift;
	unsigned long flags;

	write_seqlock_irqsave(&timekeeper.lock, flags);

	/* Make sure we're fully resumed: */
	if (unlikely(timekeeping_suspended))
		goto out;

	clock = timekeeper.clock;

#ifdef CONFIG_ARCH_USES_GETTIMEOFFSET
	offset = timekeeper.cycle_interval;
#else
	offset = (clock->read(clock) - clock->cycle_last) & clock->mask;
#endif
	timekeeper.xtime_nsec = (s64)timekeeper.xtime.tv_nsec <<
						timekeeper.shift;

	/*
	 * With NO_HZ we may have to accumulate many cycle_intervals
	 * (think "ticks") worth of time at once. To do this efficiently,
	 * we calculate the largest doubling multiple of cycle_intervals
	 * that is smaller than the offset.  We then accumulate that
	 * chunk in one go, and then try to consume the next smaller
	 * doubled multiple.
	 */
	shift = ilog2(offset) - ilog2(timekeeper.cycle_interval);
	shift = max(0, shift);
	/* Bound shift to one less than what overflows tick_length */
	maxshift = (64 - (ilog2(ntp_tick_length())+1)) - 1;
	shift = min(shift, maxshift);
	while (offset >= timekeeper.cycle_interval) {
		offset = logarithmic_accumulation(offset, shift);
		if(offset < timekeeper.cycle_interval<<shift)
			shift--;
	}

	/* correct the clock when NTP error is too big */
	timekeeping_adjust(offset);

	/*
	 * Since in the loop above, we accumulate any amount of time
	 * in xtime_nsec over a second into xtime.tv_sec, its possible for
	 * xtime_nsec to be fairly small after the loop. Further, if we're
	 * slightly speeding the clocksource up in timekeeping_adjust(),
	 * its possible the required corrective factor to xtime_nsec could
	 * cause it to underflow.
	 *
	 * Now, we cannot simply roll the accumulated second back, since
	 * the NTP subsystem has been notified via second_overflow. So
	 * instead we push xtime_nsec forward by the amount we underflowed,
	 * and add that amount into the error.
	 *
	 * We'll correct this error next time through this function, when
	 * xtime_nsec is not as small.
	 */
	if (unlikely((s64)timekeeper.xtime_nsec < 0)) {
		s64 neg = -(s64)timekeeper.xtime_nsec;
		timekeeper.xtime_nsec = 0;
		timekeeper.ntp_error += neg << timekeeper.ntp_error_shift;
	}


	/*
	 * Store full nanoseconds into xtime after rounding it up and
	 * add the remainder to the error difference.
	 */
	timekeeper.xtime.tv_nsec = ((s64)timekeeper.xtime_nsec >>
						timekeeper.shift) + 1;
	timekeeper.xtime_nsec -= (s64)timekeeper.xtime.tv_nsec <<
						timekeeper.shift;
	timekeeper.ntp_error +=	timekeeper.xtime_nsec <<
				timekeeper.ntp_error_shift;

	/*
	 * Finally, make sure that after the rounding
	 * xtime.tv_nsec isn't larger than NSEC_PER_SEC
	 */
	if (unlikely(timekeeper.xtime.tv_nsec >= NSEC_PER_SEC)) {
		int leap;
		timekeeper.xtime.tv_nsec -= NSEC_PER_SEC;
		timekeeper.xtime.tv_sec++;
		leap = second_overflow(timekeeper.xtime.tv_sec);
		timekeeper.xtime.tv_sec += leap;
		timekeeper.wall_to_monotonic.tv_sec -= leap;
		if (leap)
			clock_was_set_delayed();
	}

	timekeeping_update(false);

out:
	write_sequnlock_irqrestore(&timekeeper.lock, flags);

}