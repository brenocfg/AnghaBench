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
struct TYPE_4__ {int /*<<< orphan*/  (* validate ) (struct e1000_hw*) ;} ;
struct TYPE_5__ {TYPE_1__ ops; } ;
struct TYPE_6__ {int type; } ;
struct e1000_hw {TYPE_2__ nvm; TYPE_3__ mac; } ;
struct igb_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
#define  e1000_i210 129 
#define  e1000_i211 128 
 int /*<<< orphan*/  igb_get_flash_presence_i210 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 

__attribute__((used)) static int igb_eeprom_test(struct igb_adapter *adapter, u64 *data)
{
	struct e1000_hw *hw = &adapter->hw;

	*data = 0;

	/* Validate eeprom on all parts but flashless */
	switch (hw->mac.type) {
	case e1000_i210:
	case e1000_i211:
		if (igb_get_flash_presence_i210(hw)) {
			if (adapter->hw.nvm.ops.validate(&adapter->hw) < 0)
				*data = 2;
		}
		break;
	default:
		if (adapter->hw.nvm.ops.validate(&adapter->hw) < 0)
			*data = 2;
		break;
	}

	return *data;
}