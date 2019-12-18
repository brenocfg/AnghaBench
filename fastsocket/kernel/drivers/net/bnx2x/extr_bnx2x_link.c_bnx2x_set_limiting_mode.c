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
typedef  int /*<<< orphan*/  u16 ;
struct link_params {int /*<<< orphan*/  bp; } ;
struct bnx2x_phy {int type; } ;

/* Variables and functions */
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722 131 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8726 130 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727 129 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT 128 
 int /*<<< orphan*/  bnx2x_8726_set_limiting_mode (int /*<<< orphan*/ ,struct bnx2x_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_8727_set_limiting_mode (int /*<<< orphan*/ ,struct bnx2x_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_warpcore_set_limiting_mode (struct link_params*,struct bnx2x_phy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_set_limiting_mode(struct link_params *params,
				    struct bnx2x_phy *phy,
				    u16 edc_mode)
{
	switch (phy->type) {
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8726:
		bnx2x_8726_set_limiting_mode(params->bp, phy, edc_mode);
		break;
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727:
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722:
		bnx2x_8727_set_limiting_mode(params->bp, phy, edc_mode);
		break;
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT:
		bnx2x_warpcore_set_limiting_mode(params, phy, edc_mode);
		break;
	}
}