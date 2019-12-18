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
typedef  int /*<<< orphan*/  u8 ;
struct rtc_time {int tm_wday; scalar_t__ tm_year; scalar_t__ tm_mon; scalar_t__ tm_mday; int /*<<< orphan*/  tm_hour; scalar_t__ tm_min; scalar_t__ tm_sec; } ;
struct ds1305 {int /*<<< orphan*/  spi; int /*<<< orphan*/  hr12; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS1305_RTC_LEN ; 
 int DS1305_SEC ; 
 int DS1305_WRITE ; 
 void* bin2bcd (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ds1305* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_vdbg (struct device*,char*,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  hour2bcd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spi_write_then_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds1305_set_time(struct device *dev, struct rtc_time *time)
{
	struct ds1305	*ds1305 = dev_get_drvdata(dev);
	u8		buf[1 + DS1305_RTC_LEN];
	u8		*bp = buf;

	dev_vdbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, mon=%d, year=%d, wday=%d\n",
		"write", time->tm_sec, time->tm_min,
		time->tm_hour, time->tm_mday,
		time->tm_mon, time->tm_year, time->tm_wday);

	/* Write registers starting at the first time/date address. */
	*bp++ = DS1305_WRITE | DS1305_SEC;

	*bp++ = bin2bcd(time->tm_sec);
	*bp++ = bin2bcd(time->tm_min);
	*bp++ = hour2bcd(ds1305->hr12, time->tm_hour);
	*bp++ = (time->tm_wday < 7) ? (time->tm_wday + 1) : 1;
	*bp++ = bin2bcd(time->tm_mday);
	*bp++ = bin2bcd(time->tm_mon + 1);
	*bp++ = bin2bcd(time->tm_year - 100);

	dev_dbg(dev, "%s: %02x %02x %02x, %02x %02x %02x %02x\n",
		"write", buf[1], buf[2], buf[3],
		buf[4], buf[5], buf[6], buf[7]);

	/* use write-then-read since dma from stack is nonportable */
	return spi_write_then_read(ds1305->spi, buf, sizeof buf,
			NULL, 0);
}