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
struct sdhci_host {int quirks; int /*<<< orphan*/  pwr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  MMC_VDD_165_195 132 
#define  MMC_VDD_29_30 131 
#define  MMC_VDD_30_31 130 
#define  MMC_VDD_32_33 129 
#define  MMC_VDD_33_34 128 
 int /*<<< orphan*/  SDHCI_POWER_180 ; 
 int /*<<< orphan*/  SDHCI_POWER_300 ; 
 int /*<<< orphan*/  SDHCI_POWER_330 ; 
 int /*<<< orphan*/  SDHCI_POWER_CONTROL ; 
 int /*<<< orphan*/  SDHCI_POWER_ON ; 
 int SDHCI_QUIRK_DELAY_AFTER_POWER ; 
 int SDHCI_QUIRK_NO_SIMULT_VDD_AND_POWER ; 
 int SDHCI_QUIRK_SINGLE_POWER_WRITE ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  sdhci_writeb (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_set_power(struct sdhci_host *host, unsigned short power)
{
	u8 pwr;

	if (power == (unsigned short)-1)
		pwr = 0;
	else {
		switch (1 << power) {
		case MMC_VDD_165_195:
			pwr = SDHCI_POWER_180;
			break;
		case MMC_VDD_29_30:
		case MMC_VDD_30_31:
			pwr = SDHCI_POWER_300;
			break;
		case MMC_VDD_32_33:
		case MMC_VDD_33_34:
			pwr = SDHCI_POWER_330;
			break;
		default:
			BUG();
		}
	}

	if (host->pwr == pwr)
		return;

	host->pwr = pwr;

	if (pwr == 0) {
		sdhci_writeb(host, 0, SDHCI_POWER_CONTROL);
		return;
	}

	/*
	 * Spec says that we should clear the power reg before setting
	 * a new value. Some controllers don't seem to like this though.
	 */
	if (!(host->quirks & SDHCI_QUIRK_SINGLE_POWER_WRITE))
		sdhci_writeb(host, 0, SDHCI_POWER_CONTROL);

	/*
	 * At least the Marvell CaFe chip gets confused if we set the voltage
	 * and set turn on power at the same time, so set the voltage first.
	 */
	if (host->quirks & SDHCI_QUIRK_NO_SIMULT_VDD_AND_POWER)
		sdhci_writeb(host, pwr, SDHCI_POWER_CONTROL);

	pwr |= SDHCI_POWER_ON;

	sdhci_writeb(host, pwr, SDHCI_POWER_CONTROL);

	/*
	 * Some controllers need an extra 10ms delay of 10ms before they
	 * can apply clock after applying power
	 */
	if (host->quirks & SDHCI_QUIRK_DELAY_AFTER_POWER)
		mdelay(10);
}