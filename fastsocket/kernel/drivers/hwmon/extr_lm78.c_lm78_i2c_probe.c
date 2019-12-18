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
struct lm78_data {int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  type; struct i2c_client* client; } ;
struct i2c_device_id {int /*<<< orphan*/  driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lm78_data*) ; 
 int /*<<< orphan*/  kfree (struct lm78_data*) ; 
 struct lm78_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm78_group ; 
 int /*<<< orphan*/  lm78_init_device (struct lm78_data*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm78_i2c_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct lm78_data *data;
	int err;

	data = kzalloc(sizeof(struct lm78_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	i2c_set_clientdata(client, data);
	data->client = client;
	data->type = id->driver_data;

	/* Initialize the LM78 chip */
	lm78_init_device(data);

	/* Register sysfs hooks */
	err = sysfs_create_group(&client->dev.kobj, &lm78_group);
	if (err)
		goto ERROR3;

	data->hwmon_dev = hwmon_device_register(&client->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto ERROR4;
	}

	return 0;

ERROR4:
	sysfs_remove_group(&client->dev.kobj, &lm78_group);
ERROR3:
	kfree(data);
	return err;
}