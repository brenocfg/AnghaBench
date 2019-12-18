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
typedef  unsigned long long uint64_t ;
typedef  int /*<<< orphan*/  pal_rtc_nanotime_t ;

/* Variables and functions */
 int /*<<< orphan*/  _rtc_nanotime_adjust (unsigned long long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  pal_rtc_nanotime_info ; 
 int /*<<< orphan*/  rtc_nanotime_set_commpage (int /*<<< orphan*/ *) ; 

void
rtc_clock_adjust(uint64_t tsc_base_delta)
{
    pal_rtc_nanotime_t	*rntp = &pal_rtc_nanotime_info;

    assert(!ml_get_interrupts_enabled());
    assert(tsc_base_delta < 100ULL);	/* i.e. it's small */
    _rtc_nanotime_adjust(tsc_base_delta, rntp);
    rtc_nanotime_set_commpage(rntp);
}