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
struct ethtool_cmd {int /*<<< orphan*/  autoneg; } ;
struct efx_nic {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int efx_mdio_set_settings (struct efx_nic*,struct ethtool_cmd*) ; 

__attribute__((used)) static int tenxpress_set_settings(struct efx_nic *efx, struct ethtool_cmd *ecmd)
{
	if (!ecmd->autoneg)
		return -EINVAL;

	return efx_mdio_set_settings(efx, ecmd);
}