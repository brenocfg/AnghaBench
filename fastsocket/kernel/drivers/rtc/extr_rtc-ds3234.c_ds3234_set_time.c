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
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_wday; int tm_mday; int tm_mon; int tm_year; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS3234_REG_DATE ; 
 int /*<<< orphan*/  DS3234_REG_DAY ; 
 int /*<<< orphan*/  DS3234_REG_HOURS ; 
 int /*<<< orphan*/  DS3234_REG_MINUTES ; 
 int /*<<< orphan*/  DS3234_REG_MONTH ; 
 int /*<<< orphan*/  DS3234_REG_SECONDS ; 
 int /*<<< orphan*/  DS3234_REG_YEAR ; 
 int bin2bcd (int) ; 
 int /*<<< orphan*/  ds3234_set_reg (struct device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ds3234_set_time(struct device *dev, struct rtc_time *dt)
{
	ds3234_set_reg(dev, DS3234_REG_SECONDS, bin2bcd(dt->tm_sec));
	ds3234_set_reg(dev, DS3234_REG_MINUTES, bin2bcd(dt->tm_min));
	ds3234_set_reg(dev, DS3234_REG_HOURS, bin2bcd(dt->tm_hour) & 0x3f);

	/* 0 = Sun */
	ds3234_set_reg(dev, DS3234_REG_DAY, bin2bcd(dt->tm_wday + 1));
	ds3234_set_reg(dev, DS3234_REG_DATE, bin2bcd(dt->tm_mday));

	/* 0 = Jan */
	ds3234_set_reg(dev, DS3234_REG_MONTH, bin2bcd(dt->tm_mon + 1));

	/* Assume 20YY although we just want to make sure not to go negative. */
	if (dt->tm_year > 100)
		dt->tm_year -= 100;

	ds3234_set_reg(dev, DS3234_REG_YEAR, bin2bcd(dt->tm_year));

	return 0;
}