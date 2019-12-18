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
typedef  int u8 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int i2c_smbus_read_i2c_block_data (struct i2c_client*,int,int,int*) ; 

__attribute__((used)) static int rx8025_read_regs(struct i2c_client *client,
			    int number, u8 length, u8 *values)
{
	int ret = i2c_smbus_read_i2c_block_data(client, (number << 4) | 0x08,
						length, values);

	if (ret != length) {
		dev_err(&client->dev, "Unable to read registers #%d..#%d\n",
			number, number + length - 1);
		return ret < 0 ? ret : -EIO;
	}

	return 0;
}