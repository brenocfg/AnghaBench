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
struct efx_nic {scalar_t__ phy_type; int /*<<< orphan*/  net_dev; } ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* init_phy ) (struct efx_nic*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_MMD_PHYXS ; 
 scalar_t__ PHY_TYPE_QT2025C ; 
 int QT2022C2_MAX_RESET_TIME ; 
 int QT2022C2_RESET_WAIT ; 
 int efx_mdio_reset_mmd (struct efx_nic*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* falcon_board (struct efx_nic*) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int qt2025c_wait_reset (struct efx_nic*) ; 
 int /*<<< orphan*/  stub1 (struct efx_nic*) ; 

__attribute__((used)) static int qt202x_reset_phy(struct efx_nic *efx)
{
	int rc;

	if (efx->phy_type == PHY_TYPE_QT2025C) {
		/* Wait for the reset triggered by falcon_reset_hw()
		 * to complete */
		rc = qt2025c_wait_reset(efx);
		if (rc < 0)
			goto fail;
	} else {
		/* Reset the PHYXS MMD. This is documented as doing
		 * a complete soft reset. */
		rc = efx_mdio_reset_mmd(efx, MDIO_MMD_PHYXS,
					QT2022C2_MAX_RESET_TIME /
					QT2022C2_RESET_WAIT,
					QT2022C2_RESET_WAIT);
		if (rc < 0)
			goto fail;
	}

	/* Wait 250ms for the PHY to complete bootup */
	msleep(250);

	falcon_board(efx)->type->init_phy(efx);

	return 0;

 fail:
	netif_err(efx, hw, efx->net_dev, "PHY reset timed out\n");
	return rc;
}