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
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_year; } ;
struct ds1286_priv {int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  RTC_CMD ; 
 int /*<<< orphan*/  RTC_DATE ; 
 int /*<<< orphan*/  RTC_HOURS ; 
 int /*<<< orphan*/  RTC_MINUTES ; 
 int /*<<< orphan*/  RTC_MONTH ; 
 int /*<<< orphan*/  RTC_SECONDS ; 
 int RTC_TE ; 
 int /*<<< orphan*/  RTC_YEAR ; 
 int /*<<< orphan*/  barrier () ; 
 void* bcd2bin (int) ; 
 struct ds1286_priv* dev_get_drvdata (struct device*) ; 
 int ds1286_rtc_read (struct ds1286_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds1286_rtc_write (struct ds1286_priv*,unsigned char,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int rtc_valid_tm (struct rtc_time*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int ds1286_read_time(struct device *dev, struct rtc_time *tm)
{
	struct ds1286_priv *priv = dev_get_drvdata(dev);
	unsigned char save_control;
	unsigned long flags;
	unsigned long uip_watchdog = jiffies;

	/*
	 * read RTC once any update in progress is done. The update
	 * can take just over 2ms. We wait 10 to 20ms. There is no need to
	 * to poll-wait (up to 1s - eeccch) for the falling edge of RTC_UIP.
	 * If you need to know *exactly* when a second has started, enable
	 * periodic update complete interrupts, (via ioctl) and then
	 * immediately read /dev/rtc which will block until you get the IRQ.
	 * Once the read clears, read the RTC time (again via ioctl). Easy.
	 */

	if (ds1286_rtc_read(priv, RTC_CMD) & RTC_TE)
		while (time_before(jiffies, uip_watchdog + 2*HZ/100))
			barrier();

	/*
	 * Only the values that we read from the RTC are set. We leave
	 * tm_wday, tm_yday and tm_isdst untouched. Even though the
	 * RTC has RTC_DAY_OF_WEEK, we ignore it, as it is only updated
	 * by the RTC when initially set to a non-zero value.
	 */
	spin_lock_irqsave(&priv->lock, flags);
	save_control = ds1286_rtc_read(priv, RTC_CMD);
	ds1286_rtc_write(priv, (save_control|RTC_TE), RTC_CMD);

	tm->tm_sec = ds1286_rtc_read(priv, RTC_SECONDS);
	tm->tm_min = ds1286_rtc_read(priv, RTC_MINUTES);
	tm->tm_hour = ds1286_rtc_read(priv, RTC_HOURS) & 0x3f;
	tm->tm_mday = ds1286_rtc_read(priv, RTC_DATE);
	tm->tm_mon = ds1286_rtc_read(priv, RTC_MONTH) & 0x1f;
	tm->tm_year = ds1286_rtc_read(priv, RTC_YEAR);

	ds1286_rtc_write(priv, save_control, RTC_CMD);
	spin_unlock_irqrestore(&priv->lock, flags);

	tm->tm_sec = bcd2bin(tm->tm_sec);
	tm->tm_min = bcd2bin(tm->tm_min);
	tm->tm_hour = bcd2bin(tm->tm_hour);
	tm->tm_mday = bcd2bin(tm->tm_mday);
	tm->tm_mon = bcd2bin(tm->tm_mon);
	tm->tm_year = bcd2bin(tm->tm_year);

	/*
	 * Account for differences between how the RTC uses the values
	 * and how they are defined in a struct rtc_time;
	 */
	if (tm->tm_year < 45)
		tm->tm_year += 30;
	tm->tm_year += 40;
	if (tm->tm_year < 70)
		tm->tm_year += 100;

	tm->tm_mon--;

	return rtc_valid_tm(tm);
}