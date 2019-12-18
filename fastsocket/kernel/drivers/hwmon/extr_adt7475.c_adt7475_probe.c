#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct adt7475_data {int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ADT7475_PWM_COUNT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adt7475_attr_group ; 
 int /*<<< orphan*/  adt7475_read_pwm (struct i2c_client*,int) ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct adt7475_data*) ; 
 int /*<<< orphan*/  kfree (struct adt7475_data*) ; 
 struct adt7475_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adt7475_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct adt7475_data *data;
	int i, ret = 0;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (data == NULL)
		return -ENOMEM;

	mutex_init(&data->lock);
	i2c_set_clientdata(client, data);

	/* Call adt7475_read_pwm for all pwm's as this will reprogram any
	   pwm's which are disabled to manual mode with 0% duty cycle */
	for (i = 0; i < ADT7475_PWM_COUNT; i++)
		adt7475_read_pwm(client, i);

	ret = sysfs_create_group(&client->dev.kobj, &adt7475_attr_group);
	if (ret)
		goto efree;

	data->hwmon_dev = hwmon_device_register(&client->dev);
	if (IS_ERR(data->hwmon_dev)) {
		ret = PTR_ERR(data->hwmon_dev);
		goto eremove;
	}

	return 0;

eremove:
	sysfs_remove_group(&client->dev.kobj, &adt7475_attr_group);
efree:
	kfree(data);
	return ret;
}