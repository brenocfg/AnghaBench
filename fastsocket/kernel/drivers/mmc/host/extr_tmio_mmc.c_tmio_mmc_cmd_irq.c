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
struct tmio_mmc_host {TYPE_1__* data; struct mmc_command* cmd; } ;
struct mmc_command {int* resp; int flags; int /*<<< orphan*/  error; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CTL_RESPONSE ; 
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int MMC_DATA_READ ; 
 int MMC_RSP_136 ; 
 int MMC_RSP_CRC ; 
 int MMC_RSP_R3 ; 
 int /*<<< orphan*/  TMIO_MASK_READOP ; 
 int /*<<< orphan*/  TMIO_MASK_WRITEOP ; 
 unsigned int TMIO_STAT_CMDTIMEOUT ; 
 unsigned int TMIO_STAT_CRCFAIL ; 
 int /*<<< orphan*/  enable_mmc_irqs (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int sd_ctrl_read32 (struct tmio_mmc_host*,int) ; 
 int /*<<< orphan*/  tmio_mmc_finish_request (struct tmio_mmc_host*) ; 

__attribute__((used)) static inline void tmio_mmc_cmd_irq(struct tmio_mmc_host *host,
	unsigned int stat)
{
	struct mmc_command *cmd = host->cmd;
	int i, addr;

	if (!host->cmd) {
		pr_debug("Spurious CMD irq\n");
		return;
	}

	host->cmd = NULL;

	/* This controller is sicker than the PXA one. Not only do we need to
	 * drop the top 8 bits of the first response word, we also need to
	 * modify the order of the response for short response command types.
	 */

	for (i = 3, addr = CTL_RESPONSE ; i >= 0 ; i--, addr += 4)
		cmd->resp[i] = sd_ctrl_read32(host, addr);

	if (cmd->flags &  MMC_RSP_136) {
		cmd->resp[0] = (cmd->resp[0] << 8) | (cmd->resp[1] >> 24);
		cmd->resp[1] = (cmd->resp[1] << 8) | (cmd->resp[2] >> 24);
		cmd->resp[2] = (cmd->resp[2] << 8) | (cmd->resp[3] >> 24);
		cmd->resp[3] <<= 8;
	} else if (cmd->flags & MMC_RSP_R3) {
		cmd->resp[0] = cmd->resp[3];
	}

	if (stat & TMIO_STAT_CMDTIMEOUT)
		cmd->error = -ETIMEDOUT;
	else if (stat & TMIO_STAT_CRCFAIL && cmd->flags & MMC_RSP_CRC)
		cmd->error = -EILSEQ;

	/* If there is data to handle we enable data IRQs here, and
	 * we will ultimatley finish the request in the data_end handler.
	 * If theres no data or we encountered an error, finish now.
	 */
	if (host->data && !cmd->error) {
		if (host->data->flags & MMC_DATA_READ)
			enable_mmc_irqs(host, TMIO_MASK_READOP);
		else
			enable_mmc_irqs(host, TMIO_MASK_WRITEOP);
	} else {
		tmio_mmc_finish_request(host);
	}

	return;
}