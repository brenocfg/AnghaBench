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
struct TYPE_2__ {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_cmos_time () ; 
 scalar_t__ have_rtc ; 
 TYPE_1__ xtime ; 

void
update_xtime_from_cmos(void)
{
	if(have_rtc) {
		xtime.tv_sec = get_cmos_time();
		xtime.tv_nsec = 0;
	}
}