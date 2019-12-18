#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lm90_data {scalar_t__ kind; int /*<<< orphan*/  hwmon_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_pec ; 
 int /*<<< orphan*/  device_remove_file (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 struct lm90_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct lm90_data*) ; 
 int /*<<< orphan*/  lm90_group ; 
 scalar_t__ max6646 ; 
 scalar_t__ max6657 ; 
 TYPE_1__ sensor_dev_attr_temp2_offset ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm90_remove(struct i2c_client *client)
{
	struct lm90_data *data = i2c_get_clientdata(client);

	hwmon_device_unregister(data->hwmon_dev);
	sysfs_remove_group(&client->dev.kobj, &lm90_group);
	device_remove_file(&client->dev, &dev_attr_pec);
	if (data->kind != max6657 && data->kind != max6646)
		device_remove_file(&client->dev,
				   &sensor_dev_attr_temp2_offset.dev_attr);

	kfree(data);
	return 0;
}