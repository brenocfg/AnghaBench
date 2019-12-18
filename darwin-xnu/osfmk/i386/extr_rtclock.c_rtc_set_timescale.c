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
typedef  int uint64_t ;
typedef  void* uint32_t ;
struct TYPE_4__ {void* shift; void* scale; } ;
typedef  TYPE_1__ pal_rtc_nanotime_t ;

/* Variables and functions */
 scalar_t__ NSEC_PER_SEC ; 
 int SLOW_TSC_THRESHOLD ; 
 scalar_t__ _rtc_tsc_to_nanoseconds (scalar_t__,TYPE_1__*) ; 
 TYPE_1__ pal_rtc_nanotime_info ; 
 scalar_t__ rdtsc64 () ; 
 int /*<<< orphan*/  rtc_nanotime_init (int /*<<< orphan*/ ) ; 
 scalar_t__ tsc_at_boot ; 
 scalar_t__ tsc_rebase_abs_time ; 

__attribute__((used)) static void
rtc_set_timescale(uint64_t cycles)
{
	pal_rtc_nanotime_t	*rntp = &pal_rtc_nanotime_info;
	uint32_t    shift = 0;
    
	/* the "scale" factor will overflow unless cycles>SLOW_TSC_THRESHOLD */
    
	while ( cycles <= SLOW_TSC_THRESHOLD) {
		shift++;
		cycles <<= 1;
	}
	
	rntp->scale = (uint32_t)(((uint64_t)NSEC_PER_SEC << 32) / cycles);

	rntp->shift = shift;

	/*
	 * On some platforms, the TSC is not reset at warm boot. But the
	 * rebase time must be relative to the current boot so we can't use
	 * mach_absolute_time(). Instead, we convert the TSC delta since boot
	 * to nanoseconds.
	 */
	if (tsc_rebase_abs_time == 0)
		tsc_rebase_abs_time = _rtc_tsc_to_nanoseconds(
						rdtsc64() - tsc_at_boot, rntp);

	rtc_nanotime_init(0);
}