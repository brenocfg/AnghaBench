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
struct adm1025_data {int /*<<< orphan*/  vrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM1025_REG_CONFIG ; 
 int /*<<< orphan*/  ADM1025_REG_IN_MAX (int) ; 
 int /*<<< orphan*/  ADM1025_REG_TEMP_HIGH (int) ; 
 struct adm1025_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vid_which_vrm () ; 

__attribute__((used)) static void adm1025_init_client(struct i2c_client *client)
{
	u8 reg;
	struct adm1025_data *data = i2c_get_clientdata(client);
	int i;

	data->vrm = vid_which_vrm();

	/*
	 * Set high limits
	 * Usually we avoid setting limits on driver init, but it happens
	 * that the ADM1025 comes with stupid default limits (all registers
	 * set to 0). In case the chip has not gone through any limit
	 * setting yet, we better set the high limits to the max so that
	 * no alarm triggers.
	 */
	for (i=0; i<6; i++) {
		reg = i2c_smbus_read_byte_data(client,
					       ADM1025_REG_IN_MAX(i));
		if (reg == 0)
			i2c_smbus_write_byte_data(client,
						  ADM1025_REG_IN_MAX(i),
						  0xFF);
	}
	for (i=0; i<2; i++) {
		reg = i2c_smbus_read_byte_data(client,
					       ADM1025_REG_TEMP_HIGH(i));
		if (reg == 0)
			i2c_smbus_write_byte_data(client,
						  ADM1025_REG_TEMP_HIGH(i),
						  0x7F);
	}

	/*
	 * Start the conversions
	 */
	reg = i2c_smbus_read_byte_data(client, ADM1025_REG_CONFIG);
	if (!(reg & 0x01))
		i2c_smbus_write_byte_data(client, ADM1025_REG_CONFIG,
					  (reg&0x7E)|0x01);
}