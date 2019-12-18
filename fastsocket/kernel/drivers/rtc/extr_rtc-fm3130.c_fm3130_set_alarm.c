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
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int /*<<< orphan*/  tm_wday; int /*<<< orphan*/  tm_year; } ;
struct rtc_wkalrm {scalar_t__ enabled; struct rtc_time time; } ;
struct fm3130 {int* regs; int alarm; int /*<<< orphan*/  client; } ;
struct device {int dummy; } ;

/* Variables and functions */
 size_t FM3130_ALARM_DATE ; 
 size_t FM3130_ALARM_HOURS ; 
 size_t FM3130_ALARM_MINUTES ; 
 size_t FM3130_ALARM_MONTHS ; 
 int FM3130_ALARM_REGS ; 
 size_t FM3130_ALARM_SECONDS ; 
 size_t FM3130_RTC_CONTROL ; 
 int FM3130_RTC_CONTROL_BIT_AEN ; 
 int FM3130_RTC_CONTROL_BIT_AF ; 
 int FM3130_RTC_CONTROL_BIT_CAL ; 
 int bin2bcd (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 struct fm3130* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,size_t,int) ; 

__attribute__((used)) static int fm3130_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct fm3130 *fm3130 = dev_get_drvdata(dev);
	struct rtc_time *tm = &alrm->time;
	int i;

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, mon=%d, year=%d, wday=%d\n",
		"write alarm", tm->tm_sec, tm->tm_min,
		tm->tm_hour, tm->tm_mday,
		tm->tm_mon, tm->tm_year, tm->tm_wday);

	if (tm->tm_sec != -1)
		fm3130->regs[FM3130_ALARM_SECONDS] =
			bin2bcd(tm->tm_sec) | 0x80;

	if (tm->tm_min != -1)
		fm3130->regs[FM3130_ALARM_MINUTES] =
			bin2bcd(tm->tm_min) | 0x80;

	if (tm->tm_hour != -1)
		fm3130->regs[FM3130_ALARM_HOURS] =
			bin2bcd(tm->tm_hour) | 0x80;

	if (tm->tm_mday != -1)
		fm3130->regs[FM3130_ALARM_DATE] =
			bin2bcd(tm->tm_mday) | 0x80;

	if (tm->tm_mon != -1)
		fm3130->regs[FM3130_ALARM_MONTHS] =
			bin2bcd(tm->tm_mon + 1) | 0x80;

	dev_dbg(dev, "alarm write %02x %02x %02x %02x %02x\n",
			fm3130->regs[FM3130_ALARM_SECONDS],
			fm3130->regs[FM3130_ALARM_MINUTES],
			fm3130->regs[FM3130_ALARM_HOURS],
			fm3130->regs[FM3130_ALARM_DATE],
			fm3130->regs[FM3130_ALARM_MONTHS]);
	/* Writing time registers, we don't support multibyte transfers */
	for (i = 0; i < FM3130_ALARM_REGS; i++) {
		i2c_smbus_write_byte_data(fm3130->client,
					FM3130_ALARM_SECONDS + i,
					fm3130->regs[FM3130_ALARM_SECONDS + i]);
	}
	fm3130->regs[FM3130_RTC_CONTROL] =
		i2c_smbus_read_byte_data(fm3130->client, FM3130_RTC_CONTROL);
	/* Checking for alarm */
	if (fm3130->regs[FM3130_RTC_CONTROL] & FM3130_RTC_CONTROL_BIT_AF) {
		fm3130->alarm = 1;
		fm3130->regs[FM3130_RTC_CONTROL] &= ~FM3130_RTC_CONTROL_BIT_AF;
	}
	if (alrm->enabled) {
		i2c_smbus_write_byte_data(fm3130->client, FM3130_RTC_CONTROL,
			(fm3130->regs[FM3130_RTC_CONTROL] &
				~(FM3130_RTC_CONTROL_BIT_CAL)) |
					FM3130_RTC_CONTROL_BIT_AEN);
	} else {
		i2c_smbus_write_byte_data(fm3130->client, FM3130_RTC_CONTROL,
			fm3130->regs[FM3130_RTC_CONTROL] &
				~(FM3130_RTC_CONTROL_BIT_AEN));
	}
	return 0;
}