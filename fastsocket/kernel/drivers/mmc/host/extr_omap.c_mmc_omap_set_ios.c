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
struct mmc_omap_slot {scalar_t__ vdd; int saved_con; int /*<<< orphan*/  bus_mode; int /*<<< orphan*/  id; TYPE_1__* pdata; struct mmc_omap_host* host; } ;
struct mmc_omap_host {int dummy; } ;
struct mmc_ios {scalar_t__ vdd; int power_mode; int /*<<< orphan*/  bus_mode; } ;
struct mmc_host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_bus_mode ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  CON ; 
 int /*<<< orphan*/  IE ; 
#define  MMC_POWER_OFF 130 
#define  MMC_POWER_ON 129 
#define  MMC_POWER_UP 128 
 int OMAP_MMC_READ (struct mmc_omap_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OMAP_MMC_WRITE (struct mmc_omap_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STAT ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 
 int mmc_omap_calc_divisor (struct mmc_host*,struct mmc_ios*) ; 
 int /*<<< orphan*/  mmc_omap_fclk_enable (struct mmc_omap_host*,int) ; 
 int /*<<< orphan*/  mmc_omap_release_slot (struct mmc_omap_slot*,int) ; 
 int /*<<< orphan*/  mmc_omap_select_slot (struct mmc_omap_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_omap_set_power (struct mmc_omap_slot*,int,scalar_t__) ; 
 struct mmc_omap_slot* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void mmc_omap_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct mmc_omap_slot *slot = mmc_priv(mmc);
	struct mmc_omap_host *host = slot->host;
	int i, dsor;
	int clk_enabled;

	mmc_omap_select_slot(slot, 0);

	dsor = mmc_omap_calc_divisor(mmc, ios);

	if (ios->vdd != slot->vdd)
		slot->vdd = ios->vdd;

	clk_enabled = 0;
	switch (ios->power_mode) {
	case MMC_POWER_OFF:
		mmc_omap_set_power(slot, 0, ios->vdd);
		break;
	case MMC_POWER_UP:
		/* Cannot touch dsor yet, just power up MMC */
		mmc_omap_set_power(slot, 1, ios->vdd);
		goto exit;
	case MMC_POWER_ON:
		mmc_omap_fclk_enable(host, 1);
		clk_enabled = 1;
		dsor |= 1 << 11;
		break;
	}

	if (slot->bus_mode != ios->bus_mode) {
		if (slot->pdata->set_bus_mode != NULL)
			slot->pdata->set_bus_mode(mmc_dev(mmc), slot->id,
						  ios->bus_mode);
		slot->bus_mode = ios->bus_mode;
	}

	/* On insanely high arm_per frequencies something sometimes
	 * goes somehow out of sync, and the POW bit is not being set,
	 * which results in the while loop below getting stuck.
	 * Writing to the CON register twice seems to do the trick. */
	for (i = 0; i < 2; i++)
		OMAP_MMC_WRITE(host, CON, dsor);
	slot->saved_con = dsor;
	if (ios->power_mode == MMC_POWER_ON) {
		/* worst case at 400kHz, 80 cycles makes 200 microsecs */
		int usecs = 250;

		/* Send clock cycles, poll completion */
		OMAP_MMC_WRITE(host, IE, 0);
		OMAP_MMC_WRITE(host, STAT, 0xffff);
		OMAP_MMC_WRITE(host, CMD, 1 << 7);
		while (usecs > 0 && (OMAP_MMC_READ(host, STAT) & 1) == 0) {
			udelay(1);
			usecs--;
		}
		OMAP_MMC_WRITE(host, STAT, 1);
	}

exit:
	mmc_omap_release_slot(slot, clk_enabled);
}