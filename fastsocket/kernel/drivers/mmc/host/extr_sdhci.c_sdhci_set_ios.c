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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct sdhci_host {int flags; scalar_t__ version; unsigned int clock; int quirks; int /*<<< orphan*/  lock; } ;
struct mmc_ios {scalar_t__ power_mode; unsigned int clock; int vdd; scalar_t__ bus_width; scalar_t__ timing; scalar_t__ drv_type; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 scalar_t__ MMC_BUS_WIDTH_4 ; 
 scalar_t__ MMC_BUS_WIDTH_8 ; 
 scalar_t__ MMC_POWER_OFF ; 
 scalar_t__ MMC_SET_DRIVER_TYPE_A ; 
 scalar_t__ MMC_SET_DRIVER_TYPE_C ; 
 scalar_t__ MMC_TIMING_SD_HS ; 
 scalar_t__ MMC_TIMING_UHS_DDR50 ; 
 scalar_t__ MMC_TIMING_UHS_SDR104 ; 
 scalar_t__ MMC_TIMING_UHS_SDR12 ; 
 scalar_t__ MMC_TIMING_UHS_SDR25 ; 
 scalar_t__ MMC_TIMING_UHS_SDR50 ; 
 int SDHCI_CLOCK_CARD_EN ; 
 int /*<<< orphan*/  SDHCI_CLOCK_CONTROL ; 
 int /*<<< orphan*/  SDHCI_CTRL_4BITBUS ; 
 int /*<<< orphan*/  SDHCI_CTRL_8BITBUS ; 
 int SDHCI_CTRL_DRV_TYPE_A ; 
 int SDHCI_CTRL_DRV_TYPE_C ; 
 int SDHCI_CTRL_DRV_TYPE_MASK ; 
 int /*<<< orphan*/  SDHCI_CTRL_HISPD ; 
 int SDHCI_CTRL_PRESET_VAL_ENABLE ; 
 int SDHCI_CTRL_UHS_DDR50 ; 
 int SDHCI_CTRL_UHS_MASK ; 
 int SDHCI_CTRL_UHS_SDR104 ; 
 int SDHCI_CTRL_UHS_SDR12 ; 
 int SDHCI_CTRL_UHS_SDR25 ; 
 int SDHCI_CTRL_UHS_SDR50 ; 
 int SDHCI_DEVICE_DEAD ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL2 ; 
 int SDHCI_QUIRK_RESET_CMD_DATA_ON_IOS ; 
 int SDHCI_RESET_CMD ; 
 int SDHCI_RESET_DATA ; 
 int /*<<< orphan*/  SDHCI_SIGNAL_ENABLE ; 
 scalar_t__ SDHCI_SPEC_300 ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  sdhci_readb (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_reinit (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_reset (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  sdhci_set_clock (struct sdhci_host*,unsigned int) ; 
 int /*<<< orphan*/  sdhci_set_power (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  sdhci_writeb (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sdhci_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct sdhci_host *host;
	unsigned long flags;
	u8 ctrl;

	host = mmc_priv(mmc);

	spin_lock_irqsave(&host->lock, flags);

	if (host->flags & SDHCI_DEVICE_DEAD)
		goto out;

	/*
	 * Reset the chip on each power off.
	 * Should clear out any weird states.
	 */
	if (ios->power_mode == MMC_POWER_OFF) {
		sdhci_writel(host, 0, SDHCI_SIGNAL_ENABLE);
		sdhci_reinit(host);
	}

	sdhci_set_clock(host, ios->clock);

	if (ios->power_mode == MMC_POWER_OFF)
		sdhci_set_power(host, -1);
	else
		sdhci_set_power(host, ios->vdd);

	ctrl = sdhci_readb(host, SDHCI_HOST_CONTROL);

	if (ios->bus_width == MMC_BUS_WIDTH_8)
		ctrl |= SDHCI_CTRL_8BITBUS;
	else
		ctrl &= ~SDHCI_CTRL_8BITBUS;

	if (ios->bus_width == MMC_BUS_WIDTH_4)
		ctrl |= SDHCI_CTRL_4BITBUS;
	else
		ctrl &= ~SDHCI_CTRL_4BITBUS;

	if (ios->timing == MMC_TIMING_SD_HS)
		ctrl |= SDHCI_CTRL_HISPD;
	else
		ctrl &= ~SDHCI_CTRL_HISPD;

	if (host->version >= SDHCI_SPEC_300) {
		u16 clk, ctrl_2;
		unsigned int clock;

		/* In case of UHS-I modes, set High Speed Enable */
		if ((ios->timing == MMC_TIMING_UHS_SDR50) ||
		    (ios->timing == MMC_TIMING_UHS_SDR104) ||
		    (ios->timing == MMC_TIMING_UHS_DDR50) ||
		    (ios->timing == MMC_TIMING_UHS_SDR25))
			ctrl |= SDHCI_CTRL_HISPD;

		ctrl_2 = sdhci_readw(host, SDHCI_HOST_CONTROL2);
		if (!(ctrl_2 & SDHCI_CTRL_PRESET_VAL_ENABLE)) {
			sdhci_writeb(host, ctrl, SDHCI_HOST_CONTROL);
			/*
			 * We only need to set Driver Strength if the
			 * preset value enable is not set.
			 */
			ctrl_2 &= ~SDHCI_CTRL_DRV_TYPE_MASK;
			if (ios->drv_type == MMC_SET_DRIVER_TYPE_A)
				ctrl_2 |= SDHCI_CTRL_DRV_TYPE_A;
			else if (ios->drv_type == MMC_SET_DRIVER_TYPE_C)
				ctrl_2 |= SDHCI_CTRL_DRV_TYPE_C;

			sdhci_writew(host, ctrl_2, SDHCI_HOST_CONTROL2);
		} else {
			/*
			 * According to SDHC Spec v3.00, if the Preset Value
			 * Enable in the Host Control 2 register is set, we
			 * need to reset SD Clock Enable before changing High
			 * Speed Enable to avoid generating clock gliches.
			 */

			/* Reset SD Clock Enable */
			clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
			clk &= ~SDHCI_CLOCK_CARD_EN;
			sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);

			sdhci_writeb(host, ctrl, SDHCI_HOST_CONTROL);

			/* Re-enable SD Clock */
			clock = host->clock;
			host->clock = 0;
			sdhci_set_clock(host, clock);
		}

		ctrl_2 = sdhci_readw(host, SDHCI_HOST_CONTROL2);

		/* Select Bus Speed Mode for host */
		ctrl_2 &= ~SDHCI_CTRL_UHS_MASK;
		if (ios->timing == MMC_TIMING_UHS_SDR12)
			ctrl_2 |= SDHCI_CTRL_UHS_SDR12;
		else if (ios->timing == MMC_TIMING_UHS_SDR25)
			ctrl_2 |= SDHCI_CTRL_UHS_SDR25;
		else if (ios->timing == MMC_TIMING_UHS_SDR50)
			ctrl_2 |= SDHCI_CTRL_UHS_SDR50;
		else if (ios->timing == MMC_TIMING_UHS_SDR104)
			ctrl_2 |= SDHCI_CTRL_UHS_SDR104;
		else if (ios->timing == MMC_TIMING_UHS_DDR50)
			ctrl_2 |= SDHCI_CTRL_UHS_DDR50;

		/* Reset SD Clock Enable */
		clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
		clk &= ~SDHCI_CLOCK_CARD_EN;
		sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);

		sdhci_writew(host, ctrl_2, SDHCI_HOST_CONTROL2);

		/* Re-enable SD Clock */
		clock = host->clock;
		host->clock = 0;
		sdhci_set_clock(host, clock);
	} else
		sdhci_writeb(host, ctrl, SDHCI_HOST_CONTROL);

	/*
	 * Some (ENE) controllers go apeshit on some ios operation,
	 * signalling timeout and CRC errors even on CMD0. Resetting
	 * it on each ios seems to solve the problem.
	 */
	if(host->quirks & SDHCI_QUIRK_RESET_CMD_DATA_ON_IOS)
		sdhci_reset(host, SDHCI_RESET_CMD | SDHCI_RESET_DATA);

out:
	mmiowb();
	spin_unlock_irqrestore(&host->lock, flags);
}