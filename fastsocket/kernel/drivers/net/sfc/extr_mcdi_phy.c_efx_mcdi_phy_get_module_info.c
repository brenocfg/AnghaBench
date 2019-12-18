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
struct ethtool_modinfo {int /*<<< orphan*/  eeprom_len; int /*<<< orphan*/  type; } ;
struct efx_nic {struct efx_mcdi_phy_data* phy_data; } ;
struct efx_mcdi_phy_data {int media; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8079 ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8079_LEN ; 
#define  MC_CMD_MEDIA_SFP_PLUS 128 

__attribute__((used)) static int efx_mcdi_phy_get_module_info(struct efx_nic *efx,
					struct ethtool_modinfo *modinfo)
{
	struct efx_mcdi_phy_data *phy_cfg = efx->phy_data;

	switch (phy_cfg->media) {
	case MC_CMD_MEDIA_SFP_PLUS:
		modinfo->type = ETH_MODULE_SFF_8079;
		modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}