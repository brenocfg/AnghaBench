#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_9__ {int /*<<< orphan*/  (* read ) (struct ixgbe_hw*,int,int*) ;} ;
struct TYPE_10__ {TYPE_4__ ops; } ;
struct TYPE_8__ {scalar_t__ func; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_lan_id ) (struct ixgbe_hw*) ;} ;
struct TYPE_7__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_5__ eeprom; TYPE_3__ bus; TYPE_2__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 scalar_t__ IXGBE_SAN_MAC_ADDR_PORT0_OFFSET ; 
 scalar_t__ IXGBE_SAN_MAC_ADDR_PORT1_OFFSET ; 
 int /*<<< orphan*/  ixgbe_get_san_mac_addr_offset (struct ixgbe_hw*,int*) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int,int*) ; 

s32 ixgbe_get_san_mac_addr_generic(struct ixgbe_hw *hw, u8 *san_mac_addr)
{
	u16 san_mac_data, san_mac_offset;
	u8 i;

	/*
	 * First read the EEPROM pointer to see if the MAC addresses are
	 * available.  If they're not, no point in calling set_lan_id() here.
	 */
	ixgbe_get_san_mac_addr_offset(hw, &san_mac_offset);

	if ((san_mac_offset == 0) || (san_mac_offset == 0xFFFF)) {
		/*
		 * No addresses available in this EEPROM.  It's not an
		 * error though, so just wipe the local address and return.
		 */
		for (i = 0; i < 6; i++)
			san_mac_addr[i] = 0xFF;

		goto san_mac_addr_out;
	}

	/* make sure we know which port we need to program */
	hw->mac.ops.set_lan_id(hw);
	/* apply the port offset to the address offset */
	(hw->bus.func) ? (san_mac_offset += IXGBE_SAN_MAC_ADDR_PORT1_OFFSET) :
	                 (san_mac_offset += IXGBE_SAN_MAC_ADDR_PORT0_OFFSET);
	for (i = 0; i < 3; i++) {
		hw->eeprom.ops.read(hw, san_mac_offset, &san_mac_data);
		san_mac_addr[i * 2] = (u8)(san_mac_data);
		san_mac_addr[i * 2 + 1] = (u8)(san_mac_data >> 8);
		san_mac_offset++;
	}

san_mac_addr_out:
	return 0;
}