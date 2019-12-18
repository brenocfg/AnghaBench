#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rtc_time {scalar_t__ tm_mon; int /*<<< orphan*/  tm_wday; int /*<<< orphan*/  tm_year; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct rtc_wkalrm {struct rtc_time time; } ;
struct fm3130 {int* regs; int /*<<< orphan*/ * msg; TYPE_2__* client; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int EIO ; 
 size_t FM3130_ALARM_DATE ; 
 size_t FM3130_ALARM_HOURS ; 
 size_t FM3130_ALARM_MINUTES ; 
 size_t FM3130_ALARM_MONTHS ; 
 size_t FM3130_ALARM_SECONDS ; 
 void* bcd2bin (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*,int) ; 
 struct fm3130* dev_get_drvdata (struct device*) ; 
 int i2c_transfer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  to_i2c_adapter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fm3130_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct fm3130 *fm3130 = dev_get_drvdata(dev);
	int tmp;
	struct rtc_time *tm = &alrm->time;
	/* read the RTC alarm registers all at once */
	tmp = i2c_transfer(to_i2c_adapter(fm3130->client->dev.parent),
			&fm3130->msg[2], 2);
	if (tmp != 2) {
		dev_err(dev, "%s error %d\n", "read", tmp);
		return -EIO;
	}
	dev_dbg(dev, "alarm read %02x %02x %02x %02x %02x\n",
			fm3130->regs[FM3130_ALARM_SECONDS],
			fm3130->regs[FM3130_ALARM_MINUTES],
			fm3130->regs[FM3130_ALARM_HOURS],
			fm3130->regs[FM3130_ALARM_DATE],
			fm3130->regs[FM3130_ALARM_MONTHS]);


	tm->tm_sec	= bcd2bin(fm3130->regs[FM3130_ALARM_SECONDS] & 0x7F);
	tm->tm_min	= bcd2bin(fm3130->regs[FM3130_ALARM_MINUTES] & 0x7F);
	tm->tm_hour	= bcd2bin(fm3130->regs[FM3130_ALARM_HOURS] & 0x3F);
	tm->tm_mday	= bcd2bin(fm3130->regs[FM3130_ALARM_DATE] & 0x3F);
	tm->tm_mon	= bcd2bin(fm3130->regs[FM3130_ALARM_MONTHS] & 0x1F);
	if (tm->tm_mon > 0)
		tm->tm_mon -= 1; /* RTC is 1-12, tm_mon is 0-11 */
	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, mon=%d, year=%d, wday=%d\n",
		"read alarm", tm->tm_sec, tm->tm_min,
		tm->tm_hour, tm->tm_mday,
		tm->tm_mon, tm->tm_year, tm->tm_wday);

	return 0;
}