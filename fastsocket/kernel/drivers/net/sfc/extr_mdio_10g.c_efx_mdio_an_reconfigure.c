#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mmds; } ;
struct efx_nic {int link_advertising; TYPE_1__* phy_op; TYPE_2__ mdio; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_npage_adv ) (struct efx_nic*,int) ;} ;

/* Variables and functions */
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Pause ; 
 int ADVERTISE_CSMA ; 
 int ADVERTISE_PAUSE_ASYM ; 
 int ADVERTISE_PAUSE_CAP ; 
 int ADVERTISE_RESV ; 
 int /*<<< orphan*/  MDIO_AN_ADVERTISE ; 
 int MDIO_AN_CTRL1_ENABLE ; 
 int MDIO_AN_CTRL1_RESTART ; 
 int MDIO_AN_CTRL1_XNP ; 
 int /*<<< orphan*/  MDIO_CTRL1 ; 
 int MDIO_DEVS_AN ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int efx_mdio_read (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_mdio_write (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct efx_nic*,int) ; 

void efx_mdio_an_reconfigure(struct efx_nic *efx)
{
	int reg;

	WARN_ON(!(efx->mdio.mmds & MDIO_DEVS_AN));

	/* Set up the base page */
	reg = ADVERTISE_CSMA | ADVERTISE_RESV;
	if (efx->link_advertising & ADVERTISED_Pause)
		reg |= ADVERTISE_PAUSE_CAP;
	if (efx->link_advertising & ADVERTISED_Asym_Pause)
		reg |= ADVERTISE_PAUSE_ASYM;
	efx_mdio_write(efx, MDIO_MMD_AN, MDIO_AN_ADVERTISE, reg);

	/* Set up the (extended) next page */
	efx->phy_op->set_npage_adv(efx, efx->link_advertising);

	/* Enable and restart AN */
	reg = efx_mdio_read(efx, MDIO_MMD_AN, MDIO_CTRL1);
	reg |= MDIO_AN_CTRL1_ENABLE | MDIO_AN_CTRL1_RESTART | MDIO_AN_CTRL1_XNP;
	efx_mdio_write(efx, MDIO_MMD_AN, MDIO_CTRL1, reg);
}