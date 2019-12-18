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
struct i2c_client {TYPE_1__ dev; int /*<<< orphan*/  adapter; } ;
struct g760a_data {int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  clk; int /*<<< orphan*/  fan_div; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  G760A_DEFAULT_CLK ; 
 int /*<<< orphan*/  G760A_DEFAULT_FAN_DIV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g760a_group ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct g760a_data*) ; 
 int /*<<< orphan*/  kfree (struct g760a_data*) ; 
 struct g760a_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int g760a_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct g760a_data *data;
	int err;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE_DATA))
		return -EIO;

	data = kzalloc(sizeof(struct g760a_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	i2c_set_clientdata(client, data);

	data->client = client;
	mutex_init(&data->update_lock);

	/* setup default configuration for now */
	data->fan_div = G760A_DEFAULT_FAN_DIV;
	data->clk = G760A_DEFAULT_CLK;

	/* Register sysfs hooks */
	err = sysfs_create_group(&client->dev.kobj, &g760a_group);
	if (err)
		goto error_sysfs_create_group;

	data->hwmon_dev = hwmon_device_register(&client->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto error_hwmon_device_register;
	}

	return 0;

error_hwmon_device_register:
	sysfs_remove_group(&client->dev.kobj, &g760a_group);
error_sysfs_create_group:
	kfree(data);
	i2c_set_clientdata(client, NULL);

	return err;
}