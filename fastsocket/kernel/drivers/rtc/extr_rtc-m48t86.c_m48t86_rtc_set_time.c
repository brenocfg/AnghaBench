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
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_year; int tm_wday; } ;
struct TYPE_2__ {struct m48t86_ops* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct m48t86_ops {unsigned char (* readbyte ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* writebyte ) (unsigned char,int /*<<< orphan*/ ) ;} ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M48T86_REG_B ; 
 unsigned char M48T86_REG_B_DM ; 
 unsigned char M48T86_REG_B_H24 ; 
 unsigned char M48T86_REG_B_SET ; 
 int /*<<< orphan*/  M48T86_REG_DOM ; 
 int /*<<< orphan*/  M48T86_REG_DOW ; 
 int /*<<< orphan*/  M48T86_REG_HOUR ; 
 int /*<<< orphan*/  M48T86_REG_MIN ; 
 int /*<<< orphan*/  M48T86_REG_MONTH ; 
 int /*<<< orphan*/  M48T86_REG_SEC ; 
 int /*<<< orphan*/  M48T86_REG_YEAR ; 
 int bin2bcd (int) ; 
 unsigned char stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub14 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub16 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub17 (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int m48t86_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	unsigned char reg;
	struct platform_device *pdev = to_platform_device(dev);
	struct m48t86_ops *ops = pdev->dev.platform_data;

	reg = ops->readbyte(M48T86_REG_B);

	/* update flag and 24h mode */
	reg |= M48T86_REG_B_SET | M48T86_REG_B_H24;
	ops->writebyte(reg, M48T86_REG_B);

	if (reg & M48T86_REG_B_DM) {
		/* data (binary) mode */
		ops->writebyte(tm->tm_sec, M48T86_REG_SEC);
		ops->writebyte(tm->tm_min, M48T86_REG_MIN);
		ops->writebyte(tm->tm_hour, M48T86_REG_HOUR);
		ops->writebyte(tm->tm_mday, M48T86_REG_DOM);
		ops->writebyte(tm->tm_mon + 1, M48T86_REG_MONTH);
		ops->writebyte(tm->tm_year % 100, M48T86_REG_YEAR);
		ops->writebyte(tm->tm_wday, M48T86_REG_DOW);
	} else {
		/* bcd mode */
		ops->writebyte(bin2bcd(tm->tm_sec), M48T86_REG_SEC);
		ops->writebyte(bin2bcd(tm->tm_min), M48T86_REG_MIN);
		ops->writebyte(bin2bcd(tm->tm_hour), M48T86_REG_HOUR);
		ops->writebyte(bin2bcd(tm->tm_mday), M48T86_REG_DOM);
		ops->writebyte(bin2bcd(tm->tm_mon + 1), M48T86_REG_MONTH);
		ops->writebyte(bin2bcd(tm->tm_year % 100), M48T86_REG_YEAR);
		ops->writebyte(bin2bcd(tm->tm_wday), M48T86_REG_DOW);
	}

	/* update ended */
	reg &= ~M48T86_REG_B_SET;
	ops->writebyte(reg, M48T86_REG_B);

	return 0;
}