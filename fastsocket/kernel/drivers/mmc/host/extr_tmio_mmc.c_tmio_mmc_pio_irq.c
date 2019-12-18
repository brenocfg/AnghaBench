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
struct tmio_mmc_host {unsigned int sg_off; TYPE_1__* sg_ptr; struct mmc_data* data; } ;
struct mmc_data {unsigned int blksz; int flags; } ;
struct TYPE_2__ {unsigned int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_SD_DATA_PORT ; 
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  sd_ctrl_read16_rep (struct tmio_mmc_host*,int /*<<< orphan*/ ,unsigned short*,unsigned int) ; 
 int /*<<< orphan*/  sd_ctrl_write16_rep (struct tmio_mmc_host*,int /*<<< orphan*/ ,unsigned short*,unsigned int) ; 
 unsigned int tmio_mmc_kmap_atomic (struct tmio_mmc_host*,unsigned long*) ; 
 int /*<<< orphan*/  tmio_mmc_kunmap_atomic (struct tmio_mmc_host*,unsigned long*) ; 
 int /*<<< orphan*/  tmio_mmc_next_sg (struct tmio_mmc_host*) ; 

__attribute__((used)) static inline void tmio_mmc_pio_irq(struct tmio_mmc_host *host)
{
	struct mmc_data *data = host->data;
	unsigned short *buf;
	unsigned int count;
	unsigned long flags;

	if (!data) {
		pr_debug("Spurious PIO IRQ\n");
		return;
	}

	buf = (unsigned short *)(tmio_mmc_kmap_atomic(host, &flags) +
	      host->sg_off);

	count = host->sg_ptr->length - host->sg_off;
	if (count > data->blksz)
		count = data->blksz;

	pr_debug("count: %08x offset: %08x flags %08x\n",
	    count, host->sg_off, data->flags);

	/* Transfer the data */
	if (data->flags & MMC_DATA_READ)
		sd_ctrl_read16_rep(host, CTL_SD_DATA_PORT, buf, count >> 1);
	else
		sd_ctrl_write16_rep(host, CTL_SD_DATA_PORT, buf, count >> 1);

	host->sg_off += count;

	tmio_mmc_kunmap_atomic(host, &flags);

	if (host->sg_off == host->sg_ptr->length)
		tmio_mmc_next_sg(host);

	return;
}