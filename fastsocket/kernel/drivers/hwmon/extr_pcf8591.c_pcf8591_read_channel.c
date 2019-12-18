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
struct pcf8591_data {int control; int /*<<< orphan*/  update_lock; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int PCF8591_CONTROL_AICH_MASK ; 
 int REG_TO_SIGNED (int) ; 
 struct pcf8591_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte (struct i2c_client*,int) ; 
 int input_mode ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int pcf8591_read_channel(struct device *dev, int channel)
{
	u8 value;
	struct i2c_client *client = to_i2c_client(dev);
	struct pcf8591_data *data = i2c_get_clientdata(client);

	mutex_lock(&data->update_lock);

	if ((data->control & PCF8591_CONTROL_AICH_MASK) != channel) {
		data->control = (data->control & ~PCF8591_CONTROL_AICH_MASK)
			      | channel;
		i2c_smbus_write_byte(client, data->control);

		/* The first byte transmitted contains the conversion code of
		   the previous read cycle. FLUSH IT! */
		i2c_smbus_read_byte(client);
	}
	value = i2c_smbus_read_byte(client);

	mutex_unlock(&data->update_lock);

	if ((channel == 2 && input_mode == 2) ||
	    (channel != 3 && (input_mode == 1 || input_mode == 3)))
		return (10 * REG_TO_SIGNED(value));
	else
		return (10 * value);
}