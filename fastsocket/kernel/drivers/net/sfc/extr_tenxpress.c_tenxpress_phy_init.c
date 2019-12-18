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
struct efx_nic {int phy_mode; int /*<<< orphan*/  wanted_fc; } ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* init_phy ) (struct efx_nic*) ;} ;

/* Variables and functions */
 int HZ ; 
 int PHY_MODE_SPECIAL ; 
 int /*<<< orphan*/  TENXPRESS_REQUIRED_DEVS ; 
 int /*<<< orphan*/  efx_link_set_wanted_fc (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_mdio_an_reconfigure (struct efx_nic*) ; 
 int efx_mdio_check_mmds (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int efx_mdio_wait_reset_mmds (struct efx_nic*,int /*<<< orphan*/ ) ; 
 TYPE_2__* falcon_board (struct efx_nic*) ; 
 int /*<<< orphan*/  falcon_reset_xaui (struct efx_nic*) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  stub1 (struct efx_nic*) ; 
 int tenxpress_init (struct efx_nic*) ; 

__attribute__((used)) static int tenxpress_phy_init(struct efx_nic *efx)
{
	int rc;

	falcon_board(efx)->type->init_phy(efx);

	if (!(efx->phy_mode & PHY_MODE_SPECIAL)) {
		rc = efx_mdio_wait_reset_mmds(efx, TENXPRESS_REQUIRED_DEVS);
		if (rc < 0)
			return rc;

		rc = efx_mdio_check_mmds(efx, TENXPRESS_REQUIRED_DEVS);
		if (rc < 0)
			return rc;
	}

	rc = tenxpress_init(efx);
	if (rc < 0)
		return rc;

	/* Reinitialise flow control settings */
	efx_link_set_wanted_fc(efx, efx->wanted_fc);
	efx_mdio_an_reconfigure(efx);

	schedule_timeout_uninterruptible(HZ / 5); /* 200ms */

	/* Let XGXS and SerDes out of reset */
	falcon_reset_xaui(efx);

	return 0;
}