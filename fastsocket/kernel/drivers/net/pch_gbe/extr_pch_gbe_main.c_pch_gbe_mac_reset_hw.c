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
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct pch_gbe_hw {TYPE_2__ mac; TYPE_1__* reg; } ;
struct TYPE_3__ {int /*<<< orphan*/  RESET; int /*<<< orphan*/  MODE; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCH_GBE_ALL_RST ; 
 int /*<<< orphan*/  PCH_GBE_MODE_GMII_ETHER ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pch_gbe_mac_mar_set (struct pch_gbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_gbe_mac_read_mac_addr (struct pch_gbe_hw*) ; 
 int /*<<< orphan*/  pch_gbe_wait_clr_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pch_gbe_mac_reset_hw(struct pch_gbe_hw *hw)
{
	/* Read the MAC address. and store to the private data */
	pch_gbe_mac_read_mac_addr(hw);
	iowrite32(PCH_GBE_ALL_RST, &hw->reg->RESET);
#ifdef PCH_GBE_MAC_IFOP_RGMII
	iowrite32(PCH_GBE_MODE_GMII_ETHER, &hw->reg->MODE);
#endif
	pch_gbe_wait_clr_bit(&hw->reg->RESET, PCH_GBE_ALL_RST);
	/* Setup the receive address */
	pch_gbe_mac_mar_set(hw, hw->mac.addr, 0);
	return;
}