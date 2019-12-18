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
struct tmio_mmc_host {int /*<<< orphan*/  mmc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_IRQ_MASK ; 
 int /*<<< orphan*/  CTL_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int TMIO_MASK_CMD ; 
 unsigned int TMIO_MASK_IRQ ; 
 unsigned int TMIO_STAT_CARD_INSERT ; 
 unsigned int TMIO_STAT_CARD_REMOVE ; 
 unsigned int TMIO_STAT_DATAEND ; 
 unsigned int TMIO_STAT_RXRDY ; 
 unsigned int TMIO_STAT_TXRQ ; 
 int /*<<< orphan*/  ack_mmc_irqs (struct tmio_mmc_host*,unsigned int) ; 
 int /*<<< orphan*/  disable_mmc_irqs (struct tmio_mmc_host*,unsigned int) ; 
 int /*<<< orphan*/  mmc_detect_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_debug_status (unsigned int) ; 
 unsigned int sd_ctrl_read32 (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmio_mmc_cmd_irq (struct tmio_mmc_host*,unsigned int) ; 
 int /*<<< orphan*/  tmio_mmc_data_irq (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  tmio_mmc_pio_irq (struct tmio_mmc_host*) ; 

__attribute__((used)) static irqreturn_t tmio_mmc_irq(int irq, void *devid)
{
	struct tmio_mmc_host *host = devid;
	unsigned int ireg, irq_mask, status;

	pr_debug("MMC IRQ begin\n");

	status = sd_ctrl_read32(host, CTL_STATUS);
	irq_mask = sd_ctrl_read32(host, CTL_IRQ_MASK);
	ireg = status & TMIO_MASK_IRQ & ~irq_mask;

	pr_debug_status(status);
	pr_debug_status(ireg);

	if (!ireg) {
		disable_mmc_irqs(host, status & ~irq_mask);

		pr_debug("tmio_mmc: Spurious irq, disabling! "
			"0x%08x 0x%08x 0x%08x\n", status, irq_mask, ireg);
		pr_debug_status(status);

		goto out;
	}

	while (ireg) {
		/* Card insert / remove attempts */
		if (ireg & (TMIO_STAT_CARD_INSERT | TMIO_STAT_CARD_REMOVE)) {
			ack_mmc_irqs(host, TMIO_STAT_CARD_INSERT |
				TMIO_STAT_CARD_REMOVE);
			mmc_detect_change(host->mmc, 0);
		}

		/* CRC and other errors */
/*		if (ireg & TMIO_STAT_ERR_IRQ)
 *			handled |= tmio_error_irq(host, irq, stat);
 */

		/* Command completion */
		if (ireg & TMIO_MASK_CMD) {
			ack_mmc_irqs(host, TMIO_MASK_CMD);
			tmio_mmc_cmd_irq(host, status);
		}

		/* Data transfer */
		if (ireg & (TMIO_STAT_RXRDY | TMIO_STAT_TXRQ)) {
			ack_mmc_irqs(host, TMIO_STAT_RXRDY | TMIO_STAT_TXRQ);
			tmio_mmc_pio_irq(host);
		}

		/* Data transfer completion */
		if (ireg & TMIO_STAT_DATAEND) {
			ack_mmc_irqs(host, TMIO_STAT_DATAEND);
			tmio_mmc_data_irq(host);
		}

		/* Check status - keep going until we've handled it all */
		status = sd_ctrl_read32(host, CTL_STATUS);
		irq_mask = sd_ctrl_read32(host, CTL_IRQ_MASK);
		ireg = status & TMIO_MASK_IRQ & ~irq_mask;

		pr_debug("Status at end of loop: %08x\n", status);
		pr_debug_status(status);
	}
	pr_debug("MMC IRQ end\n");

out:
	return IRQ_HANDLED;
}