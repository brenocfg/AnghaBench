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
struct tmio_mmc_host {int dummy; } ;
struct mmc_ios {int power_mode; int bus_width; int /*<<< orphan*/  clock; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNF_PWR_CTL_2 ; 
 int /*<<< orphan*/  CTL_SD_MEM_CARD_OPT ; 
#define  MMC_BUS_WIDTH_1 132 
#define  MMC_BUS_WIDTH_4 131 
#define  MMC_POWER_OFF 130 
#define  MMC_POWER_ON 129 
#define  MMC_POWER_UP 128 
 struct tmio_mmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  sd_config_write8 (struct tmio_mmc_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sd_ctrl_write16 (struct tmio_mmc_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tmio_mmc_clk_start (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  tmio_mmc_clk_stop (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  tmio_mmc_set_clock (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void tmio_mmc_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct tmio_mmc_host *host = mmc_priv(mmc);

	if (ios->clock)
		tmio_mmc_set_clock(host, ios->clock);

	/* Power sequence - OFF -> ON -> UP */
	switch (ios->power_mode) {
	case MMC_POWER_OFF: /* power down SD bus */
		sd_config_write8(host, CNF_PWR_CTL_2, 0x00);
		tmio_mmc_clk_stop(host);
		break;
	case MMC_POWER_ON: /* power up SD bus */

		sd_config_write8(host, CNF_PWR_CTL_2, 0x02);
		break;
	case MMC_POWER_UP: /* start bus clock */
		tmio_mmc_clk_start(host);
		break;
	}

	switch (ios->bus_width) {
	case MMC_BUS_WIDTH_1:
		sd_ctrl_write16(host, CTL_SD_MEM_CARD_OPT, 0x80e0);
	break;
	case MMC_BUS_WIDTH_4:
		sd_ctrl_write16(host, CTL_SD_MEM_CARD_OPT, 0x00e0);
	break;
	}

	/* Let things settle. delay taken from winCE driver */
	udelay(140);
}