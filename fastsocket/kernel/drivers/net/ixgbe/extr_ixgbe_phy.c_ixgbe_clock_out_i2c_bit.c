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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ IXGBE_ERR_I2C ; 
 int /*<<< orphan*/  IXGBE_I2CCTL ; 
 int /*<<< orphan*/  IXGBE_I2C_T_HIGH ; 
 int /*<<< orphan*/  IXGBE_I2C_T_LOW ; 
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*,int) ; 
 int /*<<< orphan*/  ixgbe_lower_i2c_clk (struct ixgbe_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_raise_i2c_clk (struct ixgbe_hw*,int /*<<< orphan*/ *) ; 
 scalar_t__ ixgbe_set_i2c_data (struct ixgbe_hw*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 ixgbe_clock_out_i2c_bit(struct ixgbe_hw *hw, bool data)
{
	s32 status;
	u32 i2cctl = IXGBE_READ_REG(hw, IXGBE_I2CCTL);

	status = ixgbe_set_i2c_data(hw, &i2cctl, data);
	if (status == 0) {
		ixgbe_raise_i2c_clk(hw, &i2cctl);

		/* Minimum high period of clock is 4us */
		udelay(IXGBE_I2C_T_HIGH);

		ixgbe_lower_i2c_clk(hw, &i2cctl);

		/* Minimum low period of clock is 4.7 us.
		 * This also takes care of the data hold time.
		 */
		udelay(IXGBE_I2C_T_LOW);
	} else {
		status = IXGBE_ERR_I2C;
		hw_dbg(hw, "I2C data was not set to %X\n", data);
	}

	return status;
}