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
struct ixgbe_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_FACTPS ; 
 int IXGBE_FACTPS_MNGCG ; 
 int /*<<< orphan*/  IXGBE_FWSM ; 
 int IXGBE_FWSM_FW_MODE_PT ; 
 int IXGBE_FWSM_MODE_MASK ; 
 int /*<<< orphan*/  IXGBE_MANC ; 
 int IXGBE_MANC_RCV_TCO_EN ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ixgbe_mng_enabled(struct ixgbe_hw *hw)
{
	u32 fwsm, manc, factps;

	fwsm = IXGBE_READ_REG(hw, IXGBE_FWSM);
	if ((fwsm & IXGBE_FWSM_MODE_MASK) != IXGBE_FWSM_FW_MODE_PT)
		return false;

	manc = IXGBE_READ_REG(hw, IXGBE_MANC);
	if (!(manc & IXGBE_MANC_RCV_TCO_EN))
		return false;

	factps = IXGBE_READ_REG(hw, IXGBE_FACTPS);
	if (factps & IXGBE_FACTPS_MNGCG)
		return false;

	return true;
}