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
struct TYPE_2__ {int /*<<< orphan*/  byte; } ;
struct efx_nic {TYPE_1__ multicast_hash; int /*<<< orphan*/  mac_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC_CMD_SET_MCAST_HASH ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int efx_mcdi_rpc (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int efx_mcdi_set_mac (struct efx_nic*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

int efx_mcdi_mac_reconfigure(struct efx_nic *efx)
{
	int rc;

	WARN_ON(!mutex_is_locked(&efx->mac_lock));

	rc = efx_mcdi_set_mac(efx);
	if (rc != 0)
		return rc;

	return efx_mcdi_rpc(efx, MC_CMD_SET_MCAST_HASH,
			    efx->multicast_hash.byte,
			    sizeof(efx->multicast_hash),
			    NULL, 0, NULL);
}