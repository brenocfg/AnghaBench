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
struct TYPE_2__ {int tv_nsec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 scalar_t__ next_rtc_update ; 
 int /*<<< orphan*/  ntp_synced () ; 
 scalar_t__ set_rtc () ; 
 scalar_t__ tick_nsec ; 
 scalar_t__ time_before (unsigned long,scalar_t__) ; 
 TYPE_1__ xtime ; 

__attribute__((used)) static inline void do_set_rtc(void)
{
	if (!ntp_synced() || set_rtc == NULL)
		return;

	if (next_rtc_update &&
	    time_before((unsigned long)xtime.tv_sec, next_rtc_update))
		return;

	if (xtime.tv_nsec < 500000000 - ((unsigned) tick_nsec >> 1) &&
	    xtime.tv_nsec >= 500000000 + ((unsigned) tick_nsec >> 1))
		return;

	if (set_rtc())
		/*
		 * rtc update failed.  Try again in 60s
		 */
		next_rtc_update = xtime.tv_sec + 60;
	else
		next_rtc_update = xtime.tv_sec + 660;
}