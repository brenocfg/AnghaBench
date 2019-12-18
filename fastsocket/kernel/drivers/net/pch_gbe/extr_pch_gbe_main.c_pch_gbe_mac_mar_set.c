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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct pch_gbe_hw {TYPE_2__* reg; } ;
struct TYPE_4__ {int /*<<< orphan*/  ADDR_MASK; TYPE_1__* mac_adr; } ;
struct TYPE_3__ {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCH_GBE_BUSY ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pch_gbe_wait_clr_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static void pch_gbe_mac_mar_set(struct pch_gbe_hw *hw, u8 * addr, u32 index)
{
	u32 mar_low, mar_high, adrmask;

	pr_debug("index : 0x%x\n", index);

	/*
	 * HW expects these in little endian so we reverse the byte order
	 * from network order (big endian) to little endian
	 */
	mar_high = ((u32) addr[0] | ((u32) addr[1] << 8) |
		   ((u32) addr[2] << 16) | ((u32) addr[3] << 24));
	mar_low = ((u32) addr[4] | ((u32) addr[5] << 8));
	/* Stop the MAC Address of index. */
	adrmask = ioread32(&hw->reg->ADDR_MASK);
	iowrite32((adrmask | (0x0001 << index)), &hw->reg->ADDR_MASK);
	/* wait busy */
	pch_gbe_wait_clr_bit(&hw->reg->ADDR_MASK, PCH_GBE_BUSY);
	/* Set the MAC address to the MAC address 1A/1B register */
	iowrite32(mar_high, &hw->reg->mac_adr[index].high);
	iowrite32(mar_low, &hw->reg->mac_adr[index].low);
	/* Start the MAC address of index */
	iowrite32((adrmask & ~(0x0001 << index)), &hw->reg->ADDR_MASK);
	/* wait busy */
	pch_gbe_wait_clr_bit(&hw->reg->ADDR_MASK, PCH_GBE_BUSY);
}