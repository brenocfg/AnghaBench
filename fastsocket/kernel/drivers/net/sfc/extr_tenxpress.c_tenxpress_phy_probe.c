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
struct tenxpress_phy_data {int /*<<< orphan*/  phy_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode_support; int /*<<< orphan*/  mmds; } ;
struct efx_nic {int loopback_modes; int link_advertising; TYPE_1__ mdio; int /*<<< orphan*/  phy_mode; struct tenxpress_phy_data* phy_data; } ;

/* Variables and functions */
 int ADVERTISED_10000baseT_Full ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_TP ; 
 int ENOMEM ; 
 int FALCON_XMAC_LOOPBACKS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MDIO_SUPPORTS_C45 ; 
 int SFX7101_LOOPBACKS ; 
 int /*<<< orphan*/  TENXPRESS_REQUIRED_DEVS ; 
 struct tenxpress_phy_data* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tenxpress_phy_probe(struct efx_nic *efx)
{
	struct tenxpress_phy_data *phy_data;

	/* Allocate phy private storage */
	phy_data = kzalloc(sizeof(*phy_data), GFP_KERNEL);
	if (!phy_data)
		return -ENOMEM;
	efx->phy_data = phy_data;
	phy_data->phy_mode = efx->phy_mode;

	efx->mdio.mmds = TENXPRESS_REQUIRED_DEVS;
	efx->mdio.mode_support = MDIO_SUPPORTS_C45;

	efx->loopback_modes = SFX7101_LOOPBACKS | FALCON_XMAC_LOOPBACKS;

	efx->link_advertising = (ADVERTISED_TP | ADVERTISED_Autoneg |
				 ADVERTISED_10000baseT_Full);

	return 0;
}