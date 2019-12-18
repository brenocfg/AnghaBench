#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint64_t ;
struct kevent_internal_s {int fflags; scalar_t__ data; scalar_t__* ext; } ;
struct filt_timer_params {int leeway; int deadline; int interval; } ;
typedef  scalar_t__ clock_sec_t ;
typedef  int clock_nsec_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 scalar_t__ FALSE ; 
 int NOTE_ABSOLUTE ; 
 int NOTE_LEEWAY ; 
#define  NOTE_MACHTIME 131 
 int NOTE_MACH_CONTINUOUS_TIME ; 
#define  NOTE_NSECONDS 130 
#define  NOTE_SECONDS 129 
#define  NOTE_USECONDS 128 
 int NSEC_PER_SEC ; 
 int NSEC_PER_USEC ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  clock_absolutetime_interval_to_deadline (int,int*) ; 
 int /*<<< orphan*/  clock_continuoustime_interval_to_deadline (int,int*) ; 
 int /*<<< orphan*/  clock_get_calendar_nanotime (scalar_t__*,int*) ; 
 int /*<<< orphan*/  nanoseconds_to_absolutetime (int,int*) ; 
 scalar_t__ os_mul_overflow (int,int,int*) ; 

__attribute__((used)) static int
filt_timervalidate(const struct kevent_internal_s *kev,
		struct filt_timer_params *params)
{
	/*
	 * There are 5 knobs that need to be chosen for a timer registration:
	 *
	 * A) Units of time (what is the time duration of the specified number)
	 *      Absolute and interval take:
	 *              NOTE_SECONDS, NOTE_USECONDS, NOTE_NSECONDS, NOTE_MACHTIME
	 *      Defaults to milliseconds if not specified
	 *
	 * B) Clock epoch (what is the zero point of the specified number)
	 *      For interval, there is none
	 *      For absolute, defaults to the gettimeofday/calendar epoch
	 *      With NOTE_MACHTIME, uses mach_absolute_time()
	 *      With NOTE_MACHTIME and NOTE_MACH_CONTINUOUS_TIME, uses mach_continuous_time()
	 *
	 * C) The knote's behavior on delivery
	 *      Interval timer causes the knote to arm for the next interval unless one-shot is set
	 *      Absolute is a forced one-shot timer which deletes on delivery
	 *      TODO: Add a way for absolute to be not forced one-shot
	 *
	 * D) Whether the time duration is relative to now or absolute
	 *      Interval fires at now + duration when it is set up
	 *      Absolute fires at now + difference between now walltime and passed in walltime
	 *      With NOTE_MACHTIME it fires at an absolute MAT or MCT.
	 *
	 * E) Whether the timer continues to tick across sleep
	 *      By default all three do not.
	 *      For interval and absolute, NOTE_MACH_CONTINUOUS_TIME causes them to tick across sleep
	 *      With NOTE_ABSOLUTE | NOTE_MACHTIME | NOTE_MACH_CONTINUOUS_TIME:
	 *              expires when mach_continuous_time() is > the passed in value.
	 */

	uint64_t multiplier;

	boolean_t use_abstime = FALSE;

	switch (kev->fflags & (NOTE_SECONDS|NOTE_USECONDS|NOTE_NSECONDS|NOTE_MACHTIME)) {
	case NOTE_SECONDS:
		multiplier = NSEC_PER_SEC;
		break;
	case NOTE_USECONDS:
		multiplier = NSEC_PER_USEC;
		break;
	case NOTE_NSECONDS:
		multiplier = 1;
		break;
	case NOTE_MACHTIME:
		multiplier = 0;
		use_abstime = TRUE;
		break;
	case 0: /* milliseconds (default) */
		multiplier = NSEC_PER_SEC / 1000;
		break;
	default:
		return (EINVAL);
	}

	/* transform the leeway in kn_ext[1] to same time scale */
	if (kev->fflags & NOTE_LEEWAY) {
		uint64_t leeway_abs;

		if (use_abstime) {
			leeway_abs = (uint64_t)kev->ext[1];
		} else  {
			uint64_t leeway_ns;
			if (os_mul_overflow((uint64_t)kev->ext[1], multiplier, &leeway_ns))
				return (ERANGE);

			nanoseconds_to_absolutetime(leeway_ns, &leeway_abs);
		}

		params->leeway = leeway_abs;
	} else {
		params->leeway = 0;
	}

	if (kev->fflags & NOTE_ABSOLUTE) {
		uint64_t deadline_abs;

		if (use_abstime) {
			deadline_abs = (uint64_t)kev->data;
		} else {
			uint64_t calendar_deadline_ns;

			if (os_mul_overflow((uint64_t)kev->data, multiplier, &calendar_deadline_ns))
				return (ERANGE);

			/* calendar_deadline_ns is in nanoseconds since the epoch */

			clock_sec_t seconds;
			clock_nsec_t nanoseconds;

			/*
			 * Note that the conversion through wall-time is only done once.
			 *
			 * If the relationship between MAT and gettimeofday changes,
			 * the underlying timer does not update.
			 *
			 * TODO: build a wall-time denominated timer_call queue
			 * and a flag to request DTRTing with wall-time timers
			 */
			clock_get_calendar_nanotime(&seconds, &nanoseconds);

			uint64_t calendar_now_ns = (uint64_t)seconds * NSEC_PER_SEC + nanoseconds;

			/* if deadline is in the future */
			if (calendar_now_ns < calendar_deadline_ns) {
				uint64_t interval_ns = calendar_deadline_ns - calendar_now_ns;
				uint64_t interval_abs;

				nanoseconds_to_absolutetime(interval_ns, &interval_abs);

				/*
				 * Note that the NOTE_MACH_CONTINUOUS_TIME flag here only
				 * causes the timer to keep ticking across sleep, but
				 * it does not change the calendar timebase.
				 */

				if (kev->fflags & NOTE_MACH_CONTINUOUS_TIME)
					clock_continuoustime_interval_to_deadline(interval_abs,
					                                          &deadline_abs);
				else
					clock_absolutetime_interval_to_deadline(interval_abs,
					                                        &deadline_abs);
			} else {
				deadline_abs = 0; /* cause immediate expiration */
			}
		}

		params->deadline = deadline_abs;
		params->interval = 0; /* NOTE_ABSOLUTE is non-repeating */
	} else if (kev->data < 0) {
		/*
		 * Negative interval timers fire immediately, once.
		 *
		 * Ideally a negative interval would be an error, but certain clients
		 * pass negative values on accident, and expect an event back.
		 *
		 * In the old implementation the timer would repeat with no delay
		 * N times until mach_absolute_time() + (N * interval) underflowed,
		 * then it would wait ~forever by accidentally arming a timer for the far future.
		 *
		 * We now skip the power-wasting hot spin phase and go straight to the idle phase.
		 */

		params->deadline = 0; /* expire immediately */
		params->interval = 0; /* non-repeating */
	} else {
		uint64_t interval_abs = 0;

		if (use_abstime) {
			interval_abs = (uint64_t)kev->data;
		} else {
			uint64_t interval_ns;
			if (os_mul_overflow((uint64_t)kev->data, multiplier, &interval_ns))
				return (ERANGE);

			nanoseconds_to_absolutetime(interval_ns, &interval_abs);
		}

		uint64_t deadline = 0;

		if (kev->fflags & NOTE_MACH_CONTINUOUS_TIME)
			clock_continuoustime_interval_to_deadline(interval_abs, &deadline);
		else
			clock_absolutetime_interval_to_deadline(interval_abs, &deadline);

		params->deadline = deadline;
		params->interval = interval_abs;
	}

	return (0);
}