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
 int ISP1301_I2C_INTERRUPT_FALLING ; 
 int ISP1301_I2C_INTERRUPT_LATCH ; 
 int ISP1301_I2C_INTERRUPT_RISING ; 
 int ISP1301_I2C_MODE_CONTROL_1 ; 
 int ISP1301_I2C_MODE_CONTROL_2 ; 
 int ISP1301_I2C_OTG_CONTROL_1 ; 
 int ISP1301_I2C_REG_CLEAR_ADDR ; 
 int MC1_DAT_SE0 ; 
 int MC1_SPEED_REG ; 
 int MC2_BI_DI ; 
 int MC2_PSW_EN ; 
 int MC2_SPD_SUSP_CTRL ; 
 int OTG1_DM_PULLDOWN ; 
 int OTG1_DP_PULLDOWN ; 
 int /*<<< orphan*/  i2c_write (int,int) ; 

__attribute__((used)) static void isp1301_configure(void)
{
	/* PNX4008 only supports DAT_SE0 USB mode */
	/* PNX4008 R2A requires setting the MAX603 to output 3.6V */
	/* Power up externel charge-pump */

	i2c_write(MC1_DAT_SE0 | MC1_SPEED_REG, ISP1301_I2C_MODE_CONTROL_1);
	i2c_write(~(MC1_DAT_SE0 | MC1_SPEED_REG),
		  ISP1301_I2C_MODE_CONTROL_1 | ISP1301_I2C_REG_CLEAR_ADDR);
	i2c_write(MC2_BI_DI | MC2_PSW_EN | MC2_SPD_SUSP_CTRL,
		  ISP1301_I2C_MODE_CONTROL_2);
	i2c_write(~(MC2_BI_DI | MC2_PSW_EN | MC2_SPD_SUSP_CTRL),
		  ISP1301_I2C_MODE_CONTROL_2 | ISP1301_I2C_REG_CLEAR_ADDR);
	i2c_write(OTG1_DM_PULLDOWN | OTG1_DP_PULLDOWN,
		  ISP1301_I2C_OTG_CONTROL_1);
	i2c_write(~(OTG1_DM_PULLDOWN | OTG1_DP_PULLDOWN),
		  ISP1301_I2C_OTG_CONTROL_1 | ISP1301_I2C_REG_CLEAR_ADDR);
	i2c_write(0xFF,
		  ISP1301_I2C_INTERRUPT_LATCH | ISP1301_I2C_REG_CLEAR_ADDR);
	i2c_write(0xFF,
		  ISP1301_I2C_INTERRUPT_FALLING | ISP1301_I2C_REG_CLEAR_ADDR);
	i2c_write(0xFF,
		  ISP1301_I2C_INTERRUPT_RISING | ISP1301_I2C_REG_CLEAR_ADDR);

}