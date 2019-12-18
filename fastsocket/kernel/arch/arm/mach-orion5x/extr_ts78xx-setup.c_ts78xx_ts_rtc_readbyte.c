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
 int /*<<< orphan*/  TS_RTC_CTRL ; 
 int /*<<< orphan*/  TS_RTC_DATA ; 
 unsigned char readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char ts78xx_ts_rtc_readbyte(unsigned long addr)
{
	writeb(addr, TS_RTC_CTRL);
	return readb(TS_RTC_DATA);
}