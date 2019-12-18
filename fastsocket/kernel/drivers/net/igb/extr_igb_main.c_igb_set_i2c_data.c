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
struct igb_adapter {struct e1000_hw hw; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_I2CPARAMS ; 
 int /*<<< orphan*/  E1000_I2C_CLK_OE_N ; 
 int /*<<< orphan*/  E1000_I2C_DATA_OE_N ; 
 int /*<<< orphan*/  E1000_I2C_DATA_OUT ; 
 int /*<<< orphan*/  rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrfl () ; 

__attribute__((used)) static void igb_set_i2c_data(void *data, int state)
{
	struct igb_adapter *adapter = (struct igb_adapter *)data;
	struct e1000_hw *hw = &adapter->hw;
	s32 i2cctl = rd32(E1000_I2CPARAMS);

	if (state)
		i2cctl |= E1000_I2C_DATA_OUT;
	else
		i2cctl &= ~E1000_I2C_DATA_OUT;

	i2cctl &= ~E1000_I2C_DATA_OE_N;
	i2cctl |= E1000_I2C_CLK_OE_N;
	wr32(E1000_I2CPARAMS, i2cctl);
	wrfl();

}