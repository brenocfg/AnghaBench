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
struct mxcmci_host {scalar_t__ base; int /*<<< orphan*/  mmc; struct mmc_command* cmd; } ;
struct mmc_command {int error; unsigned int opcode; int arg; } ;

/* Variables and functions */
 unsigned int CMD_DAT_CONT_RESPONSE_136BIT ; 
 unsigned int CMD_DAT_CONT_RESPONSE_48BIT ; 
 unsigned int CMD_DAT_CONT_RESPONSE_48BIT_CRC ; 
 int EINVAL ; 
 int INT_END_CMD_RES_EN ; 
 int INT_READ_OP_EN ; 
 int INT_WRITE_OP_DONE_EN ; 
 scalar_t__ MMC_REG_ARG ; 
 scalar_t__ MMC_REG_CMD ; 
 scalar_t__ MMC_REG_CMD_DAT_CONT ; 
 scalar_t__ MMC_REG_INT_CNTR ; 
#define  MMC_RSP_NONE 132 
#define  MMC_RSP_R1 131 
#define  MMC_RSP_R1B 130 
#define  MMC_RSP_R2 129 
#define  MMC_RSP_R3 128 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int mmc_resp_type (struct mmc_command*) ; 
 scalar_t__ mxcmci_use_dma (struct mxcmci_host*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  writew (unsigned int,scalar_t__) ; 

__attribute__((used)) static int mxcmci_start_cmd(struct mxcmci_host *host, struct mmc_command *cmd,
		unsigned int cmdat)
{
	WARN_ON(host->cmd != NULL);
	host->cmd = cmd;

	switch (mmc_resp_type(cmd)) {
	case MMC_RSP_R1: /* short CRC, OPCODE */
	case MMC_RSP_R1B:/* short CRC, OPCODE, BUSY */
		cmdat |= CMD_DAT_CONT_RESPONSE_48BIT_CRC;
		break;
	case MMC_RSP_R2: /* long 136 bit + CRC */
		cmdat |= CMD_DAT_CONT_RESPONSE_136BIT;
		break;
	case MMC_RSP_R3: /* short */
		cmdat |= CMD_DAT_CONT_RESPONSE_48BIT;
		break;
	case MMC_RSP_NONE:
		break;
	default:
		dev_err(mmc_dev(host->mmc), "unhandled response type 0x%x\n",
				mmc_resp_type(cmd));
		cmd->error = -EINVAL;
		return -EINVAL;
	}

	if (mxcmci_use_dma(host))
		writel(INT_READ_OP_EN | INT_WRITE_OP_DONE_EN |
				INT_END_CMD_RES_EN,
				host->base + MMC_REG_INT_CNTR);
	else
		writel(INT_END_CMD_RES_EN, host->base + MMC_REG_INT_CNTR);

	writew(cmd->opcode, host->base + MMC_REG_CMD);
	writel(cmd->arg, host->base + MMC_REG_ARG);
	writew(cmdat, host->base + MMC_REG_CMD_DAT_CONT);

	return 0;
}