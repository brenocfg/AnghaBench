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
struct efx_nic {scalar_t__ loopback_mode; } ;

/* Variables and functions */
 scalar_t__ LOOPBACK_PCS ; 
 scalar_t__ LOOPBACK_PHYXS_WS ; 
 scalar_t__ LOOPBACK_PMAPMD ; 
 int /*<<< orphan*/  MDIO_CTRL1 ; 
 int /*<<< orphan*/  MDIO_MMD_PCS ; 
 int /*<<< orphan*/  MDIO_MMD_PHYXS ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  MDIO_PCS_CTRL1_LOOPBACK ; 
 int /*<<< orphan*/  MDIO_PHYXS_CTRL1_LOOPBACK ; 
 int /*<<< orphan*/  MDIO_PMA_CTRL1_LOOPBACK ; 
 int /*<<< orphan*/  efx_mdio_set_flag (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void efx_mdio_phy_reconfigure(struct efx_nic *efx)
{
	efx_mdio_set_flag(efx, MDIO_MMD_PMAPMD,
			  MDIO_CTRL1, MDIO_PMA_CTRL1_LOOPBACK,
			  efx->loopback_mode == LOOPBACK_PMAPMD);
	efx_mdio_set_flag(efx, MDIO_MMD_PCS,
			  MDIO_CTRL1, MDIO_PCS_CTRL1_LOOPBACK,
			  efx->loopback_mode == LOOPBACK_PCS);
	efx_mdio_set_flag(efx, MDIO_MMD_PHYXS,
			  MDIO_CTRL1, MDIO_PHYXS_CTRL1_LOOPBACK,
			  efx->loopback_mode == LOOPBACK_PHYXS_WS);
}