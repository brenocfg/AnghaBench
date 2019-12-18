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
typedef  int /*<<< orphan*/  txbuf ;
struct TYPE_2__ {struct rs5c348_plat_data* platform_data; } ;
struct spi_device {TYPE_1__ dev; } ;
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_wday; int tm_mday; int tm_mon; int tm_year; } ;
struct rs5c348_plat_data {scalar_t__ rtc_24h; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int RS5C348_BIT_PM ; 
 int RS5C348_BIT_Y2K ; 
 int RS5C348_CMD_MW (size_t) ; 
 int RS5C348_CMD_R (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RS5C348_REG_CTL2 ; 
 size_t RS5C348_REG_DAY ; 
 size_t RS5C348_REG_HOURS ; 
 size_t RS5C348_REG_MINS ; 
 size_t RS5C348_REG_MONTH ; 
 size_t RS5C348_REG_SECS ; 
 size_t RS5C348_REG_WDAY ; 
 size_t RS5C348_REG_YEAR ; 
 int bin2bcd (int) ; 
 int spi_write_then_read (struct spi_device*,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct spi_device* to_spi_device (struct device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
rs5c348_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct spi_device *spi = to_spi_device(dev);
	struct rs5c348_plat_data *pdata = spi->dev.platform_data;
	u8 txbuf[5+7], *txp;
	int ret;

	/* Transfer 5 bytes before writing SEC.  This gives 31us for carry. */
	txp = txbuf;
	txbuf[0] = RS5C348_CMD_R(RS5C348_REG_CTL2); /* cmd, ctl2 */
	txbuf[1] = 0;	/* dummy */
	txbuf[2] = RS5C348_CMD_R(RS5C348_REG_CTL2); /* cmd, ctl2 */
	txbuf[3] = 0;	/* dummy */
	txbuf[4] = RS5C348_CMD_MW(RS5C348_REG_SECS); /* cmd, sec, ... */
	txp = &txbuf[5];
	txp[RS5C348_REG_SECS] = bin2bcd(tm->tm_sec);
	txp[RS5C348_REG_MINS] = bin2bcd(tm->tm_min);
	if (pdata->rtc_24h) {
		txp[RS5C348_REG_HOURS] = bin2bcd(tm->tm_hour);
	} else {
		/* hour 0 is AM12, noon is PM12 */
		txp[RS5C348_REG_HOURS] = bin2bcd((tm->tm_hour + 11) % 12 + 1) |
			(tm->tm_hour >= 12 ? RS5C348_BIT_PM : 0);
	}
	txp[RS5C348_REG_WDAY] = bin2bcd(tm->tm_wday);
	txp[RS5C348_REG_DAY] = bin2bcd(tm->tm_mday);
	txp[RS5C348_REG_MONTH] = bin2bcd(tm->tm_mon + 1) |
		(tm->tm_year >= 100 ? RS5C348_BIT_Y2K : 0);
	txp[RS5C348_REG_YEAR] = bin2bcd(tm->tm_year % 100);
	/* write in one transfer to avoid data inconsistency */
	ret = spi_write_then_read(spi, txbuf, sizeof(txbuf), NULL, 0);
	udelay(62);	/* Tcsr 62us */
	return ret;
}