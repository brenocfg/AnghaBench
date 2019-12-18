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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 

__attribute__((used)) static int lm85_is_fake(struct i2c_client *client)
{
	/*
	 * Differenciate between real LM96000 and Winbond WPCD377I. The latter
	 * emulate the former except that it has no hardware monitoring function
	 * so the readings are always 0.
	 */
	int i;
	u8 in_temp, fan;

	for (i = 0; i < 8; i++) {
		in_temp = i2c_smbus_read_byte_data(client, 0x20 + i);
		fan = i2c_smbus_read_byte_data(client, 0x28 + i);
		if (in_temp != 0x00 || fan != 0xff)
			return 0;
	}

	return 1;
}