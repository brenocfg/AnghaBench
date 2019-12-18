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
typedef  int u64 ;
struct TYPE_5__ {int /*<<< orphan*/  (* check_for_link ) (struct e1000_hw*) ;} ;
struct TYPE_6__ {int serdes_has_link; scalar_t__ autoneg; TYPE_2__ ops; } ;
struct TYPE_4__ {scalar_t__ media_type; } ;
struct e1000_hw {TYPE_3__ mac; TYPE_1__ phy; } ;
struct igb_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_STATUS ; 
 int E1000_STATUS_LU ; 
 scalar_t__ e1000_media_type_internal_serdes ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 

__attribute__((used)) static int igb_link_test(struct igb_adapter *adapter, u64 *data)
{
	struct e1000_hw *hw = &adapter->hw;
	*data = 0;
	if (hw->phy.media_type == e1000_media_type_internal_serdes) {
		int i = 0;
		hw->mac.serdes_has_link = false;

		/* On some blade server designs, link establishment
		 * could take as long as 2-3 minutes
		 */
		do {
			hw->mac.ops.check_for_link(&adapter->hw);
			if (hw->mac.serdes_has_link)
				return *data;
			msleep(20);
		} while (i++ < 3750);

		*data = 1;
	} else {
		hw->mac.ops.check_for_link(&adapter->hw);
		if (hw->mac.autoneg)
			msleep(5000);

		if (!(rd32(E1000_STATUS) & E1000_STATUS_LU))
			*data = 1;
	}
	return *data;
}