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
 int RTC_TRICKLECHARGER ; 
 int /*<<< orphan*/  ds1302_wdisable () ; 
 int /*<<< orphan*/  ds1302_wenable () ; 
 int /*<<< orphan*/  out_byte (unsigned char) ; 
 int /*<<< orphan*/  start () ; 
 int /*<<< orphan*/  stop () ; 

void
ds1302_writereg(int reg, unsigned char val) 
{
#ifndef CONFIG_ETRAX_RTC_READONLY
	int do_writereg = 1;
#else
	int do_writereg = 0;

	if (reg == RTC_TRICKLECHARGER)
		do_writereg = 1;
#endif

	if (do_writereg) {
		ds1302_wenable();
		start();
		out_byte(0x80 | (reg << 1)); /* write register */
		out_byte(val);
		stop();
		ds1302_wdisable();
	}
}