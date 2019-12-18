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

/* Variables and functions */
 int CLOCK_HIGH_TIME ; 
 int CLOCK_LOW_TIME ; 
 int /*<<< orphan*/  I2C_CLOCK_HIGH ; 
 int /*<<< orphan*/  I2C_CLOCK_LOW ; 
 int /*<<< orphan*/  I2C_DATA_HIGH ; 
 int /*<<< orphan*/  I2C_DATA_LOW ; 
 int START_CONDITION_HOLD_TIME ; 
 int /*<<< orphan*/  i2c_clk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_delay (int) ; 
 int /*<<< orphan*/  i2c_dir_out () ; 

void
i2c_start(void)
{
	/*
	 * SCL=1 SDA=1
	 */
	i2c_dir_out();
	i2c_delay(CLOCK_HIGH_TIME/6);
	i2c_data(I2C_DATA_HIGH);
	i2c_clk(I2C_CLOCK_HIGH);
	i2c_delay(CLOCK_HIGH_TIME);
	/*
	 * SCL=1 SDA=0
	 */
	i2c_data(I2C_DATA_LOW);
	i2c_delay(START_CONDITION_HOLD_TIME);
	/*
	 * SCL=0 SDA=0
	 */
	i2c_clk(I2C_CLOCK_LOW);
	i2c_delay(CLOCK_LOW_TIME);
}