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
 int MAX_RETRIES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static u8 lm93_read_byte(struct i2c_client *client, u8 reg)
{
	int value, i;

	/* retry in case of read errors */
	for (i=1; i<=MAX_RETRIES; i++) {
		if ((value = i2c_smbus_read_byte_data(client, reg)) >= 0) {
			return value;
		} else {
			dev_warn(&client->dev,"lm93: read byte data failed, "
				"address 0x%02x.\n", reg);
			mdelay(i + 3);
		}

	}

	/* <TODO> what to return in case of error? */
	dev_err(&client->dev,"lm93: All read byte retries failed!!\n");
	return 0;
}