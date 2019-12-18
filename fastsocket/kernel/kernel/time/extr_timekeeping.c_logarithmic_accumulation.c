#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int cycle_t ;
struct TYPE_9__ {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_8__ {int tv_sec; } ;
struct TYPE_7__ {scalar_t__ tv_sec; } ;
struct TYPE_10__ {scalar_t__ shift; int cycle_interval; scalar_t__ xtime_nsec; int xtime_interval; int raw_interval; int ntp_error; int xtime_remainder; int ntp_error_shift; TYPE_4__ raw_time; TYPE_3__ wall_to_monotonic; TYPE_2__ xtime; TYPE_1__* clock; } ;
struct TYPE_6__ {int cycle_last; } ;

/* Variables and functions */
 scalar_t__ NSEC_PER_SEC ; 
 int /*<<< orphan*/  clock_was_set_delayed () ; 
 scalar_t__ do_div (scalar_t__,scalar_t__) ; 
 int ntp_tick_length () ; 
 int second_overflow (scalar_t__) ; 
 TYPE_5__ timekeeper ; 

__attribute__((used)) static cycle_t logarithmic_accumulation(cycle_t offset, int shift)
{
	u64 nsecps = (u64)NSEC_PER_SEC << timekeeper.shift;
	u64 raw_nsecs;

	/* If the offset is smaller than a shifted interval, do nothing */
	if (offset < timekeeper.cycle_interval<<shift)
		return offset;

	/* Accumulate one shifted interval */
	offset -= timekeeper.cycle_interval << shift;
	timekeeper.clock->cycle_last += timekeeper.cycle_interval << shift;

	timekeeper.xtime_nsec += timekeeper.xtime_interval << shift;
	while (timekeeper.xtime_nsec >= nsecps) {
		int leap;
		timekeeper.xtime_nsec -= nsecps;
		timekeeper.xtime.tv_sec++;
		leap = second_overflow(timekeeper.xtime.tv_sec);
		timekeeper.xtime.tv_sec += leap;
		timekeeper.wall_to_monotonic.tv_sec -= leap;
		if (leap)
			clock_was_set_delayed();
	}

	/* Accumulate raw time */
	raw_nsecs = timekeeper.raw_interval << shift;
	raw_nsecs += timekeeper.raw_time.tv_nsec;
	if (raw_nsecs >= NSEC_PER_SEC) {
		u64 raw_secs = raw_nsecs;
		raw_nsecs = do_div(raw_secs, NSEC_PER_SEC);
		timekeeper.raw_time.tv_sec += raw_secs;
	}
	timekeeper.raw_time.tv_nsec = raw_nsecs;

	/* Accumulate error between NTP and clock interval */
	timekeeper.ntp_error += ntp_tick_length() << shift;
	timekeeper.ntp_error -=
	    (timekeeper.xtime_interval + timekeeper.xtime_remainder) <<
				(timekeeper.ntp_error_shift + shift);

	return offset;
}