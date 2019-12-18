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
struct mmc_request {TYPE_1__* cmd; } ;
struct imxmci_host {int pending_events; int /*<<< orphan*/  mmc; int /*<<< orphan*/ * data; int /*<<< orphan*/ * cmd; int /*<<< orphan*/ * req; int /*<<< orphan*/  prev_cmd_code; int /*<<< orphan*/  lock; scalar_t__ base; int /*<<< orphan*/  imask; } ;
struct TYPE_2__ {int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMXMCI_INT_MASK_DEFAULT ; 
 int IMXMCI_PEND_CPU_DATA_m ; 
 int IMXMCI_PEND_DMA_DATA_m ; 
 int IMXMCI_PEND_DMA_END_m ; 
 int IMXMCI_PEND_WAIT_RESP_m ; 
 scalar_t__ MMC_REG_INT_MASK ; 
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,struct mmc_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void imxmci_finish_request(struct imxmci_host *host, struct mmc_request *req)
{
	unsigned long flags;

	spin_lock_irqsave(&host->lock, flags);

	host->pending_events &= ~(IMXMCI_PEND_WAIT_RESP_m | IMXMCI_PEND_DMA_END_m |
				  IMXMCI_PEND_DMA_DATA_m | IMXMCI_PEND_CPU_DATA_m);

	host->imask = IMXMCI_INT_MASK_DEFAULT;
	writew(host->imask, host->base + MMC_REG_INT_MASK);

	spin_unlock_irqrestore(&host->lock, flags);

	if (req && req->cmd)
		host->prev_cmd_code = req->cmd->opcode;

	host->req = NULL;
	host->cmd = NULL;
	host->data = NULL;
	mmc_request_done(host->mmc, req);
}