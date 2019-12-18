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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__ media_type; } ;
struct TYPE_4__ {int type; } ;
struct e1000_hw {TYPE_1__ phy; TYPE_2__ mac; } ;
struct e1000_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_RCTL_LBM_TCVR ; 
 int /*<<< orphan*/  RCTL ; 
#define  e1000_80003es2lan 130 
#define  e1000_82571 129 
#define  e1000_82572 128 
 int e1000_integrated_phy_loopback (struct e1000_adapter*) ; 
 scalar_t__ e1000_media_type_copper ; 
 scalar_t__ e1000_media_type_fiber ; 
 scalar_t__ e1000_media_type_internal_serdes ; 
 int e1000_set_82571_fiber_loopback (struct e1000_adapter*) ; 
 int e1000_set_es2lan_mac_loopback (struct e1000_adapter*) ; 
 int /*<<< orphan*/  er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int e1000_setup_loopback_test(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 rctl;

	if (hw->phy.media_type == e1000_media_type_fiber ||
	    hw->phy.media_type == e1000_media_type_internal_serdes) {
		switch (hw->mac.type) {
		case e1000_80003es2lan:
			return e1000_set_es2lan_mac_loopback(adapter);
			break;
		case e1000_82571:
		case e1000_82572:
			return e1000_set_82571_fiber_loopback(adapter);
			break;
		default:
			rctl = er32(RCTL);
			rctl |= E1000_RCTL_LBM_TCVR;
			ew32(RCTL, rctl);
			return 0;
		}
	} else if (hw->phy.media_type == e1000_media_type_copper) {
		return e1000_integrated_phy_loopback(adapter);
	}

	return 7;
}