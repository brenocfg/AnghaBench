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
struct max6650_data {int speed; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  config; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int DIV_FROM_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FAN_RPM_MAX ; 
 int /*<<< orphan*/  FAN_RPM_MIN ; 
 int /*<<< orphan*/  MAX6650_REG_SPEED ; 
 int SENSORS_LIMIT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clock ; 
 struct max6650_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t set_target(struct device *dev, struct device_attribute *devattr,
			 const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct max6650_data *data = i2c_get_clientdata(client);
	int rpm = simple_strtoul(buf, NULL, 10);
	int kscale, ktach;

	rpm = SENSORS_LIMIT(rpm, FAN_RPM_MIN, FAN_RPM_MAX);

	/*
	* Divide the required speed by 60 to get from rpm to rps, then
	* use the datasheet equation:
	*
	*     KTACH = [(fCLK x KSCALE) / (256 x FanSpeed)] - 1
	*/

	mutex_lock(&data->update_lock);

	kscale = DIV_FROM_REG(data->config);
	ktach = ((clock * kscale) / (256 * rpm / 60)) - 1;
	if (ktach < 0)
		ktach = 0;
	if (ktach > 255)
		ktach = 255;
	data->speed = ktach;

	i2c_smbus_write_byte_data(client, MAX6650_REG_SPEED, data->speed);

	mutex_unlock(&data->update_lock);

	return count;
}