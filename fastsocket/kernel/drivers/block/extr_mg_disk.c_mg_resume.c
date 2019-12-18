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
struct TYPE_2__ {struct mg_drv_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mg_host {scalar_t__ dev_base; } ;
struct mg_drv_data {int /*<<< orphan*/  use_polling; struct mg_host* host; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MG_CMD_WAKEUP ; 
 scalar_t__ MG_REG_COMMAND ; 
 scalar_t__ MG_REG_DRV_CTRL ; 
 int /*<<< orphan*/  MG_STAT_READY ; 
 int /*<<< orphan*/  MG_TMAX_CONF_TO_CMD ; 
 scalar_t__ mg_wait (struct mg_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int mg_resume(struct platform_device *plat_dev)
{
	struct mg_drv_data *prv_data = plat_dev->dev.platform_data;
	struct mg_host *host = prv_data->host;

	if (mg_wait(host, MG_STAT_READY, MG_TMAX_CONF_TO_CMD))
		return -EIO;

	outb(MG_CMD_WAKEUP, (unsigned long)host->dev_base + MG_REG_COMMAND);
	/* wait until mflash wakeup */
	msleep(1);

	if (mg_wait(host, MG_STAT_READY, MG_TMAX_CONF_TO_CMD))
		return -EIO;

	if (!prv_data->use_polling)
		outb(0, (unsigned long)host->dev_base + MG_REG_DRV_CTRL);

	return 0;
}