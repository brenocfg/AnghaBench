#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {scalar_t__ ns_base; scalar_t__ tsc_base; int /*<<< orphan*/  shift; int /*<<< orphan*/  scale; } ;
typedef  TYPE_1__ pal_rtc_nanotime_t ;

/* Variables and functions */
 int /*<<< orphan*/  _pal_rtc_nanotime_store (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ _rtc_tsc_to_nanoseconds (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ml_get_interrupts_enabled () ; 
 TYPE_1__ pal_rtc_nanotime_info ; 
 scalar_t__ rdtsc64 () ; 
 int /*<<< orphan*/  rtc_nanotime_set_commpage (TYPE_1__*) ; 

void
rtc_clock_napped(uint64_t base, uint64_t tsc_base)
{
	pal_rtc_nanotime_t	*rntp = &pal_rtc_nanotime_info;
	uint64_t	oldnsecs;
	uint64_t	newnsecs;
	uint64_t	tsc;

	assert(!ml_get_interrupts_enabled());
	tsc = rdtsc64();
	oldnsecs = rntp->ns_base + _rtc_tsc_to_nanoseconds(tsc - rntp->tsc_base, rntp);
	newnsecs = base + _rtc_tsc_to_nanoseconds(tsc - tsc_base, rntp);
	
	/*
	 * Only update the base values if time using the new base values
	 * is later than the time using the old base values.
	 */
	if (oldnsecs < newnsecs) {
	    _pal_rtc_nanotime_store(tsc_base, base, rntp->scale, rntp->shift, rntp);
	    rtc_nanotime_set_commpage(rntp);
	}
}