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
typedef  scalar_t__ volatile uint64_t ;
typedef  scalar_t__ volatile uint32_t ;
struct timeval {scalar_t__ volatile tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_2__ {scalar_t__ TimeStamp_tick; scalar_t__ TimeStamp_sec; scalar_t__ TimeStamp_frac; scalar_t__ Ticks_scale; scalar_t__ Ticks_per_sec; } ;
typedef  TYPE_1__ new_commpage_timeofday_data_t ;
typedef  scalar_t__ volatile __darwin_time_t ;

/* Variables and functions */
 scalar_t__ _COMM_PAGE_NEWTIMEOFDAY_DATA ; 
 scalar_t__ mach_absolute_time () ; 
 scalar_t__ multi_overflow (scalar_t__ volatile,scalar_t__ volatile) ; 

int
__commpage_gettimeofday_internal(struct timeval *tp, uint64_t *tbr_out)
{
	uint64_t now, over;
	uint64_t delta,frac;
	uint64_t TimeStamp_tick;
	uint64_t TimeStamp_sec;
	uint64_t TimeStamp_frac;
	uint64_t Tick_scale;
	uint64_t Ticks_per_sec;

	volatile uint64_t *gtod_TimeStamp_tick_p;
	volatile uint64_t *gtod_TimeStamp_sec_p;
	volatile uint64_t *gtod_TimeStamp_frac_p;
	volatile uint64_t *gtod_Ticks_scale_p;
	volatile uint64_t *gtod_Ticks_per_sec_p;

	new_commpage_timeofday_data_t *commpage_timeofday_datap;

	commpage_timeofday_datap =  (new_commpage_timeofday_data_t *)_COMM_PAGE_NEWTIMEOFDAY_DATA;

	gtod_TimeStamp_tick_p = &commpage_timeofday_datap->TimeStamp_tick;
	gtod_TimeStamp_sec_p = &commpage_timeofday_datap->TimeStamp_sec;
	gtod_TimeStamp_frac_p = &commpage_timeofday_datap->TimeStamp_frac;
	gtod_Ticks_scale_p = &commpage_timeofday_datap->Ticks_scale;
	gtod_Ticks_per_sec_p = &commpage_timeofday_datap->Ticks_per_sec;

	do {
		TimeStamp_tick = *gtod_TimeStamp_tick_p;
		/*
		 * This call contains an instruction barrier which will ensure that the
		 * second read of the abs time isn't speculated above the reads of the
		 * other values above
		 */
		now = mach_absolute_time();
		TimeStamp_sec = *gtod_TimeStamp_sec_p;
		TimeStamp_frac = *gtod_TimeStamp_frac_p;
		Tick_scale = *gtod_Ticks_scale_p;
		Ticks_per_sec = *gtod_Ticks_per_sec_p;
		/*
		 * This barrier prevents the reordering of the second read of gtod_TimeStamp_tick_p
		 * w.r.t the values read just after mach_absolute_time is invoked.
		 */
#if	(__ARM_ARCH__ >= 7)
		__asm__ volatile("dmb ishld" ::: "memory");
#endif
	} while (TimeStamp_tick != *gtod_TimeStamp_tick_p);

	if (TimeStamp_tick == 0)
		return(1);

	delta = now - TimeStamp_tick;

	/* If more than one second force a syscall */
	if (delta >= Ticks_per_sec)
		return(1);

	if (TimeStamp_sec > __LONG_MAX__) {
		return(1);
	}

	tp->tv_sec = (__darwin_time_t)TimeStamp_sec;

	over = multi_overflow(Tick_scale, delta);
	if(over){
		tp->tv_sec += over;
	}

	/* Sum scale*delta to TimeStamp_frac, if it overflows increment sec */
	frac = TimeStamp_frac;
	frac += Tick_scale * delta;
	if( TimeStamp_frac > frac )
		tp->tv_sec++;

	/*
	 * Convert frac (64 bit frac of a sec) to usec
	 * usec = frac * USEC_PER_SEC / 2^64
	 */
	tp->tv_usec = ((uint64_t)1000000 * (uint32_t)(frac >> 32)) >> 32;

	if (tbr_out) {
		*tbr_out = now;
	}

	return(0);
}