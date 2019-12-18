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
typedef  void* uint64_t ;
struct TYPE_2__ {int TimeStamp_tick; void* Ticks_per_sec; void* Ticks_scale; void* TimeStamp_frac; void* TimeStamp_sec; } ;
typedef  TYPE_1__ new_commpage_timeofday_data_t ;

/* Variables and functions */
 scalar_t__ _COMM_PAGE_NEWTIMEOFDAY_DATA ; 
 scalar_t__ _COMM_PAGE_RW_OFFSET ; 
 scalar_t__ commPagePtr ; 

void
commpage_set_timestamp(
	uint64_t	tbr, 
	uint64_t	secs,
	uint64_t	frac,
	uint64_t	scale,
	uint64_t	tick_per_sec)
{
	new_commpage_timeofday_data_t *commpage_timeofday_datap;

	if (commPagePtr == 0)
		return;

	commpage_timeofday_datap =  (new_commpage_timeofday_data_t *)(_COMM_PAGE_NEWTIMEOFDAY_DATA+_COMM_PAGE_RW_OFFSET);

	commpage_timeofday_datap->TimeStamp_tick = 0x0ULL;

#if	(__ARM_ARCH__ >= 7)
	__asm__ volatile("dmb ish");
#endif
	commpage_timeofday_datap->TimeStamp_sec = secs;
	commpage_timeofday_datap->TimeStamp_frac = frac;
	commpage_timeofday_datap->Ticks_scale = scale;
	commpage_timeofday_datap->Ticks_per_sec = tick_per_sec;

#if	(__ARM_ARCH__ >= 7)
	__asm__ volatile("dmb ish");
#endif
	commpage_timeofday_datap->TimeStamp_tick = tbr;
}