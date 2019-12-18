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
typedef  int u32 ;

/* Variables and functions */
 int MC_CMD_PHY_CAP_10000FDX_LBN ; 
 int MC_CMD_PHY_CAP_1000FDX_LBN ; 
 int MC_CMD_PHY_CAP_1000HDX_LBN ; 
 int MC_CMD_PHY_CAP_100FDX_LBN ; 
 int MC_CMD_PHY_CAP_100HDX_LBN ; 
 int MC_CMD_PHY_CAP_10FDX_LBN ; 
 int MC_CMD_PHY_CAP_10HDX_LBN ; 
 int MC_CMD_PHY_CAP_AN_LBN ; 
 int MC_CMD_PHY_CAP_ASYM_LBN ; 
 int MC_CMD_PHY_CAP_PAUSE_LBN ; 
 int SUPPORTED_10000baseKX4_Full ; 
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_1000baseKX_Full ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_1000baseT_Half ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_Asym_Pause ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_Pause ; 

__attribute__((used)) static u32 ethtool_to_mcdi_cap(u32 cap)
{
	u32 result = 0;

	if (cap & SUPPORTED_10baseT_Half)
		result |= (1 << MC_CMD_PHY_CAP_10HDX_LBN);
	if (cap & SUPPORTED_10baseT_Full)
		result |= (1 << MC_CMD_PHY_CAP_10FDX_LBN);
	if (cap & SUPPORTED_100baseT_Half)
		result |= (1 << MC_CMD_PHY_CAP_100HDX_LBN);
	if (cap & SUPPORTED_100baseT_Full)
		result |= (1 << MC_CMD_PHY_CAP_100FDX_LBN);
	if (cap & SUPPORTED_1000baseT_Half)
		result |= (1 << MC_CMD_PHY_CAP_1000HDX_LBN);
	if (cap & (SUPPORTED_1000baseT_Full | SUPPORTED_1000baseKX_Full))
		result |= (1 << MC_CMD_PHY_CAP_1000FDX_LBN);
	if (cap & (SUPPORTED_10000baseT_Full | SUPPORTED_10000baseKX4_Full))
		result |= (1 << MC_CMD_PHY_CAP_10000FDX_LBN);
	if (cap & SUPPORTED_Pause)
		result |= (1 << MC_CMD_PHY_CAP_PAUSE_LBN);
	if (cap & SUPPORTED_Asym_Pause)
		result |= (1 << MC_CMD_PHY_CAP_ASYM_LBN);
	if (cap & SUPPORTED_Autoneg)
		result |= (1 << MC_CMD_PHY_CAP_AN_LBN);

	return result;
}