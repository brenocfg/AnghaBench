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
struct mmci_host {int /*<<< orphan*/  sg_ptr; scalar_t__ sg_len; int /*<<< orphan*/  data_xfered; } ;
struct mmc_data {int flags; int /*<<< orphan*/  stop; int /*<<< orphan*/  mrq; int /*<<< orphan*/  error; scalar_t__ blksz; } ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 unsigned int MCI_DATABLOCKEND ; 
 unsigned int MCI_DATACRCFAIL ; 
 unsigned int MCI_DATAEND ; 
 unsigned int MCI_DATATIMEOUT ; 
 unsigned int MCI_RXOVERRUN ; 
 unsigned int MCI_TXUNDERRUN ; 
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  flush_dcache_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmci_request_end (struct mmci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmci_start_command (struct mmci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmci_stop_data (struct mmci_host*) ; 
 int /*<<< orphan*/  sg_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mmci_data_irq(struct mmci_host *host, struct mmc_data *data,
	      unsigned int status)
{
	if (status & MCI_DATABLOCKEND) {
		host->data_xfered += data->blksz;
	}
	if (status & (MCI_DATACRCFAIL|MCI_DATATIMEOUT|MCI_TXUNDERRUN|MCI_RXOVERRUN)) {
		if (status & MCI_DATACRCFAIL)
			data->error = -EILSEQ;
		else if (status & MCI_DATATIMEOUT)
			data->error = -ETIMEDOUT;
		else if (status & (MCI_TXUNDERRUN|MCI_RXOVERRUN))
			data->error = -EIO;
		status |= MCI_DATAEND;

		/*
		 * We hit an error condition.  Ensure that any data
		 * partially written to a page is properly coherent.
		 */
		if (host->sg_len && data->flags & MMC_DATA_READ)
			flush_dcache_page(sg_page(host->sg_ptr));
	}
	if (status & MCI_DATAEND) {
		mmci_stop_data(host);

		if (!data->stop) {
			mmci_request_end(host, data->mrq);
		} else {
			mmci_start_command(host, data->stop, 0);
		}
	}
}