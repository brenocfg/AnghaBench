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
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_year; int tm_wday; } ;
struct ds1307 {int* regs; int type; int (* write_block_data ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ;int /*<<< orphan*/  offset; int /*<<< orphan*/  client; } ;
struct device {int dummy; } ;

/* Variables and functions */
 size_t DS1307_REG_HOUR ; 
 size_t DS1307_REG_MDAY ; 
 size_t DS1307_REG_MIN ; 
 size_t DS1307_REG_MONTH ; 
 size_t DS1307_REG_SECS ; 
 size_t DS1307_REG_WDAY ; 
 size_t DS1307_REG_YEAR ; 
 int DS1337_BIT_CENTURY ; 
 int DS1340_BIT_CENTURY ; 
 int DS1340_BIT_CENTURY_EN ; 
 int bin2bcd (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*,int) ; 
 struct ds1307* dev_get_drvdata (struct device*) ; 
#define  ds_1337 131 
#define  ds_1339 130 
#define  ds_1340 129 
#define  ds_3231 128 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int ds1307_set_time(struct device *dev, struct rtc_time *t)
{
	struct ds1307	*ds1307 = dev_get_drvdata(dev);
	int		result;
	int		tmp;
	u8		*buf = ds1307->regs;

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, mon=%d, year=%d, wday=%d\n",
		"write", t->tm_sec, t->tm_min,
		t->tm_hour, t->tm_mday,
		t->tm_mon, t->tm_year, t->tm_wday);

	buf[DS1307_REG_SECS] = bin2bcd(t->tm_sec);
	buf[DS1307_REG_MIN] = bin2bcd(t->tm_min);
	buf[DS1307_REG_HOUR] = bin2bcd(t->tm_hour);
	buf[DS1307_REG_WDAY] = bin2bcd(t->tm_wday + 1);
	buf[DS1307_REG_MDAY] = bin2bcd(t->tm_mday);
	buf[DS1307_REG_MONTH] = bin2bcd(t->tm_mon + 1);

	/* assume 20YY not 19YY */
	tmp = t->tm_year - 100;
	buf[DS1307_REG_YEAR] = bin2bcd(tmp);

	switch (ds1307->type) {
	case ds_1337:
	case ds_1339:
	case ds_3231:
		buf[DS1307_REG_MONTH] |= DS1337_BIT_CENTURY;
		break;
	case ds_1340:
		buf[DS1307_REG_HOUR] |= DS1340_BIT_CENTURY_EN
				| DS1340_BIT_CENTURY;
		break;
	default:
		break;
	}

	dev_dbg(dev, "%s: %02x %02x %02x %02x %02x %02x %02x\n",
		"write", buf[0], buf[1], buf[2], buf[3],
		buf[4], buf[5], buf[6]);

	result = ds1307->write_block_data(ds1307->client,
		ds1307->offset, 7, buf);
	if (result < 0) {
		dev_err(dev, "%s error %d\n", "write", result);
		return result;
	}
	return 0;
}