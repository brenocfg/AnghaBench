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
struct device {int dummy; } ;
struct ad7418_data {int valid; int adc_max; int /*<<< orphan*/  lock; scalar_t__ last_updated; void** in; void** temp; } ;

/* Variables and functions */
 int AD7418_CH_TEMP ; 
 int /*<<< orphan*/  AD7418_REG_ADC ; 
 int AD7418_REG_ADC_CH (int) ; 
 int /*<<< orphan*/  AD7418_REG_CONF ; 
 int /*<<< orphan*/ * AD7418_REG_TEMP ; 
 int HZ ; 
 void* ad7418_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad7418_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct ad7418_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static struct ad7418_data *ad7418_update_device(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct ad7418_data *data = i2c_get_clientdata(client);

	mutex_lock(&data->lock);

	if (time_after(jiffies, data->last_updated + HZ + HZ / 2)
		|| !data->valid) {
		u8 cfg;
		int i, ch;

		/* read config register and clear channel bits */
		cfg = i2c_smbus_read_byte_data(client, AD7418_REG_CONF);
		cfg &= 0x1F;

		i2c_smbus_write_byte_data(client, AD7418_REG_CONF,
						cfg | AD7418_CH_TEMP);
		udelay(30);

		for (i = 0; i < 3; i++) {
			data->temp[i] = ad7418_read(client, AD7418_REG_TEMP[i]);
		}

		for (i = 0, ch = 4; i < data->adc_max; i++, ch--) {
			i2c_smbus_write_byte_data(client,
					AD7418_REG_CONF,
					cfg | AD7418_REG_ADC_CH(ch));

			udelay(15);
			data->in[data->adc_max - 1 - i] =
				ad7418_read(client, AD7418_REG_ADC);
		}

		/* restore old configuration value */
		ad7418_write(client, AD7418_REG_CONF, cfg);

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->lock);

	return data;
}