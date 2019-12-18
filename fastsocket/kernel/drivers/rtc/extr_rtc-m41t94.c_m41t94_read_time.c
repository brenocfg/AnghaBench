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
typedef  int u8 ;
struct spi_device {int dummy; } ;
struct rtc_time {scalar_t__ tm_wday; void* tm_year; scalar_t__ tm_mon; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int M41T94_BIT_CB ; 
 int M41T94_BIT_CEB ; 
 int M41T94_BIT_HALT ; 
 int M41T94_BIT_STOP ; 
 int M41T94_REG_DAY ; 
 int M41T94_REG_HOURS ; 
 int M41T94_REG_HT ; 
 int M41T94_REG_MINUTES ; 
 int M41T94_REG_MONTH ; 
 int M41T94_REG_SECONDS ; 
 int M41T94_REG_WDAY ; 
 int M41T94_REG_YEAR ; 
 void* bcd2bin (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,void*,void*,void*,void*,scalar_t__,void*,scalar_t__) ; 
 int rtc_valid_tm (struct rtc_time*) ; 
 int spi_w8r8 (struct spi_device*,int) ; 
 int /*<<< orphan*/  spi_write (struct spi_device*,int*,int) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int m41t94_read_time(struct device *dev, struct rtc_time *tm)
{
	struct spi_device *spi = to_spi_device(dev);
	u8 buf[2];
	int ret, hour;

	/* clear halt update bit */
	ret = spi_w8r8(spi, M41T94_REG_HT);
	if (ret < 0)
		return ret;
	if (ret & M41T94_BIT_HALT) {
		buf[0] = 0x80 | M41T94_REG_HT;
		buf[1] = ret & ~M41T94_BIT_HALT;
		spi_write(spi, buf, 2);
	}

	/* clear stop bit */
	ret = spi_w8r8(spi, M41T94_REG_SECONDS);
	if (ret < 0)
		return ret;
	if (ret & M41T94_BIT_STOP) {
		buf[0] = 0x80 | M41T94_REG_SECONDS;
		buf[1] = ret & ~M41T94_BIT_STOP;
		spi_write(spi, buf, 2);
	}

	tm->tm_sec  = bcd2bin(spi_w8r8(spi, M41T94_REG_SECONDS));
	tm->tm_min  = bcd2bin(spi_w8r8(spi, M41T94_REG_MINUTES));
	hour = spi_w8r8(spi, M41T94_REG_HOURS);
	tm->tm_hour = bcd2bin(hour & 0x3f);
	tm->tm_wday = bcd2bin(spi_w8r8(spi, M41T94_REG_WDAY)) - 1;
	tm->tm_mday = bcd2bin(spi_w8r8(spi, M41T94_REG_DAY));
	tm->tm_mon  = bcd2bin(spi_w8r8(spi, M41T94_REG_MONTH)) - 1;
	tm->tm_year = bcd2bin(spi_w8r8(spi, M41T94_REG_YEAR));
	if ((hour & M41T94_BIT_CB) || !(hour & M41T94_BIT_CEB))
		tm->tm_year += 100;

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, mon=%d, year=%d, wday=%d\n",
		"read", tm->tm_sec, tm->tm_min,
		tm->tm_hour, tm->tm_mday,
		tm->tm_mon, tm->tm_year, tm->tm_wday);

	/* initial clock setting can be undefined */
	return rtc_valid_tm(tm);
}