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
typedef  size_t u8 ;
struct rtc_time {size_t tm_sec; size_t tm_min; size_t tm_hour; size_t tm_wday; size_t tm_mday; size_t tm_mon; size_t tm_year; } ;
struct ds1305 {int /*<<< orphan*/  spi; } ;
struct device {int dummy; } ;

/* Variables and functions */
 size_t DS1305_HOUR ; 
 size_t DS1305_MDAY ; 
 size_t DS1305_MIN ; 
 size_t DS1305_MON ; 
 int DS1305_RTC_LEN ; 
 size_t DS1305_SEC ; 
 size_t DS1305_WDAY ; 
 size_t DS1305_YEAR ; 
 void* bcd2bin (size_t) ; 
 size_t bcd2hour (size_t) ; 
 struct ds1305* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_vdbg (struct device*,char*,char*,size_t,size_t,size_t,size_t,size_t,size_t,size_t) ; 
 int rtc_valid_tm (struct rtc_time*) ; 
 int spi_write_then_read (int /*<<< orphan*/ ,size_t*,int,size_t*,int) ; 

__attribute__((used)) static int ds1305_get_time(struct device *dev, struct rtc_time *time)
{
	struct ds1305	*ds1305 = dev_get_drvdata(dev);
	u8		addr = DS1305_SEC;
	u8		buf[DS1305_RTC_LEN];
	int		status;

	/* Use write-then-read to get all the date/time registers
	 * since dma from stack is nonportable
	 */
	status = spi_write_then_read(ds1305->spi, &addr, sizeof addr,
			buf, sizeof buf);
	if (status < 0)
		return status;

	dev_vdbg(dev, "%s: %02x %02x %02x, %02x %02x %02x %02x\n",
		"read", buf[0], buf[1], buf[2], buf[3],
		buf[4], buf[5], buf[6]);

	/* Decode the registers */
	time->tm_sec = bcd2bin(buf[DS1305_SEC]);
	time->tm_min = bcd2bin(buf[DS1305_MIN]);
	time->tm_hour = bcd2hour(buf[DS1305_HOUR]);
	time->tm_wday = buf[DS1305_WDAY] - 1;
	time->tm_mday = bcd2bin(buf[DS1305_MDAY]);
	time->tm_mon = bcd2bin(buf[DS1305_MON]) - 1;
	time->tm_year = bcd2bin(buf[DS1305_YEAR]) + 100;

	dev_vdbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, mon=%d, year=%d, wday=%d\n",
		"read", time->tm_sec, time->tm_min,
		time->tm_hour, time->tm_mday,
		time->tm_mon, time->tm_year, time->tm_wday);

	/* Time may not be set */
	return rtc_valid_tm(time);
}