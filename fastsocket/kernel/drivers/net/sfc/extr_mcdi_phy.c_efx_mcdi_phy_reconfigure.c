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
struct efx_nic {int /*<<< orphan*/  loopback_mode; scalar_t__ link_advertising; struct efx_mcdi_phy_data* phy_data; } ;
struct efx_mcdi_phy_data {int /*<<< orphan*/  forced_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  efx_get_mcdi_phy_flags (struct efx_nic*) ; 
 int efx_mcdi_set_link (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethtool_to_mcdi_cap (scalar_t__) ; 

int efx_mcdi_phy_reconfigure(struct efx_nic *efx)
{
	struct efx_mcdi_phy_data *phy_cfg = efx->phy_data;
	u32 caps = (efx->link_advertising ?
		    ethtool_to_mcdi_cap(efx->link_advertising) :
		    phy_cfg->forced_cap);

	return efx_mcdi_set_link(efx, caps, efx_get_mcdi_phy_flags(efx),
				 efx->loopback_mode, 0);
}