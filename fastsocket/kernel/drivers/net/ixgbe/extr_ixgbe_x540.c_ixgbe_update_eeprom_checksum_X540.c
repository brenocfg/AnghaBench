#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {scalar_t__ (* acquire_swfw_sync ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* release_swfw_sync ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_1__ ops; } ;
struct TYPE_7__ {scalar_t__ (* read ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* calc_checksum ) (struct ixgbe_hw*) ;} ;
struct TYPE_8__ {TYPE_3__ ops; } ;
struct ixgbe_hw {TYPE_2__ mac; TYPE_4__ eeprom; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_EEPROM_CHECKSUM ; 
 scalar_t__ IXGBE_ERR_SWFW_SYNC ; 
 int /*<<< orphan*/  IXGBE_GSSR_EEP_SM ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 scalar_t__ ixgbe_update_flash_X540 (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_write_eewr_generic (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub4 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 ixgbe_update_eeprom_checksum_X540(struct ixgbe_hw *hw)
{
	s32 status;
	u16 checksum;

	/*
	 * Read the first word from the EEPROM. If this times out or fails, do
	 * not continue or we could be in for a very long wait while every
	 * EEPROM read fails
	 */
	status = hw->eeprom.ops.read(hw, 0, &checksum);

	if (status != 0)
		hw_dbg(hw, "EEPROM read failed\n");

	if (hw->mac.ops.acquire_swfw_sync(hw, IXGBE_GSSR_EEP_SM) == 0) {
		checksum = hw->eeprom.ops.calc_checksum(hw);

		/*
		 * Do not use hw->eeprom.ops.write because we do not want to
		 * take the synchronization semaphores twice here.
		 */
		status = ixgbe_write_eewr_generic(hw, IXGBE_EEPROM_CHECKSUM,
						  checksum);

	if (status == 0)
		status = ixgbe_update_flash_X540(hw);
	else
		status = IXGBE_ERR_SWFW_SYNC;
	}

	hw->mac.ops.release_swfw_sync(hw, IXGBE_GSSR_EEP_SM);

	return status;
}