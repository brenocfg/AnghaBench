#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct w83793_data {int /*<<< orphan*/ ** lm75; int /*<<< orphan*/  hwmon_dev; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev_attr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_attr_vrm ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 struct w83793_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct w83793_data*) ; 
 TYPE_1__* sda_single_files ; 
 TYPE_1__* w83793_left_fan ; 
 TYPE_1__* w83793_left_pwm ; 
 TYPE_1__* w83793_sensor_attr_2 ; 
 TYPE_1__* w83793_temp ; 
 TYPE_1__* w83793_vid ; 

__attribute__((used)) static int w83793_remove(struct i2c_client *client)
{
	struct w83793_data *data = i2c_get_clientdata(client);
	struct device *dev = &client->dev;
	int i;

	hwmon_device_unregister(data->hwmon_dev);

	for (i = 0; i < ARRAY_SIZE(w83793_sensor_attr_2); i++)
		device_remove_file(dev,
				   &w83793_sensor_attr_2[i].dev_attr);

	for (i = 0; i < ARRAY_SIZE(sda_single_files); i++)
		device_remove_file(dev, &sda_single_files[i].dev_attr);

	for (i = 0; i < ARRAY_SIZE(w83793_vid); i++)
		device_remove_file(dev, &w83793_vid[i].dev_attr);
	device_remove_file(dev, &dev_attr_vrm);

	for (i = 0; i < ARRAY_SIZE(w83793_left_fan); i++)
		device_remove_file(dev, &w83793_left_fan[i].dev_attr);

	for (i = 0; i < ARRAY_SIZE(w83793_left_pwm); i++)
		device_remove_file(dev, &w83793_left_pwm[i].dev_attr);

	for (i = 0; i < ARRAY_SIZE(w83793_temp); i++)
		device_remove_file(dev, &w83793_temp[i].dev_attr);

	if (data->lm75[0] != NULL)
		i2c_unregister_device(data->lm75[0]);
	if (data->lm75[1] != NULL)
		i2c_unregister_device(data->lm75[1]);

	kfree(data);

	return 0;
}