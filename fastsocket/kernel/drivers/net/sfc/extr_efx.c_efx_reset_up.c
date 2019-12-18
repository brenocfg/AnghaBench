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
struct efx_nic {int port_initialized; int /*<<< orphan*/  mac_lock; TYPE_2__* type; int /*<<< orphan*/  net_dev; TYPE_1__* phy_op; } ;
typedef  enum reset_type { ____Placeholder_reset_type } reset_type ;
struct TYPE_4__ {int (* init ) (struct efx_nic*) ;int /*<<< orphan*/  (* reconfigure_mac ) (struct efx_nic*) ;} ;
struct TYPE_3__ {int (* init ) (struct efx_nic*) ;scalar_t__ (* reconfigure ) (struct efx_nic*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_ASSERT_RESET_SERIALISED (struct efx_nic*) ; 
 int RESET_TYPE_INVISIBLE ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  efx_restore_filters (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_sriov_reset (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_start_all (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_start_interrupts (struct efx_nic*,int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int stub1 (struct efx_nic*) ; 
 int stub2 (struct efx_nic*) ; 
 scalar_t__ stub3 (struct efx_nic*) ; 
 int /*<<< orphan*/  stub4 (struct efx_nic*) ; 

int efx_reset_up(struct efx_nic *efx, enum reset_type method, bool ok)
{
	int rc;

	EFX_ASSERT_RESET_SERIALISED(efx);

	rc = efx->type->init(efx);
	if (rc) {
		netif_err(efx, drv, efx->net_dev, "failed to initialise NIC\n");
		goto fail;
	}

	if (!ok)
		goto fail;

	if (efx->port_initialized && method != RESET_TYPE_INVISIBLE) {
		rc = efx->phy_op->init(efx);
		if (rc)
			goto fail;
		if (efx->phy_op->reconfigure(efx))
			netif_err(efx, drv, efx->net_dev,
				  "could not restore PHY settings\n");
	}

	efx->type->reconfigure_mac(efx);

	efx_start_interrupts(efx, false);
	efx_restore_filters(efx);
	efx_sriov_reset(efx);

	mutex_unlock(&efx->mac_lock);

	efx_start_all(efx);

	return 0;

fail:
	efx->port_initialized = false;
 
	mutex_unlock(&efx->mac_lock);

	return rc;
}