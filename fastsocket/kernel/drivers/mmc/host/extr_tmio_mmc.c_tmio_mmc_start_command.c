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
struct tmio_mmc_host {struct mmc_command* cmd; struct mmc_data* data; } ;
struct mmc_data {int blocks; int flags; } ;
struct mmc_command {int opcode; int /*<<< orphan*/  arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_ARG_REG ; 
 int /*<<< orphan*/  CTL_SD_CMD ; 
 int /*<<< orphan*/  CTL_STOP_INTERNAL_ACTION ; 
 int DATA_PRESENT ; 
 int EINVAL ; 
 int MMC_DATA_READ ; 
#define  MMC_RSP_NONE 132 
#define  MMC_RSP_R1 131 
#define  MMC_RSP_R1B 130 
#define  MMC_RSP_R2 129 
#define  MMC_RSP_R3 128 
 int RESP_NONE ; 
 int RESP_R1 ; 
 int RESP_R1B ; 
 int RESP_R2 ; 
 int RESP_R3 ; 
 int /*<<< orphan*/  TMIO_MASK_CMD ; 
 int TRANSFER_MULTI ; 
 int TRANSFER_READ ; 
 int /*<<< orphan*/  enable_mmc_irqs (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 int mmc_resp_type (struct mmc_command*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  sd_ctrl_write16 (struct tmio_mmc_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sd_ctrl_write32 (struct tmio_mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tmio_mmc_start_command(struct tmio_mmc_host *host, struct mmc_command *cmd)
{
	struct mmc_data *data = host->data;
	int c = cmd->opcode;

	/* Command 12 is handled by hardware */
	if (cmd->opcode == 12 && !cmd->arg) {
		sd_ctrl_write16(host, CTL_STOP_INTERNAL_ACTION, 0x001);
		return 0;
	}

	switch (mmc_resp_type(cmd)) {
	case MMC_RSP_NONE: c |= RESP_NONE; break;
	case MMC_RSP_R1:   c |= RESP_R1;   break;
	case MMC_RSP_R1B:  c |= RESP_R1B;  break;
	case MMC_RSP_R2:   c |= RESP_R2;   break;
	case MMC_RSP_R3:   c |= RESP_R3;   break;
	default:
		pr_debug("Unknown response type %d\n", mmc_resp_type(cmd));
		return -EINVAL;
	}

	host->cmd = cmd;

/* FIXME - this seems to be ok comented out but the spec suggest this bit should
 *         be set when issuing app commands.
 *	if(cmd->flags & MMC_FLAG_ACMD)
 *		c |= APP_CMD;
 */
	if (data) {
		c |= DATA_PRESENT;
		if (data->blocks > 1) {
			sd_ctrl_write16(host, CTL_STOP_INTERNAL_ACTION, 0x100);
			c |= TRANSFER_MULTI;
		}
		if (data->flags & MMC_DATA_READ)
			c |= TRANSFER_READ;
	}

	enable_mmc_irqs(host, TMIO_MASK_CMD);

	/* Fire off the command */
	sd_ctrl_write32(host, CTL_ARG_REG, cmd->arg);
	sd_ctrl_write16(host, CTL_SD_CMD, c);

	return 0;
}