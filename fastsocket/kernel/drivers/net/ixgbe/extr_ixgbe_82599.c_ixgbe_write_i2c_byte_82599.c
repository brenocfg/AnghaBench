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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_2__ {int qsfp_shared_i2c_bus; } ;
struct ixgbe_hw {TYPE_1__ phy; } ;
typedef  int s32 ;

/* Variables and functions */
 int IXGBE_ERR_I2C ; 
 int /*<<< orphan*/  IXGBE_ESDP ; 
 int IXGBE_ESDP_SDP0 ; 
 int IXGBE_ESDP_SDP1 ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 int ixgbe_write_i2c_byte_generic (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static s32 ixgbe_write_i2c_byte_82599(struct ixgbe_hw *hw, u8 byte_offset,
				      u8 dev_addr, u8 data)
{
	u32 esdp;
	s32 status;
	s32 timeout = 200;

	if (hw->phy.qsfp_shared_i2c_bus == true) {
		/* Acquire I2C bus ownership. */
		esdp = IXGBE_READ_REG(hw, IXGBE_ESDP);
		esdp |= IXGBE_ESDP_SDP0;
		IXGBE_WRITE_REG(hw, IXGBE_ESDP, esdp);
		IXGBE_WRITE_FLUSH(hw);

		while (timeout) {
			esdp = IXGBE_READ_REG(hw, IXGBE_ESDP);
			if (esdp & IXGBE_ESDP_SDP1)
				break;

			usleep_range(5000, 10000);
			timeout--;
		}

		if (!timeout) {
			hw_dbg(hw, "Driver can't access resource, acquiring I2C bus timeout.\n");
			status = IXGBE_ERR_I2C;
			goto release_i2c_access;
		}
	}

	status = ixgbe_write_i2c_byte_generic(hw, byte_offset, dev_addr, data);

release_i2c_access:
	if (hw->phy.qsfp_shared_i2c_bus == true) {
		/* Release I2C bus ownership. */
		esdp = IXGBE_READ_REG(hw, IXGBE_ESDP);
		esdp &= ~IXGBE_ESDP_SDP0;
		IXGBE_WRITE_REG(hw, IXGBE_ESDP, esdp);
		IXGBE_WRITE_FLUSH(hw);
	}

	return status;
}