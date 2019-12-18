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
 unsigned int RTC_CMD_WRITE ; 
 int RTC_IODATA ; 
 int RTC_RESET ; 
 int RTC_SCLK ; 
 int /*<<< orphan*/  ds1302_sendbits (unsigned int) ; 
 int get_dp () ; 
 int /*<<< orphan*/  set_dp (int) ; 

__attribute__((used)) static void ds1302_writebyte(unsigned int addr, unsigned int val)
{
	set_dp(get_dp() & ~(RTC_RESET | RTC_IODATA | RTC_SCLK));
	set_dp(get_dp() | RTC_RESET);
	ds1302_sendbits(((addr & 0x3f) << 1) | RTC_CMD_WRITE);
	ds1302_sendbits(val);
	set_dp(get_dp() & ~RTC_RESET);
}