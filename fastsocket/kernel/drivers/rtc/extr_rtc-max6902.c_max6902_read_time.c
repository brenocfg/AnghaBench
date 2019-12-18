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
struct spi_device {int dummy; } ;
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_wday; int tm_year; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX6902_REG_CENTURY ; 
 int bcd2bin (unsigned char) ; 
 int max6902_get_reg (struct device*,int /*<<< orphan*/ ,unsigned char*) ; 
 int rtc_valid_tm (struct rtc_time*) ; 
 int spi_write_then_read (struct spi_device*,unsigned char*,int,unsigned char*,int) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int max6902_read_time(struct device *dev, struct rtc_time *dt)
{
	int err, century;
	struct spi_device *spi = to_spi_device(dev);
	unsigned char buf[8];

	buf[0] = 0xbf;	/* Burst read */

	err = spi_write_then_read(spi, buf, 1, buf, 8);
	if (err != 0)
		return err;

	/* The chip sends data in this order:
	 * Seconds, Minutes, Hours, Date, Month, Day, Year */
	dt->tm_sec	= bcd2bin(buf[0]);
	dt->tm_min	= bcd2bin(buf[1]);
	dt->tm_hour	= bcd2bin(buf[2]);
	dt->tm_mday	= bcd2bin(buf[3]);
	dt->tm_mon	= bcd2bin(buf[4]) - 1;
	dt->tm_wday	= bcd2bin(buf[5]);
	dt->tm_year	= bcd2bin(buf[6]);

	/* Read century */
	err = max6902_get_reg(dev, MAX6902_REG_CENTURY, &buf[0]);
	if (err != 0)
		return err;

	century = bcd2bin(buf[0]) * 100;

	dt->tm_year += century;
	dt->tm_year -= 1900;

	return rtc_valid_tm(dt);
}