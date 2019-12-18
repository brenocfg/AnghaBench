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
struct efx_nic {scalar_t__ phy_type; struct efx_mcdi_phy_data* phy_data; } ;
struct efx_mcdi_phy_data {int flags; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char const**) ; 
 int MC_CMD_GET_PHY_CFG_OUT_BIST_CABLE_LONG_LBN ; 
 int MC_CMD_GET_PHY_CFG_OUT_BIST_CABLE_SHORT_LBN ; 
 int MC_CMD_GET_PHY_CFG_OUT_BIST_LBN ; 
 scalar_t__ PHY_TYPE_SFT9001B ; 
 char const** mcdi_sft9001_cable_diag_names ; 

__attribute__((used)) static const char *efx_mcdi_phy_test_name(struct efx_nic *efx,
					  unsigned int index)
{
	struct efx_mcdi_phy_data *phy_cfg = efx->phy_data;

	if (phy_cfg->flags & (1 << MC_CMD_GET_PHY_CFG_OUT_BIST_LBN)) {
		if (index == 0)
			return "bist";
		--index;
	}

	if (phy_cfg->flags & ((1 << MC_CMD_GET_PHY_CFG_OUT_BIST_CABLE_SHORT_LBN) |
			      (1 << MC_CMD_GET_PHY_CFG_OUT_BIST_CABLE_LONG_LBN))) {
		if (index == 0)
			return "cable";
		--index;

		if (efx->phy_type == PHY_TYPE_SFT9001B) {
			if (index < ARRAY_SIZE(mcdi_sft9001_cable_diag_names))
				return mcdi_sft9001_cable_diag_names[index];
			index -= ARRAY_SIZE(mcdi_sft9001_cable_diag_names);
		}
	}

	return NULL;
}