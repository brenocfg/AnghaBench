#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct omap_hsmmc_host {int /*<<< orphan*/  irq_lock; TYPE_2__* mrq; TYPE_3__* cmd; int /*<<< orphan*/  base; struct mmc_data* data; int /*<<< orphan*/  mmc; scalar_t__ response_busy; } ;
struct mmc_data {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int error; int opcode; } ;
struct TYPE_5__ {TYPE_1__* cmd; } ;
struct TYPE_4__ {int error; } ;

/* Variables and functions */
 int CARD_ERR ; 
 int CC ; 
 int CMD_CRC ; 
 int CMD_TIMEOUT ; 
 int DATA_CRC ; 
 int DATA_TIMEOUT ; 
 int EILSEQ ; 
 int ERR ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int OMAP_HSMMC_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OMAP_HSMMC_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SRC ; 
 int /*<<< orphan*/  SRD ; 
 int /*<<< orphan*/  STAT ; 
 int TC ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_hsmmc_cmd_done (struct omap_hsmmc_host*,TYPE_3__*) ; 
 int /*<<< orphan*/  omap_hsmmc_dma_cleanup (struct omap_hsmmc_host*,int) ; 
 int /*<<< orphan*/  omap_hsmmc_report_irq (struct omap_hsmmc_host*,int) ; 
 int /*<<< orphan*/  omap_hsmmc_reset_controller_fsm (struct omap_hsmmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_hsmmc_xfer_done (struct omap_hsmmc_host*,struct mmc_data*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t omap_hsmmc_irq(int irq, void *dev_id)
{
	struct omap_hsmmc_host *host = dev_id;
	struct mmc_data *data;
	int end_cmd = 0, end_trans = 0, status;

	spin_lock(&host->irq_lock);

	if (host->mrq == NULL) {
		OMAP_HSMMC_WRITE(host->base, STAT,
			OMAP_HSMMC_READ(host->base, STAT));
		/* Flush posted write */
		OMAP_HSMMC_READ(host->base, STAT);
		spin_unlock(&host->irq_lock);
		return IRQ_HANDLED;
	}

	data = host->data;
	status = OMAP_HSMMC_READ(host->base, STAT);
	dev_dbg(mmc_dev(host->mmc), "IRQ Status is %x\n", status);

	if (status & ERR) {
#ifdef CONFIG_MMC_DEBUG
		omap_hsmmc_report_irq(host, status);
#endif
		if ((status & CMD_TIMEOUT) ||
			(status & CMD_CRC)) {
			if (host->cmd) {
				if (status & CMD_TIMEOUT) {
					omap_hsmmc_reset_controller_fsm(host,
									SRC);
					host->cmd->error = -ETIMEDOUT;
				} else {
					host->cmd->error = -EILSEQ;
				}
				end_cmd = 1;
			}
			if (host->data || host->response_busy) {
				if (host->data)
					omap_hsmmc_dma_cleanup(host,
								-ETIMEDOUT);
				host->response_busy = 0;
				omap_hsmmc_reset_controller_fsm(host, SRD);
			}
		}
		if ((status & DATA_TIMEOUT) ||
			(status & DATA_CRC)) {
			if (host->data || host->response_busy) {
				int err = (status & DATA_TIMEOUT) ?
						-ETIMEDOUT : -EILSEQ;

				if (host->data)
					omap_hsmmc_dma_cleanup(host, err);
				else
					host->mrq->cmd->error = err;
				host->response_busy = 0;
				omap_hsmmc_reset_controller_fsm(host, SRD);
				end_trans = 1;
			}
		}
		if (status & CARD_ERR) {
			dev_dbg(mmc_dev(host->mmc),
				"Ignoring card err CMD%d\n", host->cmd->opcode);
			if (host->cmd)
				end_cmd = 1;
			if (host->data)
				end_trans = 1;
		}
	}

	OMAP_HSMMC_WRITE(host->base, STAT, status);
	/* Flush posted write */
	OMAP_HSMMC_READ(host->base, STAT);

	if (end_cmd || ((status & CC) && host->cmd))
		omap_hsmmc_cmd_done(host, host->cmd);
	if ((end_trans || (status & TC)) && host->mrq)
		omap_hsmmc_xfer_done(host, data);

	spin_unlock(&host->irq_lock);

	return IRQ_HANDLED;
}