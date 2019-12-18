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
typedef  scalar_t__ u8 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,scalar_t__) ; 
 int i2c_smbus_write_i2c_block_data (struct i2c_client*,int,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static int rx8025_write_regs(struct i2c_client *client,
			     int number, u8 length, u8 *values)
{
	int ret = i2c_smbus_write_i2c_block_data(client, (number << 4) | 0x08,
						 length, values);

	if (ret)
		dev_err(&client->dev, "Unable to write registers #%d..#%d\n",
			number, number + length - 1);

	return ret;
}