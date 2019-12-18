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
struct tsl2561_command {int cmd; int /*<<< orphan*/  address; int /*<<< orphan*/  block; int /*<<< orphan*/  word; int /*<<< orphan*/  clear; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSL2561_CONTROL_REGISTER ; 
 int /*<<< orphan*/  TSL2561_CONT_REG_PWR_OFF ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tsl2561_powerdown(struct i2c_client *client)
{
	int err;
	struct tsl2561_command Command = {
		.cmd =  1,
		.clear = 0,
		.word = 0,
		.block = 0,
		.address = TSL2561_CONTROL_REGISTER,
	};

	err = i2c_smbus_write_byte_data(client, *(char *)(&Command),
					TSL2561_CONT_REG_PWR_OFF);
	return (err < 0) ? err : 0;
}