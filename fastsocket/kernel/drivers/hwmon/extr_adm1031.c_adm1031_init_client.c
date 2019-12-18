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
struct i2c_client {int dummy; } ;
struct adm1031_data {scalar_t__ chip_type; } ;

/* Variables and functions */
 unsigned int ADM1031_CONF1_MONITOR_ENABLE ; 
 unsigned int ADM1031_CONF2_PWM1_ENABLE ; 
 unsigned int ADM1031_CONF2_PWM2_ENABLE ; 
 unsigned int ADM1031_CONF2_TACH1_ENABLE ; 
 unsigned int ADM1031_CONF2_TACH2_ENABLE ; 
 int /*<<< orphan*/  ADM1031_REG_CONF1 ; 
 int /*<<< orphan*/  ADM1031_REG_CONF2 ; 
 scalar_t__ adm1031 ; 
 unsigned int adm1031_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adm1031_write_value (struct i2c_client*,int /*<<< orphan*/ ,unsigned int) ; 
 struct adm1031_data* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static void adm1031_init_client(struct i2c_client *client)
{
	unsigned int read_val;
	unsigned int mask;
	struct adm1031_data *data = i2c_get_clientdata(client);

	mask = (ADM1031_CONF2_PWM1_ENABLE | ADM1031_CONF2_TACH1_ENABLE);
	if (data->chip_type == adm1031) {
		mask |= (ADM1031_CONF2_PWM2_ENABLE |
			ADM1031_CONF2_TACH2_ENABLE);
	}
	/* Initialize the ADM1031 chip (enables fan speed reading ) */
	read_val = adm1031_read_value(client, ADM1031_REG_CONF2);
	if ((read_val | mask) != read_val) {
	    adm1031_write_value(client, ADM1031_REG_CONF2, read_val | mask);
	}

	read_val = adm1031_read_value(client, ADM1031_REG_CONF1);
	if ((read_val | ADM1031_CONF1_MONITOR_ENABLE) != read_val) {
	    adm1031_write_value(client, ADM1031_REG_CONF1, read_val |
				ADM1031_CONF1_MONITOR_ENABLE);
	}

}