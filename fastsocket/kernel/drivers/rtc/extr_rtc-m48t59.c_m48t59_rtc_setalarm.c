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
typedef  int u8 ;
struct rtc_time {int tm_year; int tm_mday; int tm_hour; int tm_min; int tm_sec; int /*<<< orphan*/  tm_mon; } ;
struct rtc_wkalrm {struct rtc_time time; } ;
struct TYPE_2__ {struct m48t59_plat_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct m48t59_private {scalar_t__ irq; int /*<<< orphan*/  lock; } ;
struct m48t59_plat_data {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  M48T59_ALARM_DATE ; 
 int /*<<< orphan*/  M48T59_ALARM_HOUR ; 
 int /*<<< orphan*/  M48T59_ALARM_MIN ; 
 int /*<<< orphan*/  M48T59_ALARM_SEC ; 
 int /*<<< orphan*/  M48T59_CLEAR_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M48T59_CNTL ; 
 int /*<<< orphan*/  M48T59_CNTL_WRITE ; 
 int /*<<< orphan*/  M48T59_MDAY ; 
 int M48T59_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M48T59_SET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M48T59_WRITE (int,int /*<<< orphan*/ ) ; 
 scalar_t__ NO_IRQ ; 
 int bin2bcd (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int /*<<< orphan*/ ,int,int,int,int) ; 
 struct m48t59_private* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int m48t59_rtc_setalarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct m48t59_plat_data *pdata = pdev->dev.platform_data;
	struct m48t59_private *m48t59 = platform_get_drvdata(pdev);
	struct rtc_time *tm = &alrm->time;
	u8 mday, hour, min, sec;
	unsigned long flags;
	int year = tm->tm_year;

#ifdef CONFIG_SPARC
	/* Sun SPARC machines count years since 1968 */
	year -= 68;
#endif

	/* If no irq, we don't support ALARM */
	if (m48t59->irq == NO_IRQ)
		return -EIO;

	if (year < 0)
		return -EINVAL;

	/*
	 * 0xff means "always match"
	 */
	mday = tm->tm_mday;
	mday = (mday >= 1 && mday <= 31) ? bin2bcd(mday) : 0xff;
	if (mday == 0xff)
		mday = M48T59_READ(M48T59_MDAY);

	hour = tm->tm_hour;
	hour = (hour < 24) ? bin2bcd(hour) : 0x00;

	min = tm->tm_min;
	min = (min < 60) ? bin2bcd(min) : 0x00;

	sec = tm->tm_sec;
	sec = (sec < 60) ? bin2bcd(sec) : 0x00;

	spin_lock_irqsave(&m48t59->lock, flags);
	/* Issue the WRITE command */
	M48T59_SET_BITS(M48T59_CNTL_WRITE, M48T59_CNTL);

	M48T59_WRITE(mday, M48T59_ALARM_DATE);
	M48T59_WRITE(hour, M48T59_ALARM_HOUR);
	M48T59_WRITE(min, M48T59_ALARM_MIN);
	M48T59_WRITE(sec, M48T59_ALARM_SEC);

	/* Clear the WRITE bit */
	M48T59_CLEAR_BITS(M48T59_CNTL_WRITE, M48T59_CNTL);
	spin_unlock_irqrestore(&m48t59->lock, flags);

	dev_dbg(dev, "RTC set alarm time %04d-%02d-%02d %02d/%02d/%02d\n",
		year + 1900, tm->tm_mon, tm->tm_mday,
		tm->tm_hour, tm->tm_min, tm->tm_sec);
	return 0;
}