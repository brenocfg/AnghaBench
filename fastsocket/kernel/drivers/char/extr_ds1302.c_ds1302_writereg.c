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
 int /*<<< orphan*/  ds1302_wdisable () ; 
 int /*<<< orphan*/  ds1302_wenable () ; 
 int /*<<< orphan*/  out_byte_rtc (int,unsigned char) ; 

void
ds1302_writereg(int reg, unsigned char val)
{
	ds1302_wenable();
	out_byte_rtc((0x80 | (reg << 1)),val);
	ds1302_wdisable();
}