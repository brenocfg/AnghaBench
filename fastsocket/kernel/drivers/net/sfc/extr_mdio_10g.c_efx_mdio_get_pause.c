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
typedef  int u8 ;
struct TYPE_2__ {int mmds; } ;
struct efx_nic {int wanted_fc; TYPE_1__ mdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EFX_FC_AUTO ; 
 int EFX_FC_RX ; 
 int EFX_FC_TX ; 
 int /*<<< orphan*/  MDIO_AN_LPA ; 
 int MDIO_DEVS_AN ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  efx_mdio_read (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_advertise_flowctrl (int) ; 
 int mii_resolve_flowctrl_fdx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u8 efx_mdio_get_pause(struct efx_nic *efx)
{
	BUILD_BUG_ON(EFX_FC_AUTO & (EFX_FC_RX | EFX_FC_TX));

	if (!(efx->wanted_fc & EFX_FC_AUTO))
		return efx->wanted_fc;

	WARN_ON(!(efx->mdio.mmds & MDIO_DEVS_AN));

	return mii_resolve_flowctrl_fdx(
		mii_advertise_flowctrl(efx->wanted_fc),
		efx_mdio_read(efx, MDIO_MMD_AN, MDIO_AN_LPA));
}