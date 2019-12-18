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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* rtc_config ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  rtc_nanotime_init (int /*<<< orphan*/ ) ; 
 TYPE_1__* rtc_timer ; 
 int /*<<< orphan*/  stub1 () ; 

void
rtc_sleep_wakeup(
	uint64_t		base)
{
    	/* Set fixed configuration for lapic timers */
	rtc_timer->rtc_config();

	/*
	 * Reset nanotime.
	 * The timestamp counter will have been reset
	 * but nanotime (uptime) marches onward.
	 */
	rtc_nanotime_init(base);
}