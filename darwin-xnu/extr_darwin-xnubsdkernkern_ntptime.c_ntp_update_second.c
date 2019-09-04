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
typedef  scalar_t__ l_fp ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ clock_sec_t ;

/* Variables and functions */
 int /*<<< orphan*/  L_ADD (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  L_LINT (scalar_t__,int) ; 
 int /*<<< orphan*/  L_RSHIFT (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  L_SUB (scalar_t__,scalar_t__) ; 
 int MAXFREQ ; 
 int /*<<< orphan*/  NTP_ASSERT_LOCKED () ; 
 scalar_t__ SHIFT_PLL ; 
 scalar_t__ last_time_maxerror_update ; 
 int time_adjtime ; 
 scalar_t__ time_constant ; 
 scalar_t__ time_freq ; 
 int time_maxerror ; 
 scalar_t__ time_offset ; 
 int updated ; 

void
ntp_update_second(int64_t *adjustment, clock_sec_t secs)
{
	int tickrate;
	l_fp time_adj;
	l_fp ftemp, old_time_adjtime, old_offset;

	NTP_ASSERT_LOCKED();

	if (secs > last_time_maxerror_update) {
		time_maxerror += (MAXFREQ / 1000)*(secs-last_time_maxerror_update);
		last_time_maxerror_update = secs;
	}

	old_offset = time_offset;
	old_time_adjtime = time_adjtime;

	ftemp = time_offset;
	L_RSHIFT(ftemp, SHIFT_PLL + time_constant);
	time_adj = ftemp;
	L_SUB(time_offset, ftemp);
	L_ADD(time_adj, time_freq);

	/*
	 * Apply any correction from adjtime.  If more than one second
	 * off we slew at a rate of 5ms/s (5000 PPM) else 500us/s (500PPM)
	 * until the last second is slewed the final < 500 usecs.
	 */
	if (time_adjtime != 0) {
		if (time_adjtime > 1000000)
			tickrate = 5000;
		else if (time_adjtime < -1000000)
			tickrate = -5000;
		else if (time_adjtime > 500)
			tickrate = 500;
		else if (time_adjtime < -500)
			tickrate = -500;
		else
			tickrate = time_adjtime;
		time_adjtime -= tickrate;
		L_LINT(ftemp, tickrate * 1000);
		L_ADD(time_adj, ftemp);
	}

	if (old_time_adjtime || ((time_offset || old_offset) && (time_offset != old_offset))) {
		updated = 1;
	}
	else{
		updated = 0;
	}

#if DEVELOPEMNT || DEBUG
	if (g_should_log_clock_adjustments) {
		int64_t nano = (time_adj > 0)? time_adj >> 32 : -((-time_adj) >> 32); 
		int64_t frac = (time_adj > 0)? ((uint32_t) time_adj) : -((uint32_t) (-time_adj)); 

		os_log(OS_LOG_DEFAULT, "%s:AFTER offset %lld (%lld) freq %lld status %d "
		       "constant %ld time_adjtime %lld nano %lld frac %lld adj %lld\n",
		       __func__, time_offset, (time_offset > 0)? time_offset >> 32 : -((-time_offset) >> 32),
		       time_freq, time_status, time_constant, time_adjtime, nano, frac, time_adj);
	}
#endif

	*adjustment = time_adj;
}