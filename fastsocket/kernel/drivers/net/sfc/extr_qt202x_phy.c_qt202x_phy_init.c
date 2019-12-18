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
typedef  int /*<<< orphan*/  u32 ;
struct efx_nic {scalar_t__ phy_type; int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_MMD_PHYXS ; 
 scalar_t__ PHY_TYPE_QT2025C ; 
 int /*<<< orphan*/  efx_mdio_id_model (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_mdio_id_oui (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_mdio_id_rev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_mdio_read_id (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_info (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  qt2025c_firmware_id (struct efx_nic*) ; 
 int qt202x_reset_phy (struct efx_nic*) ; 

__attribute__((used)) static int qt202x_phy_init(struct efx_nic *efx)
{
	u32 devid;
	int rc;

	rc = qt202x_reset_phy(efx);
	if (rc) {
		netif_err(efx, probe, efx->net_dev, "PHY init failed\n");
		return rc;
	}

	devid = efx_mdio_read_id(efx, MDIO_MMD_PHYXS);
	netif_info(efx, probe, efx->net_dev,
		   "PHY ID reg %x (OUI %06x model %02x revision %x)\n",
		   devid, efx_mdio_id_oui(devid), efx_mdio_id_model(devid),
		   efx_mdio_id_rev(devid));

	if (efx->phy_type == PHY_TYPE_QT2025C)
		qt2025c_firmware_id(efx);

	return 0;
}