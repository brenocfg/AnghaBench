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
struct omap_hsmmc_host {int /*<<< orphan*/  mmc; int /*<<< orphan*/  base; int /*<<< orphan*/  dbclk; scalar_t__ got_dbclk; int /*<<< orphan*/  fclk; int /*<<< orphan*/  iclk; int /*<<< orphan*/  slot_id; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int (* set_power ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HCTL ; 
 int MMC_VDD_23_24 ; 
 int OMAP_HSMMC_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OMAP_HSMMC_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int SDVS18 ; 
 int SDVS30 ; 
 int SDVSCLR ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 TYPE_1__ mmc_slot (struct omap_hsmmc_host*) ; 
 int /*<<< orphan*/  set_sd_bus_power (struct omap_hsmmc_host*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int omap_hsmmc_switch_opcond(struct omap_hsmmc_host *host, int vdd)
{
	u32 reg_val = 0;
	int ret;

	/* Disable the clocks */
	clk_disable(host->fclk);
	clk_disable(host->iclk);
	if (host->got_dbclk)
		clk_disable(host->dbclk);

	/* Turn the power off */
	ret = mmc_slot(host).set_power(host->dev, host->slot_id, 0, 0);

	/* Turn the power ON with given VDD 1.8 or 3.0v */
	if (!ret)
		ret = mmc_slot(host).set_power(host->dev, host->slot_id, 1,
					       vdd);
	clk_enable(host->iclk);
	clk_enable(host->fclk);
	if (host->got_dbclk)
		clk_enable(host->dbclk);

	if (ret != 0)
		goto err;

	OMAP_HSMMC_WRITE(host->base, HCTL,
		OMAP_HSMMC_READ(host->base, HCTL) & SDVSCLR);
	reg_val = OMAP_HSMMC_READ(host->base, HCTL);

	/*
	 * If a MMC dual voltage card is detected, the set_ios fn calls
	 * this fn with VDD bit set for 1.8V. Upon card removal from the
	 * slot, omap_hsmmc_set_ios sets the VDD back to 3V on MMC_POWER_OFF.
	 *
	 * Cope with a bit of slop in the range ... per data sheets:
	 *  - "1.8V" for vdds_mmc1/vdds_mmc1a can be up to 2.45V max,
	 *    but recommended values are 1.71V to 1.89V
	 *  - "3.0V" for vdds_mmc1/vdds_mmc1a can be up to 3.5V max,
	 *    but recommended values are 2.7V to 3.3V
	 *
	 * Board setup code shouldn't permit anything very out-of-range.
	 * TWL4030-family VMMC1 and VSIM regulators are fine (avoiding the
	 * middle range) but VSIM can't power DAT4..DAT7 at more than 3V.
	 */
	if ((1 << vdd) <= MMC_VDD_23_24)
		reg_val |= SDVS18;
	else
		reg_val |= SDVS30;

	OMAP_HSMMC_WRITE(host->base, HCTL, reg_val);
	set_sd_bus_power(host);

	return 0;
err:
	dev_dbg(mmc_dev(host->mmc), "Unable to switch operating voltage\n");
	return ret;
}