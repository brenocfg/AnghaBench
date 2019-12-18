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
struct e1000_hw {TYPE_1__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  CTRL_EXT ; 
 int E1000_CTRL_EXT_PHYPDEN ; 
 int E1000_CTRL_MEHE ; 
 int E1000_PBECCSTS_ECC_ENABLE ; 
 int E1000_RFCTL_IPV6_EX_DIS ; 
 int E1000_RFCTL_NEW_IPV6_EXT_DIS ; 
 int E1000_RFCTL_NFSR_DIS ; 
 int E1000_RFCTL_NFSW_DIS ; 
 int E1000_TCTL_MULR ; 
 int /*<<< orphan*/  PBECCSTS ; 
 int /*<<< orphan*/  RFCTL ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  TARC (int) ; 
 int /*<<< orphan*/  TCTL ; 
 int /*<<< orphan*/  TXDCTL (int) ; 
 scalar_t__ e1000_ich8lan ; 
 scalar_t__ e1000_pch_lpt ; 
 scalar_t__ e1000_pchlan ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void e1000_initialize_hw_bits_ich8lan(struct e1000_hw *hw)
{
	u32 reg;

	/* Extended Device Control */
	reg = er32(CTRL_EXT);
	reg |= (1 << 22);
	/* Enable PHY low-power state when MAC is at D3 w/o WoL */
	if (hw->mac.type >= e1000_pchlan)
		reg |= E1000_CTRL_EXT_PHYPDEN;
	ew32(CTRL_EXT, reg);

	/* Transmit Descriptor Control 0 */
	reg = er32(TXDCTL(0));
	reg |= (1 << 22);
	ew32(TXDCTL(0), reg);

	/* Transmit Descriptor Control 1 */
	reg = er32(TXDCTL(1));
	reg |= (1 << 22);
	ew32(TXDCTL(1), reg);

	/* Transmit Arbitration Control 0 */
	reg = er32(TARC(0));
	if (hw->mac.type == e1000_ich8lan)
		reg |= (1 << 28) | (1 << 29);
	reg |= (1 << 23) | (1 << 24) | (1 << 26) | (1 << 27);
	ew32(TARC(0), reg);

	/* Transmit Arbitration Control 1 */
	reg = er32(TARC(1));
	if (er32(TCTL) & E1000_TCTL_MULR)
		reg &= ~(1 << 28);
	else
		reg |= (1 << 28);
	reg |= (1 << 24) | (1 << 26) | (1 << 30);
	ew32(TARC(1), reg);

	/* Device Status */
	if (hw->mac.type == e1000_ich8lan) {
		reg = er32(STATUS);
		reg &= ~(1 << 31);
		ew32(STATUS, reg);
	}

	/* work-around descriptor data corruption issue during nfs v2 udp
	 * traffic, just disable the nfs filtering capability
	 */
	reg = er32(RFCTL);
	reg |= (E1000_RFCTL_NFSW_DIS | E1000_RFCTL_NFSR_DIS);

	/* Disable IPv6 extension header parsing because some malformed
	 * IPv6 headers can hang the Rx.
	 */
	if (hw->mac.type == e1000_ich8lan)
		reg |= (E1000_RFCTL_IPV6_EX_DIS | E1000_RFCTL_NEW_IPV6_EXT_DIS);
	ew32(RFCTL, reg);

	/* Enable ECC on Lynxpoint */
	if (hw->mac.type == e1000_pch_lpt) {
		reg = er32(PBECCSTS);
		reg |= E1000_PBECCSTS_ECC_ENABLE;
		ew32(PBECCSTS, reg);

		reg = er32(CTRL);
		reg |= E1000_CTRL_MEHE;
		ew32(CTRL, reg);
	}
}