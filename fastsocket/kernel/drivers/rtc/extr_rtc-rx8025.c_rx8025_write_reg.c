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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rx8025_write_reg(struct i2c_client *client, int number, u8 value)
{
	int ret = i2c_smbus_write_byte_data(client, number << 4, value);

	if (ret)
		dev_err(&client->dev, "Unable to write register #%d\n",
			number);

	return ret;
}