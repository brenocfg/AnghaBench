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
typedef  int /*<<< orphan*/  spl_t ;

/* Variables and functions */
 int /*<<< orphan*/  pal_rtc_nanotime_info ; 
 int /*<<< orphan*/  rtc_nanotime_set_commpage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  splclock () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 

void
rtc_nanotime_init_commpage(void)
{
	spl_t			s = splclock();

	rtc_nanotime_set_commpage(&pal_rtc_nanotime_info);
	splx(s);
}