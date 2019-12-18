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
struct efx_nic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int PMA_PMD_EXT_SSR_LBN ; 
 int /*<<< orphan*/  PMA_PMD_XCONTROL_REG ; 
 int /*<<< orphan*/  TENXPRESS_REQUIRED_DEVS ; 
 int efx_mdio_read (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int efx_mdio_wait_reset_mmds (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_mdio_write (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  falcon_start_nic_stats (struct efx_nic*) ; 
 int /*<<< orphan*/  falcon_stop_nic_stats (struct efx_nic*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int tenxpress_init (struct efx_nic*) ; 

__attribute__((used)) static int tenxpress_special_reset(struct efx_nic *efx)
{
	int rc, reg;

	/* The XGMAC clock is driven from the SFX7101 312MHz clock, so
	 * a special software reset can glitch the XGMAC sufficiently for stats
	 * requests to fail. */
	falcon_stop_nic_stats(efx);

	/* Initiate reset */
	reg = efx_mdio_read(efx, MDIO_MMD_PMAPMD, PMA_PMD_XCONTROL_REG);
	reg |= (1 << PMA_PMD_EXT_SSR_LBN);
	efx_mdio_write(efx, MDIO_MMD_PMAPMD, PMA_PMD_XCONTROL_REG, reg);

	mdelay(200);

	/* Wait for the blocks to come out of reset */
	rc = efx_mdio_wait_reset_mmds(efx, TENXPRESS_REQUIRED_DEVS);
	if (rc < 0)
		goto out;

	/* Try and reconfigure the device */
	rc = tenxpress_init(efx);
	if (rc < 0)
		goto out;

	/* Wait for the XGXS state machine to churn */
	mdelay(10);
out:
	falcon_start_nic_stats(efx);
	return rc;
}