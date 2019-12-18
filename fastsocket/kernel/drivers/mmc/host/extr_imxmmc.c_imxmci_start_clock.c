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
typedef  int u16 ;
struct imxmci_host {int /*<<< orphan*/  mmc; scalar_t__ base; int /*<<< orphan*/  pending_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMXMCI_PEND_STARTED_b ; 
 scalar_t__ MMC_REG_STATUS ; 
 scalar_t__ MMC_REG_STR_STP_CLK ; 
 int STATUS_CARD_BUS_CLK_RUN ; 
 int STR_STP_CLK_START_CLK ; 
 int STR_STP_CLK_STOP_CLK ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int readw (scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int imxmci_start_clock(struct imxmci_host *host)
{
	unsigned int trials = 0;
	unsigned int delay_limit = 128;
	unsigned long flags;
	u16 reg;

	reg = readw(host->base + MMC_REG_STR_STP_CLK);
	writew(reg & ~STR_STP_CLK_STOP_CLK, host->base + MMC_REG_STR_STP_CLK);

	clear_bit(IMXMCI_PEND_STARTED_b, &host->pending_events);

	/*
	 * Command start of the clock, this usually succeeds in less
	 * then 6 delay loops, but during card detection (low clockrate)
	 * it takes up to 5000 delay loops and sometimes fails for the first time
	 */
	reg = readw(host->base + MMC_REG_STR_STP_CLK);
	writew(reg | STR_STP_CLK_START_CLK, host->base + MMC_REG_STR_STP_CLK);

	do {
		unsigned int delay = delay_limit;

		while (delay--) {
			reg = readw(host->base + MMC_REG_STATUS);
			if (reg & STATUS_CARD_BUS_CLK_RUN)
				/* Check twice before cut */
				reg = readw(host->base + MMC_REG_STATUS);
				if (reg & STATUS_CARD_BUS_CLK_RUN)
					return 0;

			if (test_bit(IMXMCI_PEND_STARTED_b, &host->pending_events))
				return 0;
		}

		local_irq_save(flags);
		/*
		 * Ensure, that request is not doubled under all possible circumstances.
		 * It is possible, that cock running state is missed, because some other
		 * IRQ or schedule delays this function execution and the clocks has
		 * been already stopped by other means (response processing, SDHC HW)
		 */
		if (!test_bit(IMXMCI_PEND_STARTED_b, &host->pending_events)) {
			reg = readw(host->base + MMC_REG_STR_STP_CLK);
			writew(reg | STR_STP_CLK_START_CLK,
					host->base + MMC_REG_STR_STP_CLK);
		}
		local_irq_restore(flags);

	} while (++trials < 256);

	dev_err(mmc_dev(host->mmc), "imxmci_start_clock blocked, no luck\n");

	return -1;
}