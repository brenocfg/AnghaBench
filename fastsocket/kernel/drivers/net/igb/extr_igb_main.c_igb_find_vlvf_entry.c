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
struct e1000_hw {int dummy; } ;
struct igb_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_VLVF (int) ; 
 int E1000_VLVF_ARRAY_SIZE ; 
 int E1000_VLVF_VLANID_ENABLE ; 
 int E1000_VLVF_VLANID_MASK ; 
 int rd32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int igb_find_vlvf_entry(struct igb_adapter *adapter, int vid)
{
	struct e1000_hw *hw = &adapter->hw;
	int i;
	u32 reg;

	/* Find the vlan filter for this id */
	for (i = 0; i < E1000_VLVF_ARRAY_SIZE; i++) {
		reg = rd32(E1000_VLVF(i));
		if ((reg & E1000_VLVF_VLANID_ENABLE) &&
		    vid == (reg & E1000_VLVF_VLANID_MASK))
			break;
	}

	if (i >= E1000_VLVF_ARRAY_SIZE)
		i = -1;

	return i;
}