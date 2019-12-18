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
typedef  int /*<<< orphan*/  u8 ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int type; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722 130 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727 129 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT 128 
 int /*<<< orphan*/  bnx2x_8727_power_module (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_warpcore_power_module (struct link_params*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_power_sfp_module(struct link_params *params,
				   struct bnx2x_phy *phy,
				   u8 power)
{
	struct bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "Setting SFP+ power to %x\n", power);

	switch (phy->type) {
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727:
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722:
		bnx2x_8727_power_module(params->bp, phy, power);
		break;
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT:
		bnx2x_warpcore_power_module(params, power);
		break;
	default:
		break;
	}
}