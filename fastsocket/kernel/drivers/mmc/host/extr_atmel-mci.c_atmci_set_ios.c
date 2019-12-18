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
typedef  int u32 ;
struct mmc_ios {int bus_width; int power_mode; scalar_t__ clock; } ;
struct mmc_host {int /*<<< orphan*/  class_dev; } ;
struct atmel_mci_slot {int /*<<< orphan*/  flags; scalar_t__ clock; int /*<<< orphan*/  sdc_reg; struct atmel_mci* host; } ;
struct atmel_mci {int mode_reg; int bus_hz; int need_clock_update; int /*<<< orphan*/  lock; int /*<<< orphan*/  mck; TYPE_1__** slot; int /*<<< orphan*/  queue; } ;
struct TYPE_2__ {unsigned int clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMCI_CARD_NEED_INIT ; 
 unsigned int ATMEL_MCI_MAX_NR_SLOTS ; 
 int /*<<< orphan*/  CR ; 
 int DIV_ROUND_UP (int,int) ; 
 int MCI_CR_MCIDIS ; 
 int MCI_CR_MCIEN ; 
 int MCI_CR_SWRST ; 
 int MCI_MR_CLKDIV (int) ; 
 int MCI_MR_RDPROOF ; 
 int MCI_MR_WRPROOF ; 
 int /*<<< orphan*/  MCI_SDCBUS_1BIT ; 
 int /*<<< orphan*/  MCI_SDCBUS_4BIT ; 
 int /*<<< orphan*/  MCI_SDCBUS_MASK ; 
#define  MMC_BUS_WIDTH_1 130 
#define  MMC_BUS_WIDTH_4 129 
#define  MMC_POWER_UP 128 
 int /*<<< orphan*/  MR ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,unsigned int,int) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ mci_has_rwproof () ; 
 int /*<<< orphan*/  mci_readl (struct atmel_mci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mci_writel (struct atmel_mci*,int /*<<< orphan*/ ,int) ; 
 struct atmel_mci_slot* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atmci_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct atmel_mci_slot	*slot = mmc_priv(mmc);
	struct atmel_mci	*host = slot->host;
	unsigned int		i;

	slot->sdc_reg &= ~MCI_SDCBUS_MASK;
	switch (ios->bus_width) {
	case MMC_BUS_WIDTH_1:
		slot->sdc_reg |= MCI_SDCBUS_1BIT;
		break;
	case MMC_BUS_WIDTH_4:
		slot->sdc_reg |= MCI_SDCBUS_4BIT;
		break;
	}

	if (ios->clock) {
		unsigned int clock_min = ~0U;
		u32 clkdiv;

		spin_lock_bh(&host->lock);
		if (!host->mode_reg) {
			clk_enable(host->mck);
			mci_writel(host, CR, MCI_CR_SWRST);
			mci_writel(host, CR, MCI_CR_MCIEN);
		}

		/*
		 * Use mirror of ios->clock to prevent race with mmc
		 * core ios update when finding the minimum.
		 */
		slot->clock = ios->clock;
		for (i = 0; i < ATMEL_MCI_MAX_NR_SLOTS; i++) {
			if (host->slot[i] && host->slot[i]->clock
					&& host->slot[i]->clock < clock_min)
				clock_min = host->slot[i]->clock;
		}

		/* Calculate clock divider */
		clkdiv = DIV_ROUND_UP(host->bus_hz, 2 * clock_min) - 1;
		if (clkdiv > 255) {
			dev_warn(&mmc->class_dev,
				"clock %u too slow; using %lu\n",
				clock_min, host->bus_hz / (2 * 256));
			clkdiv = 255;
		}

		host->mode_reg = MCI_MR_CLKDIV(clkdiv);

		/*
		 * WRPROOF and RDPROOF prevent overruns/underruns by
		 * stopping the clock when the FIFO is full/empty.
		 * This state is not expected to last for long.
		 */
		if (mci_has_rwproof())
			host->mode_reg |= (MCI_MR_WRPROOF | MCI_MR_RDPROOF);

		if (list_empty(&host->queue))
			mci_writel(host, MR, host->mode_reg);
		else
			host->need_clock_update = true;

		spin_unlock_bh(&host->lock);
	} else {
		bool any_slot_active = false;

		spin_lock_bh(&host->lock);
		slot->clock = 0;
		for (i = 0; i < ATMEL_MCI_MAX_NR_SLOTS; i++) {
			if (host->slot[i] && host->slot[i]->clock) {
				any_slot_active = true;
				break;
			}
		}
		if (!any_slot_active) {
			mci_writel(host, CR, MCI_CR_MCIDIS);
			if (host->mode_reg) {
				mci_readl(host, MR);
				clk_disable(host->mck);
			}
			host->mode_reg = 0;
		}
		spin_unlock_bh(&host->lock);
	}

	switch (ios->power_mode) {
	case MMC_POWER_UP:
		set_bit(ATMCI_CARD_NEED_INIT, &slot->flags);
		break;
	default:
		/*
		 * TODO: None of the currently available AVR32-based
		 * boards allow MMC power to be turned off. Implement
		 * power control when this can be tested properly.
		 *
		 * We also need to hook this into the clock management
		 * somehow so that newly inserted cards aren't
		 * subjected to a fast clock before we have a chance
		 * to figure out what the maximum rate is. Currently,
		 * there's no way to avoid this, and there never will
		 * be for boards that don't support power control.
		 */
		break;
	}
}