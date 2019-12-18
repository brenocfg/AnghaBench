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
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int type; } ;
struct ixgbe_hw {TYPE_2__ mac; TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbe_mac_82598EB ; 
#define  ixgbe_phy_nl 136 
#define  ixgbe_phy_sfp_active_unknown 135 
#define  ixgbe_phy_sfp_avago 134 
#define  ixgbe_phy_sfp_ftl 133 
#define  ixgbe_phy_sfp_ftl_active 132 
#define  ixgbe_phy_sfp_intel 131 
#define  ixgbe_phy_sfp_passive_tyco 130 
#define  ixgbe_phy_sfp_passive_unknown 129 
#define  ixgbe_phy_sfp_unknown 128 

__attribute__((used)) static inline bool ixgbe_is_sfp(struct ixgbe_hw *hw)
{
	switch (hw->phy.type) {
	case ixgbe_phy_sfp_avago:
	case ixgbe_phy_sfp_ftl:
	case ixgbe_phy_sfp_intel:
	case ixgbe_phy_sfp_unknown:
	case ixgbe_phy_sfp_passive_tyco:
	case ixgbe_phy_sfp_passive_unknown:
	case ixgbe_phy_sfp_active_unknown:
	case ixgbe_phy_sfp_ftl_active:
		return true;
	case ixgbe_phy_nl:
		if (hw->mac.type == ixgbe_mac_82598EB)
			return true;
	default:
		return false;
	}
}