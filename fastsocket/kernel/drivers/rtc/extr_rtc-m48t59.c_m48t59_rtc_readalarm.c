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
struct rtc_time {void* tm_sec; void* tm_min; void* tm_hour; void* tm_mday; void* tm_mon; void* tm_year; } ;
struct rtc_wkalrm {struct rtc_time time; } ;
struct TYPE_2__ {struct m48t59_plat_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct m48t59_private {scalar_t__ irq; int /*<<< orphan*/  lock; } ;
struct m48t59_plat_data {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  M48T59_ALARM_DATE ; 
 int /*<<< orphan*/  M48T59_ALARM_HOUR ; 
 int /*<<< orphan*/  M48T59_ALARM_MIN ; 
 int /*<<< orphan*/  M48T59_ALARM_SEC ; 
 int /*<<< orphan*/  M48T59_CLEAR_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M48T59_CNTL ; 
 int /*<<< orphan*/  M48T59_CNTL_READ ; 
 int /*<<< orphan*/  M48T59_MONTH ; 
 int M48T59_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M48T59_SET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M48T59_WDAY ; 
 int M48T59_WDAY_CB ; 
 int M48T59_WDAY_CEB ; 
 int /*<<< orphan*/  M48T59_YEAR ; 
 scalar_t__ NO_IRQ ; 
 void* bcd2bin (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,void*,void*,void*,void*,void*,void*) ; 
 struct m48t59_private* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int m48t59_rtc_readalarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct m48t59_plat_data *pdata = pdev->dev.platform_data;
	struct m48t59_private *m48t59 = platform_get_drvdata(pdev);
	struct rtc_time *tm = &alrm->time;
	unsigned long flags;
	u8 val;

	/* If no irq, we don't support ALARM */
	if (m48t59->irq == NO_IRQ)
		return -EIO;

	spin_lock_irqsave(&m48t59->lock, flags);
	/* Issue the READ command */
	M48T59_SET_BITS(M48T59_CNTL_READ, M48T59_CNTL);

	tm->tm_year = bcd2bin(M48T59_READ(M48T59_YEAR));
#ifdef CONFIG_SPARC
	/* Sun SPARC machines count years since 1968 */
	tm->tm_year += 68;
#endif
	/* tm_mon is 0-11 */
	tm->tm_mon = bcd2bin(M48T59_READ(M48T59_MONTH)) - 1;

	val = M48T59_READ(M48T59_WDAY);
	if ((val & M48T59_WDAY_CEB) && (val & M48T59_WDAY_CB))
		tm->tm_year += 100;	/* one century */

	tm->tm_mday = bcd2bin(M48T59_READ(M48T59_ALARM_DATE));
	tm->tm_hour = bcd2bin(M48T59_READ(M48T59_ALARM_HOUR));
	tm->tm_min = bcd2bin(M48T59_READ(M48T59_ALARM_MIN));
	tm->tm_sec = bcd2bin(M48T59_READ(M48T59_ALARM_SEC));

	/* Clear the READ bit */
	M48T59_CLEAR_BITS(M48T59_CNTL_READ, M48T59_CNTL);
	spin_unlock_irqrestore(&m48t59->lock, flags);

	dev_dbg(dev, "RTC read alarm time %04d-%02d-%02d %02d/%02d/%02d\n",
		tm->tm_year + 1900, tm->tm_mon, tm->tm_mday,
		tm->tm_hour, tm->tm_min, tm->tm_sec);
	return 0;
}