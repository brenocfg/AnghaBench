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
struct TYPE_3__ {int rar_entry_count; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {TYPE_2__* vf_data; struct e1000_hw hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  vf_mac_addresses; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  igb_rar_set_qsel (struct igb_adapter*,unsigned char*,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int igb_set_vf_mac(struct igb_adapter *adapter,
			  int vf, unsigned char *mac_addr)
{
	struct e1000_hw *hw = &adapter->hw;
	/* VF MAC addresses start at end of receive addresses and moves
	 * towards the first, as a result a collision should not be possible
	 */
	int rar_entry = hw->mac.rar_entry_count - (vf + 1);

	memcpy(adapter->vf_data[vf].vf_mac_addresses, mac_addr, ETH_ALEN);

	igb_rar_set_qsel(adapter, mac_addr, rar_entry, vf);

	return 0;
}