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
#define  RTC_CLOCKOUT_FREQ 137 
#define  RTC_CONTROL1 136 
#define  RTC_CONTROL2 135 
#define  RTC_DAY_OF_MONTH 134 
#define  RTC_HOURS 133 
#define  RTC_MINUTES 132 
#define  RTC_MONTH 131 
#define  RTC_SECONDS 130 
#define  RTC_TIMER_CONTROL 129 
#define  RTC_WEEKDAY 128 
 unsigned char rtc_read (int) ; 

unsigned char
pcf8563_readreg(int reg)
{
	unsigned char res = rtc_read(reg);

	/* The PCF8563 does not return 0 for unimplemented bits. */
	switch (reg) {
		case RTC_SECONDS:
		case RTC_MINUTES:
			res &= 0x7F;
			break;
		case RTC_HOURS:
		case RTC_DAY_OF_MONTH:
			res &= 0x3F;
			break;
		case RTC_WEEKDAY:
			res &= 0x07;
			break;
		case RTC_MONTH:
			res &= 0x1F;
			break;
		case RTC_CONTROL1:
			res &= 0xA8;
			break;
		case RTC_CONTROL2:
			res &= 0x1F;
			break;
		case RTC_CLOCKOUT_FREQ:
		case RTC_TIMER_CONTROL:
			res &= 0x83;
			break;
	}
	return res;
}