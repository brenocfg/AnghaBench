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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_COMMAND_REG ; 
 int /*<<< orphan*/  RESET_COMMAND ; 
 int /*<<< orphan*/  SOFT_RESET_DELAY_MS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int synaptics_i2c_config (struct i2c_client*) ; 
 int synaptics_i2c_reg_set (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int synaptics_i2c_reset_config(struct i2c_client *client)
{
	int ret;

	/* Reset the Touchpad */
	ret = synaptics_i2c_reg_set(client, DEV_COMMAND_REG, RESET_COMMAND);
	if (ret) {
		dev_err(&client->dev, "Unable to reset device\n");
	} else {
		msleep(SOFT_RESET_DELAY_MS);
		ret = synaptics_i2c_config(client);
		if (ret)
			dev_err(&client->dev, "Unable to config device\n");
	}

	return ret;
}