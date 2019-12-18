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
typedef  int u32 ;
struct efx_nic {int wanted_fc; int /*<<< orphan*/  net_dev; struct efx_mcdi_phy_data* phy_data; } ;
struct efx_mcdi_phy_data {int supported_cap; } ;

/* Variables and functions */
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Pause ; 
 int EFX_FC_AUTO ; 
 int EFX_FC_TX ; 
 int MC_CMD_PHY_CAP_AN_LBN ; 
 int MC_CMD_PHY_CAP_ASYM_LBN ; 
 int MC_CMD_PHY_CAP_PAUSE_LBN ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void efx_mcdi_phy_check_fcntl(struct efx_nic *efx, u32 lpa)
{
	struct efx_mcdi_phy_data *phy_cfg = efx->phy_data;
	u32 rmtadv;

	/* The link partner capabilities are only relevant if the
	 * link supports flow control autonegotiation */
	if (~phy_cfg->supported_cap & (1 << MC_CMD_PHY_CAP_AN_LBN))
		return;

	/* If flow control autoneg is supported and enabled, then fine */
	if (efx->wanted_fc & EFX_FC_AUTO)
		return;

	rmtadv = 0;
	if (lpa & (1 << MC_CMD_PHY_CAP_PAUSE_LBN))
		rmtadv |= ADVERTISED_Pause;
	if (lpa & (1 << MC_CMD_PHY_CAP_ASYM_LBN))
		rmtadv |=  ADVERTISED_Asym_Pause;

	if ((efx->wanted_fc & EFX_FC_TX) && rmtadv == ADVERTISED_Asym_Pause)
		netif_err(efx, link, efx->net_dev,
			  "warning: link partner doesn't support pause frames");
}