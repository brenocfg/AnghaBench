#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct timespec {long tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_4__ {long tv_nsec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long NSEC_PER_SEC ; 
 int do_gettimeoffset () ; 
 int /*<<< orphan*/  ntp_clear () ; 
 int /*<<< orphan*/  set_normalized_timespec (TYPE_1__*,scalar_t__,long) ; 
 TYPE_1__ wall_to_monotonic ; 
 TYPE_1__ xtime ; 

__attribute__((used)) static int sbus_do_settimeofday(struct timespec *tv)
{
	time_t wtm_sec, sec = tv->tv_sec;
	long wtm_nsec, nsec = tv->tv_nsec;

	if ((unsigned long)tv->tv_nsec >= NSEC_PER_SEC)
		return -EINVAL;

	/*
	 * This is revolting. We need to set "xtime" correctly. However, the
	 * value in this location is the value at the most recent update of
	 * wall time.  Discover what correction gettimeofday() would have
	 * made, and then undo it!
	 */
	nsec -= 1000 * do_gettimeoffset();

	wtm_sec  = wall_to_monotonic.tv_sec + (xtime.tv_sec - sec);
	wtm_nsec = wall_to_monotonic.tv_nsec + (xtime.tv_nsec - nsec);

	set_normalized_timespec(&xtime, sec, nsec);
	set_normalized_timespec(&wall_to_monotonic, wtm_sec, wtm_nsec);

	ntp_clear();
	return 0;
}