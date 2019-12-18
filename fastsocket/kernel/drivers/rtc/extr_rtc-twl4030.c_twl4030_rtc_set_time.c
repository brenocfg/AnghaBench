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
struct rtc_time {scalar_t__ tm_year; scalar_t__ tm_mon; scalar_t__ tm_mday; scalar_t__ tm_hour; scalar_t__ tm_min; scalar_t__ tm_sec; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_TIME_REGS ; 
 unsigned char BIT_RTC_CTRL_REG_STOP_RTC_M ; 
 int /*<<< orphan*/  REG_RTC_CTRL_REG ; 
 int /*<<< orphan*/  REG_SECONDS_REG ; 
 int /*<<< orphan*/  TWL4030_MODULE_RTC ; 
 unsigned char bin2bcd (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int twl4030_i2c_write (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int twl4030_rtc_read_u8 (unsigned char*,int /*<<< orphan*/ ) ; 
 int twl4030_rtc_write_u8 (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	unsigned char save_control;
	unsigned char rtc_data[ALL_TIME_REGS + 1];
	int ret;

	rtc_data[1] = bin2bcd(tm->tm_sec);
	rtc_data[2] = bin2bcd(tm->tm_min);
	rtc_data[3] = bin2bcd(tm->tm_hour);
	rtc_data[4] = bin2bcd(tm->tm_mday);
	rtc_data[5] = bin2bcd(tm->tm_mon + 1);
	rtc_data[6] = bin2bcd(tm->tm_year - 100);

	/* Stop RTC while updating the TC registers */
	ret = twl4030_rtc_read_u8(&save_control, REG_RTC_CTRL_REG);
	if (ret < 0)
		goto out;

	save_control &= ~BIT_RTC_CTRL_REG_STOP_RTC_M;
	twl4030_rtc_write_u8(save_control, REG_RTC_CTRL_REG);
	if (ret < 0)
		goto out;

	/* update all the time registers in one shot */
	ret = twl4030_i2c_write(TWL4030_MODULE_RTC, rtc_data,
			REG_SECONDS_REG, ALL_TIME_REGS);
	if (ret < 0) {
		dev_err(dev, "rtc_set_time error %d\n", ret);
		goto out;
	}

	/* Start back RTC */
	save_control |= BIT_RTC_CTRL_REG_STOP_RTC_M;
	ret = twl4030_rtc_write_u8(save_control, REG_RTC_CTRL_REG);

out:
	return ret;
}