#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct at91mci_host {int /*<<< orphan*/  mmc; TYPE_2__* request; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {TYPE_1__* data; } ;
struct TYPE_3__ {int blocks; } ;

/* Variables and functions */
 unsigned int AT91_MCI_BLKE ; 
 unsigned int AT91_MCI_CMDRDY ; 
 unsigned int AT91_MCI_DCRCE ; 
 unsigned int AT91_MCI_DTIP ; 
 unsigned int AT91_MCI_DTOE ; 
 unsigned int AT91_MCI_ENDRX ; 
 unsigned int AT91_MCI_ENDTX ; 
 unsigned int AT91_MCI_ERRORS ; 
 int /*<<< orphan*/  AT91_MCI_IDR ; 
 int /*<<< orphan*/  AT91_MCI_IER ; 
 int /*<<< orphan*/  AT91_MCI_IMR ; 
 unsigned int AT91_MCI_NOTBUSY ; 
 unsigned int AT91_MCI_OVRE ; 
 unsigned int AT91_MCI_RCRCE ; 
 unsigned int AT91_MCI_RDIRE ; 
 unsigned int AT91_MCI_RENDE ; 
 unsigned int AT91_MCI_RINDE ; 
 unsigned int AT91_MCI_RTOE ; 
 unsigned int AT91_MCI_RXBUFF ; 
 unsigned int AT91_MCI_RXRDY ; 
 unsigned int AT91_MCI_SDIOIRQA ; 
 unsigned int AT91_MCI_SDIOIRQB ; 
 int /*<<< orphan*/  AT91_MCI_SR ; 
 unsigned int AT91_MCI_TXBUFE ; 
 unsigned int AT91_MCI_TXRDY ; 
 unsigned int AT91_MCI_UNRE ; 
 int /*<<< orphan*/  ATMEL_PDC_PTCR ; 
 unsigned int ATMEL_PDC_RXTDIS ; 
 unsigned int ATMEL_PDC_TXTDIS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  at91_mci_completed_command (struct at91mci_host*,unsigned int) ; 
 int at91_mci_handle_cmdrdy (struct at91mci_host*) ; 
 int /*<<< orphan*/  at91_mci_handle_transmitted (struct at91mci_host*) ; 
 int /*<<< orphan*/  at91_mci_post_dma_read (struct at91mci_host*) ; 
 unsigned int at91_mci_read (struct at91mci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_mci_update_bytes_xfered (struct at91mci_host*) ; 
 int /*<<< orphan*/  at91_mci_write (struct at91mci_host*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mmc_signal_sdio_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static irqreturn_t at91_mci_irq(int irq, void *devid)
{
	struct at91mci_host *host = devid;
	int completed = 0;
	unsigned int int_status, int_mask;

	int_status = at91_mci_read(host, AT91_MCI_SR);
	int_mask = at91_mci_read(host, AT91_MCI_IMR);

	pr_debug("MCI irq: status = %08X, %08X, %08X\n", int_status, int_mask,
		int_status & int_mask);

	int_status = int_status & int_mask;

	if (int_status & AT91_MCI_ERRORS) {
		completed = 1;

		if (int_status & AT91_MCI_UNRE)
			pr_debug("MMC: Underrun error\n");
		if (int_status & AT91_MCI_OVRE)
			pr_debug("MMC: Overrun error\n");
		if (int_status & AT91_MCI_DTOE)
			pr_debug("MMC: Data timeout\n");
		if (int_status & AT91_MCI_DCRCE)
			pr_debug("MMC: CRC error in data\n");
		if (int_status & AT91_MCI_RTOE)
			pr_debug("MMC: Response timeout\n");
		if (int_status & AT91_MCI_RENDE)
			pr_debug("MMC: Response end bit error\n");
		if (int_status & AT91_MCI_RCRCE)
			pr_debug("MMC: Response CRC error\n");
		if (int_status & AT91_MCI_RDIRE)
			pr_debug("MMC: Response direction error\n");
		if (int_status & AT91_MCI_RINDE)
			pr_debug("MMC: Response index error\n");
	} else {
		/* Only continue processing if no errors */

		if (int_status & AT91_MCI_TXBUFE) {
			pr_debug("TX buffer empty\n");
			at91_mci_handle_transmitted(host);
		}

		if (int_status & AT91_MCI_ENDRX) {
			pr_debug("ENDRX\n");
			at91_mci_post_dma_read(host);
		}

		if (int_status & AT91_MCI_RXBUFF) {
			pr_debug("RX buffer full\n");
			at91_mci_write(host, ATMEL_PDC_PTCR, ATMEL_PDC_RXTDIS | ATMEL_PDC_TXTDIS);
			at91_mci_write(host, AT91_MCI_IDR, AT91_MCI_RXBUFF | AT91_MCI_ENDRX);
			completed = 1;
		}

		if (int_status & AT91_MCI_ENDTX)
			pr_debug("Transmit has ended\n");

		if (int_status & AT91_MCI_NOTBUSY) {
			pr_debug("Card is ready\n");
			at91_mci_update_bytes_xfered(host);
			completed = 1;
		}

		if (int_status & AT91_MCI_DTIP)
			pr_debug("Data transfer in progress\n");

		if (int_status & AT91_MCI_BLKE) {
			pr_debug("Block transfer has ended\n");
			if (host->request->data && host->request->data->blocks > 1) {
				/* multi block write : complete multi write
				 * command and send stop */
				completed = 1;
			} else {
				at91_mci_write(host, AT91_MCI_IER, AT91_MCI_NOTBUSY);
			}
		}

		if (int_status & AT91_MCI_SDIOIRQA)
			mmc_signal_sdio_irq(host->mmc);

		if (int_status & AT91_MCI_SDIOIRQB)
			mmc_signal_sdio_irq(host->mmc);

		if (int_status & AT91_MCI_TXRDY)
			pr_debug("Ready to transmit\n");

		if (int_status & AT91_MCI_RXRDY)
			pr_debug("Ready to receive\n");

		if (int_status & AT91_MCI_CMDRDY) {
			pr_debug("Command ready\n");
			completed = at91_mci_handle_cmdrdy(host);
		}
	}

	if (completed) {
		pr_debug("Completed command\n");
		at91_mci_write(host, AT91_MCI_IDR, 0xffffffff & ~(AT91_MCI_SDIOIRQA | AT91_MCI_SDIOIRQB));
		at91_mci_completed_command(host, int_status);
	} else
		at91_mci_write(host, AT91_MCI_IDR, int_status & ~(AT91_MCI_SDIOIRQA | AT91_MCI_SDIOIRQB));

	return IRQ_HANDLED;
}