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
struct pxamci_host {unsigned int cmdat; struct mmc_request* mrq; } ;
struct mmc_request {int /*<<< orphan*/  cmd; TYPE_1__* data; } ;
struct mmc_host {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 unsigned int CMDAT_BUSY ; 
 unsigned int CMDAT_DATAEN ; 
 unsigned int CMDAT_DMAEN ; 
 unsigned int CMDAT_INIT ; 
 unsigned int CMDAT_STREAM ; 
 unsigned int CMDAT_WRITE ; 
 int MMC_DATA_STREAM ; 
 int MMC_DATA_WRITE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct pxamci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  pxamci_setup_data (struct pxamci_host*,TYPE_1__*) ; 
 int /*<<< orphan*/  pxamci_start_cmd (struct pxamci_host*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pxamci_stop_clock (struct pxamci_host*) ; 

__attribute__((used)) static void pxamci_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct pxamci_host *host = mmc_priv(mmc);
	unsigned int cmdat;

	WARN_ON(host->mrq != NULL);

	host->mrq = mrq;

	pxamci_stop_clock(host);

	cmdat = host->cmdat;
	host->cmdat &= ~CMDAT_INIT;

	if (mrq->data) {
		pxamci_setup_data(host, mrq->data);

		cmdat &= ~CMDAT_BUSY;
		cmdat |= CMDAT_DATAEN | CMDAT_DMAEN;
		if (mrq->data->flags & MMC_DATA_WRITE)
			cmdat |= CMDAT_WRITE;

		if (mrq->data->flags & MMC_DATA_STREAM)
			cmdat |= CMDAT_STREAM;
	}

	pxamci_start_cmd(host, mrq->cmd, cmdat);
}