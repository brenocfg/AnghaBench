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
struct TYPE_2__ {void* tm_year; void* tm_mon; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct rtc_wkalrm {int enabled; TYPE_1__ time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_TIME_REGS ; 
 int BIT_RTC_INTERRUPTS_REG_IT_ALARM_M ; 
 int /*<<< orphan*/  REG_ALARM_SECONDS_REG ; 
 int /*<<< orphan*/  TWL4030_MODULE_RTC ; 
 void* bcd2bin (unsigned char) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int rtc_irq_bits ; 
 int twl4030_i2c_read (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alm)
{
	unsigned char rtc_data[ALL_TIME_REGS + 1];
	int ret;

	ret = twl4030_i2c_read(TWL4030_MODULE_RTC, rtc_data,
			       REG_ALARM_SECONDS_REG, ALL_TIME_REGS);
	if (ret < 0) {
		dev_err(dev, "rtc_read_alarm error %d\n", ret);
		return ret;
	}

	/* some of these fields may be wildcard/"match all" */
	alm->time.tm_sec = bcd2bin(rtc_data[0]);
	alm->time.tm_min = bcd2bin(rtc_data[1]);
	alm->time.tm_hour = bcd2bin(rtc_data[2]);
	alm->time.tm_mday = bcd2bin(rtc_data[3]);
	alm->time.tm_mon = bcd2bin(rtc_data[4]) - 1;
	alm->time.tm_year = bcd2bin(rtc_data[5]) + 100;

	/* report cached alarm enable state */
	if (rtc_irq_bits & BIT_RTC_INTERRUPTS_REG_IT_ALARM_M)
		alm->enabled = 1;

	return ret;
}