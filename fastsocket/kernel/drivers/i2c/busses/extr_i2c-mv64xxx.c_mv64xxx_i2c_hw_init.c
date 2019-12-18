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
struct mv64xxx_i2c_data {int freq_m; int freq_n; int /*<<< orphan*/  state; scalar_t__ reg_base; } ;

/* Variables and functions */
 scalar_t__ MV64XXX_I2C_REG_BAUD ; 
 scalar_t__ MV64XXX_I2C_REG_CONTROL ; 
 int MV64XXX_I2C_REG_CONTROL_STOP ; 
 int MV64XXX_I2C_REG_CONTROL_TWSIEN ; 
 scalar_t__ MV64XXX_I2C_REG_EXT_SLAVE_ADDR ; 
 scalar_t__ MV64XXX_I2C_REG_SLAVE_ADDR ; 
 scalar_t__ MV64XXX_I2C_REG_SOFT_RESET ; 
 int /*<<< orphan*/  MV64XXX_I2C_STATE_IDLE ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void
mv64xxx_i2c_hw_init(struct mv64xxx_i2c_data *drv_data)
{
	writel(0, drv_data->reg_base + MV64XXX_I2C_REG_SOFT_RESET);
	writel((((drv_data->freq_m & 0xf) << 3) | (drv_data->freq_n & 0x7)),
		drv_data->reg_base + MV64XXX_I2C_REG_BAUD);
	writel(0, drv_data->reg_base + MV64XXX_I2C_REG_SLAVE_ADDR);
	writel(0, drv_data->reg_base + MV64XXX_I2C_REG_EXT_SLAVE_ADDR);
	writel(MV64XXX_I2C_REG_CONTROL_TWSIEN | MV64XXX_I2C_REG_CONTROL_STOP,
		drv_data->reg_base + MV64XXX_I2C_REG_CONTROL);
	drv_data->state = MV64XXX_I2C_STATE_IDLE;
}