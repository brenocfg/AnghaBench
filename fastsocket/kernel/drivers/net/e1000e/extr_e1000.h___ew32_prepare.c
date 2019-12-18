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
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int E1000_ICH_FWSM_PCIM2PCI ; 
 scalar_t__ E1000_ICH_FWSM_PCIM2PCI_COUNT ; 
 int /*<<< orphan*/  FWSM ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline s32 __ew32_prepare(struct e1000_hw *hw)
{
	s32 i = E1000_ICH_FWSM_PCIM2PCI_COUNT;

	while ((er32(FWSM) & E1000_ICH_FWSM_PCIM2PCI) && --i)
		udelay(50);

	return i;
}