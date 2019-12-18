#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* check_link ) (struct ixgbe_hw*,int*,int*,int) ;int /*<<< orphan*/  (* get_link_capabilities ) (struct ixgbe_hw*,int*,int*) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {int autoneg_advertised; int type; int /*<<< orphan*/  sfp_type; } ;
struct ixgbe_hw {TYPE_3__ mac; TYPE_1__ phy; } ;
struct ixgbe_adapter {struct ixgbe_hw hw; } ;
struct ethtool_cmd {int duplex; void* port; int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; int /*<<< orphan*/  transceiver; int /*<<< orphan*/  autoneg; } ;
typedef  int ixgbe_link_speed ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISED_10000baseT_Full ; 
 int /*<<< orphan*/  ADVERTISED_1000baseT_Full ; 
 int /*<<< orphan*/  ADVERTISED_100baseT_Full ; 
 int /*<<< orphan*/  ADVERTISED_Autoneg ; 
 int /*<<< orphan*/  ADVERTISED_FIBRE ; 
 int /*<<< orphan*/  ADVERTISED_TP ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int DUPLEX_FULL ; 
#define  IXGBE_LINK_SPEED_100_FULL 160 
#define  IXGBE_LINK_SPEED_10GB_FULL 159 
#define  IXGBE_LINK_SPEED_1GB_FULL 158 
 void* PORT_DA ; 
 void* PORT_FIBRE ; 
 void* PORT_NONE ; 
 void* PORT_OTHER ; 
 void* PORT_TP ; 
 int SPEED_100 ; 
 int SPEED_1000 ; 
 int SPEED_10000 ; 
 int /*<<< orphan*/  SUPPORTED_10000baseT_Full ; 
 int /*<<< orphan*/  SUPPORTED_1000baseT_Full ; 
 int /*<<< orphan*/  SUPPORTED_100baseT_Full ; 
 int /*<<< orphan*/  SUPPORTED_Autoneg ; 
 int /*<<< orphan*/  SUPPORTED_FIBRE ; 
 int /*<<< orphan*/  SUPPORTED_TP ; 
 int /*<<< orphan*/  XCVR_EXTERNAL ; 
 int /*<<< orphan*/  ethtool_cmd_speed_set (struct ethtool_cmd*,int) ; 
#define  ixgbe_phy_aq 157 
#define  ixgbe_phy_cu_unknown 156 
#define  ixgbe_phy_generic 155 
#define  ixgbe_phy_nl 154 
#define  ixgbe_phy_qt 153 
#define  ixgbe_phy_sfp_avago 152 
#define  ixgbe_phy_sfp_ftl 151 
#define  ixgbe_phy_sfp_intel 150 
#define  ixgbe_phy_sfp_passive_tyco 149 
#define  ixgbe_phy_sfp_passive_unknown 148 
#define  ixgbe_phy_sfp_unknown 147 
#define  ixgbe_phy_sfp_unsupported 146 
#define  ixgbe_phy_tn 145 
#define  ixgbe_phy_unknown 144 
#define  ixgbe_phy_xaui 143 
#define  ixgbe_sfp_type_1g_cu_core0 142 
#define  ixgbe_sfp_type_1g_cu_core1 141 
#define  ixgbe_sfp_type_1g_lx_core0 140 
#define  ixgbe_sfp_type_1g_lx_core1 139 
#define  ixgbe_sfp_type_1g_sx_core0 138 
#define  ixgbe_sfp_type_1g_sx_core1 137 
#define  ixgbe_sfp_type_da_cu 136 
#define  ixgbe_sfp_type_da_cu_core0 135 
#define  ixgbe_sfp_type_da_cu_core1 134 
#define  ixgbe_sfp_type_lr 133 
#define  ixgbe_sfp_type_not_present 132 
#define  ixgbe_sfp_type_sr 131 
#define  ixgbe_sfp_type_srlr_core0 130 
#define  ixgbe_sfp_type_srlr_core1 129 
#define  ixgbe_sfp_type_unknown 128 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int*,int*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int*,int*,int) ; 

__attribute__((used)) static int ixgbe_get_settings(struct net_device *netdev,
                              struct ethtool_cmd *ecmd)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	struct ixgbe_hw *hw = &adapter->hw;
	ixgbe_link_speed supported_link;
	u32 link_speed = 0;
	bool autoneg = false;
	bool link_up;

	hw->mac.ops.get_link_capabilities(hw, &supported_link, &autoneg);

	/* set the supported link speeds */
	if (supported_link & IXGBE_LINK_SPEED_10GB_FULL)
		ecmd->supported |= SUPPORTED_10000baseT_Full;
	if (supported_link & IXGBE_LINK_SPEED_1GB_FULL)
		ecmd->supported |= SUPPORTED_1000baseT_Full;
	if (supported_link & IXGBE_LINK_SPEED_100_FULL)
		ecmd->supported |= SUPPORTED_100baseT_Full;

	/* set the advertised speeds */
	if (hw->phy.autoneg_advertised) {
		if (hw->phy.autoneg_advertised & IXGBE_LINK_SPEED_100_FULL)
			ecmd->advertising |= ADVERTISED_100baseT_Full;
		if (hw->phy.autoneg_advertised & IXGBE_LINK_SPEED_10GB_FULL)
			ecmd->advertising |= ADVERTISED_10000baseT_Full;
		if (hw->phy.autoneg_advertised & IXGBE_LINK_SPEED_1GB_FULL)
			ecmd->advertising |= ADVERTISED_1000baseT_Full;
	} else {
		/* default modes in case phy.autoneg_advertised isn't set */
		if (supported_link & IXGBE_LINK_SPEED_10GB_FULL)
			ecmd->advertising |= ADVERTISED_10000baseT_Full;
		if (supported_link & IXGBE_LINK_SPEED_1GB_FULL)
			ecmd->advertising |= ADVERTISED_1000baseT_Full;
		if (supported_link & IXGBE_LINK_SPEED_100_FULL)
			ecmd->advertising |= ADVERTISED_100baseT_Full;
	}

	if (autoneg) {
		ecmd->supported |= SUPPORTED_Autoneg;
		ecmd->advertising |= ADVERTISED_Autoneg;
		ecmd->autoneg = AUTONEG_ENABLE;
	} else
		ecmd->autoneg = AUTONEG_DISABLE;

	ecmd->transceiver = XCVR_EXTERNAL;

	/* Determine the remaining settings based on the PHY type. */
	switch (adapter->hw.phy.type) {
	case ixgbe_phy_tn:
	case ixgbe_phy_aq:
	case ixgbe_phy_cu_unknown:
		ecmd->supported |= SUPPORTED_TP;
		ecmd->advertising |= ADVERTISED_TP;
		ecmd->port = PORT_TP;
		break;
	case ixgbe_phy_qt:
		ecmd->supported |= SUPPORTED_FIBRE;
		ecmd->advertising |= ADVERTISED_FIBRE;
		ecmd->port = PORT_FIBRE;
		break;
	case ixgbe_phy_nl:
	case ixgbe_phy_sfp_passive_tyco:
	case ixgbe_phy_sfp_passive_unknown:
	case ixgbe_phy_sfp_ftl:
	case ixgbe_phy_sfp_avago:
	case ixgbe_phy_sfp_intel:
	case ixgbe_phy_sfp_unknown:
		/* SFP+ devices, further checking needed */
		switch (adapter->hw.phy.sfp_type) {
		case ixgbe_sfp_type_da_cu:
		case ixgbe_sfp_type_da_cu_core0:
		case ixgbe_sfp_type_da_cu_core1:
			ecmd->supported |= SUPPORTED_FIBRE;
			ecmd->advertising |= ADVERTISED_FIBRE;
			ecmd->port = PORT_DA;
			break;
		case ixgbe_sfp_type_sr:
		case ixgbe_sfp_type_lr:
		case ixgbe_sfp_type_srlr_core0:
		case ixgbe_sfp_type_srlr_core1:
		case ixgbe_sfp_type_1g_sx_core0:
		case ixgbe_sfp_type_1g_sx_core1:
		case ixgbe_sfp_type_1g_lx_core0:
		case ixgbe_sfp_type_1g_lx_core1:
			ecmd->supported |= SUPPORTED_FIBRE;
			ecmd->advertising |= ADVERTISED_FIBRE;
			ecmd->port = PORT_FIBRE;
			break;
		case ixgbe_sfp_type_not_present:
			ecmd->supported |= SUPPORTED_FIBRE;
			ecmd->advertising |= ADVERTISED_FIBRE;
			ecmd->port = PORT_NONE;
			break;
		case ixgbe_sfp_type_1g_cu_core0:
		case ixgbe_sfp_type_1g_cu_core1:
			ecmd->supported |= SUPPORTED_TP;
			ecmd->advertising |= ADVERTISED_TP;
			ecmd->port = PORT_TP;
			break;
		case ixgbe_sfp_type_unknown:
		default:
			ecmd->supported |= SUPPORTED_FIBRE;
			ecmd->advertising |= ADVERTISED_FIBRE;
			ecmd->port = PORT_OTHER;
			break;
		}
		break;
	case ixgbe_phy_xaui:
		ecmd->supported |= SUPPORTED_FIBRE;
		ecmd->advertising |= ADVERTISED_FIBRE;
		ecmd->port = PORT_NONE;
		break;
	case ixgbe_phy_unknown:
	case ixgbe_phy_generic:
	case ixgbe_phy_sfp_unsupported:
	default:
		ecmd->supported |= SUPPORTED_FIBRE;
		ecmd->advertising |= ADVERTISED_FIBRE;
		ecmd->port = PORT_OTHER;
		break;
	}

	hw->mac.ops.check_link(hw, &link_speed, &link_up, false);
	if (link_up) {
		switch (link_speed) {
		case IXGBE_LINK_SPEED_10GB_FULL:
			ethtool_cmd_speed_set(ecmd, SPEED_10000);
			break;
		case IXGBE_LINK_SPEED_1GB_FULL:
			ethtool_cmd_speed_set(ecmd, SPEED_1000);
			break;
		case IXGBE_LINK_SPEED_100_FULL:
			ethtool_cmd_speed_set(ecmd, SPEED_100);
			break;
		default:
			break;
		}
		ecmd->duplex = DUPLEX_FULL;
	} else {
		ethtool_cmd_speed_set(ecmd, -1);
		ecmd->duplex = -1;
	}

	return 0;
}