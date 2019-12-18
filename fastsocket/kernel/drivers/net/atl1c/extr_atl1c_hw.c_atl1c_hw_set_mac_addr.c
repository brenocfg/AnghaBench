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
typedef  int u8 ;
typedef  int u32 ;
struct atl1c_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_WRITE_REG_ARRAY (struct atl1c_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  REG_MAC_STA_ADDR ; 

void atl1c_hw_set_mac_addr(struct atl1c_hw *hw, u8 *mac_addr)
{
	u32 value;
	/*
	 * 00-0B-6A-F6-00-DC
	 * 0:  6AF600DC 1: 000B
	 * low dword
	 */
	value = mac_addr[2] << 24 |
		mac_addr[3] << 16 |
		mac_addr[4] << 8  |
		mac_addr[5];
	AT_WRITE_REG_ARRAY(hw, REG_MAC_STA_ADDR, 0, value);
	/* hight dword */
	value = mac_addr[0] << 8 |
		mac_addr[1];
	AT_WRITE_REG_ARRAY(hw, REG_MAC_STA_ADDR, 1, value);
}