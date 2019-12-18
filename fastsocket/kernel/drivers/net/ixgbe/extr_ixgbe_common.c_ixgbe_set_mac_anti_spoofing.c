#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_PFVFSPOOF (int) ; 
 int IXGBE_PFVFSPOOF_REG_COUNT ; 
 int IXGBE_SPOOF_MACAS_MASK ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ixgbe_mac_82598EB ; 

void ixgbe_set_mac_anti_spoofing(struct ixgbe_hw *hw, bool enable, int pf)
{
	int j;
	int pf_target_reg = pf >> 3;
	int pf_target_shift = pf % 8;
	u32 pfvfspoof = 0;

	if (hw->mac.type == ixgbe_mac_82598EB)
		return;

	if (enable)
		pfvfspoof = IXGBE_SPOOF_MACAS_MASK;

	/*
	 * PFVFSPOOF register array is size 8 with 8 bits assigned to
	 * MAC anti-spoof enables in each register array element.
	 */
	for (j = 0; j < pf_target_reg; j++)
		IXGBE_WRITE_REG(hw, IXGBE_PFVFSPOOF(j), pfvfspoof);

	/*
	 * The PF should be allowed to spoof so that it can support
	 * emulation mode NICs.  Do not set the bits assigned to the PF
	 */
	pfvfspoof &= (1 << pf_target_shift) - 1;
	IXGBE_WRITE_REG(hw, IXGBE_PFVFSPOOF(j), pfvfspoof);

	/*
	 * Remaining pools belong to the PF so they do not need to have
	 * anti-spoofing enabled.
	 */
	for (j++; j < IXGBE_PFVFSPOOF_REG_COUNT; j++)
		IXGBE_WRITE_REG(hw, IXGBE_PFVFSPOOF(j), 0);
}