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
typedef  int u8 ;
struct TYPE_3__ {scalar_t__ (* write_i2c_byte ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;scalar_t__ (* read_i2c_byte ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;
typedef  int ixgbe_link_speed ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_I2C_EEPROM_DEV_ADDR2 ; 
#define  IXGBE_LINK_SPEED_10GB_FULL 129 
#define  IXGBE_LINK_SPEED_1GB_FULL 128 
 int /*<<< orphan*/  IXGBE_SFF_SFF_8472_ESCB ; 
 int /*<<< orphan*/  IXGBE_SFF_SFF_8472_OSCB ; 
 int IXGBE_SFF_SOFT_RS_SELECT_10G ; 
 int IXGBE_SFF_SOFT_RS_SELECT_1G ; 
 int IXGBE_SFF_SOFT_RS_SELECT_MASK ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub3 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub4 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ixgbe_set_fiber_fixed_speed(struct ixgbe_hw *hw,
					ixgbe_link_speed speed)
{
	s32 status;
	u8 rs, eeprom_data;

	switch (speed) {
	case IXGBE_LINK_SPEED_10GB_FULL:
		/* one bit mask same as setting on */
		rs = IXGBE_SFF_SOFT_RS_SELECT_10G;
		break;
	case IXGBE_LINK_SPEED_1GB_FULL:
		rs = IXGBE_SFF_SOFT_RS_SELECT_1G;
		break;
	default:
		hw_dbg(hw, "Invalid fixed module speed\n");
		return;
	}

	/* Set RS0 */
	status = hw->phy.ops.read_i2c_byte(hw, IXGBE_SFF_SFF_8472_OSCB,
					   IXGBE_I2C_EEPROM_DEV_ADDR2,
					   &eeprom_data);
	if (status) {
		hw_dbg(hw, "Failed to read Rx Rate Select RS0\n");
		goto out;
	}

	eeprom_data = (eeprom_data & ~IXGBE_SFF_SOFT_RS_SELECT_MASK) & rs;

	status = hw->phy.ops.write_i2c_byte(hw, IXGBE_SFF_SFF_8472_OSCB,
					    IXGBE_I2C_EEPROM_DEV_ADDR2,
					    eeprom_data);
	if (status) {
		hw_dbg(hw, "Failed to write Rx Rate Select RS0\n");
		goto out;
	}

	/* Set RS1 */
	status = hw->phy.ops.read_i2c_byte(hw, IXGBE_SFF_SFF_8472_ESCB,
					   IXGBE_I2C_EEPROM_DEV_ADDR2,
					   &eeprom_data);
	if (status) {
		hw_dbg(hw, "Failed to read Rx Rate Select RS1\n");
		goto out;
	}

	eeprom_data = (eeprom_data & ~IXGBE_SFF_SOFT_RS_SELECT_MASK) & rs;

	status = hw->phy.ops.write_i2c_byte(hw, IXGBE_SFF_SFF_8472_ESCB,
					    IXGBE_I2C_EEPROM_DEV_ADDR2,
					    eeprom_data);
	if (status) {
		hw_dbg(hw, "Failed to write Rx Rate Select RS1\n");
		goto out;
	}
out:
	return;
}