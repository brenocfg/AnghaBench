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
typedef  int /*<<< orphan*/  u32 ;
struct ixgbe_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SWFW_REGSMP ; 
 int /*<<< orphan*/  IXGBE_SWFW_SYNC ; 
 int /*<<< orphan*/  IXGBE_SWSM ; 
 int /*<<< orphan*/  IXGBE_SWSM_SMBI ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbe_release_swfw_sync_semaphore(struct ixgbe_hw *hw)
{
	 u32 swsm;

	/* Release both semaphores by writing 0 to the bits REGSMP and SMBI */

	swsm = IXGBE_READ_REG(hw, IXGBE_SWSM);
	swsm &= ~IXGBE_SWSM_SMBI;
	IXGBE_WRITE_REG(hw, IXGBE_SWSM, swsm);

	swsm = IXGBE_READ_REG(hw, IXGBE_SWFW_SYNC);
	swsm &= ~IXGBE_SWFW_REGSMP;
	IXGBE_WRITE_REG(hw, IXGBE_SWFW_SYNC, swsm);

	IXGBE_WRITE_FLUSH(hw);
}