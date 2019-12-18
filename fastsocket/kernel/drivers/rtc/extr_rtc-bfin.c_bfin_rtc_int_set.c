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
typedef  int u16 ;

/* Variables and functions */
 int bfin_read_RTC_ICTL () ; 
 int /*<<< orphan*/  bfin_write_RTC_ICTL (int) ; 
 int /*<<< orphan*/  bfin_write_RTC_ISTAT (int) ; 

__attribute__((used)) static void bfin_rtc_int_set(u16 rtc_int)
{
	bfin_write_RTC_ISTAT(rtc_int);
	bfin_write_RTC_ICTL(bfin_read_RTC_ICTL() | rtc_int);
}