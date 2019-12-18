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
struct tsl2550_data {int power_state; size_t operating_mode; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/ * TSL2550_MODE_RANGE ; 
 int TSL2550_POWER_UP ; 
 struct tsl2550_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 int i2c_smbus_write_byte (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tsl2550_init_client(struct i2c_client *client)
{
	struct tsl2550_data *data = i2c_get_clientdata(client);
	int err;

	/*
	 * Probe the chip. To do so we try to power up the device and then to
	 * read back the 0x03 code
	 */
	err = i2c_smbus_read_byte_data(client, TSL2550_POWER_UP);
	if (err < 0)
		return err;
	if (err != TSL2550_POWER_UP)
		return -ENODEV;
	data->power_state = 1;

	/* Set the default operating mode */
	err = i2c_smbus_write_byte(client,
				   TSL2550_MODE_RANGE[data->operating_mode]);
	if (err < 0)
		return err;

	return 0;
}