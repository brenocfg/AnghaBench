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

/* Variables and functions */
 int RTC_IODATA ; 
 int RTC_SCLK ; 
 int get_dp () ; 
 int /*<<< orphan*/  set_dp (int) ; 

__attribute__((used)) static void ds1302_sendbits(unsigned int val)
{
	int i;

	for (i = 8; (i); i--, val >>= 1) {
		set_dp((get_dp() & ~RTC_IODATA) | ((val & 0x1) ?
			RTC_IODATA : 0));
		set_dp(get_dp() | RTC_SCLK);	/* clock high */
		set_dp(get_dp() & ~RTC_SCLK);	/* clock low */
	}
}