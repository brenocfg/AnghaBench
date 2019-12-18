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
struct mg_host {scalar_t__ dev_base; scalar_t__ rst; scalar_t__ rstout; int /*<<< orphan*/  irq; int /*<<< orphan*/  major; scalar_t__ breq; scalar_t__ gd; int /*<<< orphan*/  timer; } ;
struct mg_drv_data {scalar_t__ dev_attr; int /*<<< orphan*/  use_polling; struct mg_host* host; } ;

/* Variables and functions */
 scalar_t__ MG_BOOT_DEV ; 
 int /*<<< orphan*/  MG_DISK_NAME ; 
 int /*<<< orphan*/  blk_cleanup_queue (scalar_t__) ; 
 int /*<<< orphan*/  del_gendisk (scalar_t__) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mg_host*) ; 
 int /*<<< orphan*/  gpio_free (scalar_t__) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct mg_host*) ; 
 int /*<<< orphan*/  put_disk (scalar_t__) ; 
 int /*<<< orphan*/  unregister_blkdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mg_remove(struct platform_device *plat_dev)
{
	struct mg_drv_data *prv_data = plat_dev->dev.platform_data;
	struct mg_host *host = prv_data->host;
	int err = 0;

	/* delete timer */
	del_timer_sync(&host->timer);

	/* remove disk */
	if (host->gd) {
		del_gendisk(host->gd);
		put_disk(host->gd);
	}
	/* remove queue */
	if (host->breq)
		blk_cleanup_queue(host->breq);

	/* unregister blk device */
	unregister_blkdev(host->major, MG_DISK_NAME);

	/* free irq */
	if (!prv_data->use_polling)
		free_irq(host->irq, host);

	/* free reset-out pin */
	if (prv_data->dev_attr != MG_BOOT_DEV)
		gpio_free(host->rstout);

	/* free rst pin */
	if (host->rst)
		gpio_free(host->rst);

	/* unmap io */
	if (host->dev_base)
		iounmap(host->dev_base);

	/* free mg_host */
	kfree(host);

	return err;
}