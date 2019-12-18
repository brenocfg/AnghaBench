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
struct mcu {int reg_ctrl; int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int MCU_CTRL_POFF ; 
 int /*<<< orphan*/  MCU_REG_CTRL ; 
 struct mcu* glob_mcu ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void mcu_power_off(void)
{
	struct mcu *mcu = glob_mcu;

	pr_info("Sending power-off request to the MCU...\n");
	mutex_lock(&mcu->lock);
	i2c_smbus_write_byte_data(glob_mcu->client, MCU_REG_CTRL,
				  mcu->reg_ctrl | MCU_CTRL_POFF);
	mutex_unlock(&mcu->lock);
}