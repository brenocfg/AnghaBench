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
struct mg_host {scalar_t__ dev_base; int /*<<< orphan*/  rst; TYPE_1__* dev; } ;
struct mg_drv_data {scalar_t__ use_polling; } ;
typedef  int s32 ;
struct TYPE_2__ {struct mg_drv_data* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_BUSY ; 
 int ATA_NIEN ; 
 int ATA_SRST ; 
 int MG_ERR_INIT_STAT ; 
 scalar_t__ MG_REG_DRV_CTRL ; 
 scalar_t__ MG_REG_STATUS ; 
 int /*<<< orphan*/  MG_STAT_READY ; 
 int /*<<< orphan*/  MG_TMAX_HDRST_TO_RDY ; 
 int /*<<< orphan*/  MG_TMAX_RST_TO_BUSY ; 
 int /*<<< orphan*/  MG_TMAX_SWRST_TO_RDY ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int inb (scalar_t__) ; 
 int mg_wait (struct mg_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int mg_disk_init(struct mg_host *host)
{
	struct mg_drv_data *prv_data = host->dev->platform_data;
	s32 err;
	u8 init_status;

	/* hdd rst low */
	gpio_set_value(host->rst, 0);
	err = mg_wait(host, ATA_BUSY, MG_TMAX_RST_TO_BUSY);
	if (err)
		return err;

	/* hdd rst high */
	gpio_set_value(host->rst, 1);
	err = mg_wait(host, MG_STAT_READY, MG_TMAX_HDRST_TO_RDY);
	if (err)
		return err;

	/* soft reset on */
	outb(ATA_SRST | (prv_data->use_polling ? ATA_NIEN : 0),
			(unsigned long)host->dev_base + MG_REG_DRV_CTRL);
	err = mg_wait(host, ATA_BUSY, MG_TMAX_RST_TO_BUSY);
	if (err)
		return err;

	/* soft reset off */
	outb(prv_data->use_polling ? ATA_NIEN : 0,
			(unsigned long)host->dev_base + MG_REG_DRV_CTRL);
	err = mg_wait(host, MG_STAT_READY, MG_TMAX_SWRST_TO_RDY);
	if (err)
		return err;

	init_status = inb((unsigned long)host->dev_base + MG_REG_STATUS) & 0xf;

	if (init_status == 0xf)
		return MG_ERR_INIT_STAT;

	return err;
}