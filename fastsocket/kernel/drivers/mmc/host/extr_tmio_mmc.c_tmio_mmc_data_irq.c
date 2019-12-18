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
struct tmio_mmc_host {struct mmc_data* data; } ;
struct mmc_data {int bytes_xfered; int blocks; int blksz; int flags; int /*<<< orphan*/  error; struct mmc_command* stop; } ;
struct mmc_command {int opcode; int /*<<< orphan*/  arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CTL_STOP_INTERNAL_ACTION ; 
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  TMIO_MASK_READOP ; 
 int /*<<< orphan*/  TMIO_MASK_WRITEOP ; 
 int /*<<< orphan*/  disable_mmc_irqs (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  sd_ctrl_write16 (struct tmio_mmc_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tmio_mmc_finish_request (struct tmio_mmc_host*) ; 

__attribute__((used)) static inline void tmio_mmc_data_irq(struct tmio_mmc_host *host)
{
	struct mmc_data *data = host->data;
	struct mmc_command *stop;

	host->data = NULL;

	if (!data) {
		pr_debug("Spurious data end IRQ\n");
		return;
	}
	stop = data->stop;

	/* FIXME - return correct transfer count on errors */
	if (!data->error)
		data->bytes_xfered = data->blocks * data->blksz;
	else
		data->bytes_xfered = 0;

	pr_debug("Completed data request\n");

	/*FIXME - other drivers allow an optional stop command of any given type
	 *        which we dont do, as the chip can auto generate them.
	 *        Perhaps we can be smarter about when to use auto CMD12 and
	 *        only issue the auto request when we know this is the desired
	 *        stop command, allowing fallback to the stop command the
	 *        upper layers expect. For now, we do what works.
	 */

	if (data->flags & MMC_DATA_READ)
		disable_mmc_irqs(host, TMIO_MASK_READOP);
	else
		disable_mmc_irqs(host, TMIO_MASK_WRITEOP);

	if (stop) {
		if (stop->opcode == 12 && !stop->arg)
			sd_ctrl_write16(host, CTL_STOP_INTERNAL_ACTION, 0x000);
		else
			BUG();
	}

	tmio_mmc_finish_request(host);
}