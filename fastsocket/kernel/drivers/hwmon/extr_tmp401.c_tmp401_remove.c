#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tmp401_data {scalar_t__ kind; scalar_t__ hwmon_dev; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_attr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_device_unregister (scalar_t__) ; 
 struct tmp401_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct tmp401_data*) ; 
 TYPE_1__* tmp401_attr ; 
 scalar_t__ tmp411 ; 
 TYPE_1__* tmp411_attr ; 

__attribute__((used)) static int tmp401_remove(struct i2c_client *client)
{
	struct tmp401_data *data = i2c_get_clientdata(client);
	int i;

	if (data->hwmon_dev)
		hwmon_device_unregister(data->hwmon_dev);

	for (i = 0; i < ARRAY_SIZE(tmp401_attr); i++)
		device_remove_file(&client->dev, &tmp401_attr[i].dev_attr);

	if (data->kind == tmp411) {
		for (i = 0; i < ARRAY_SIZE(tmp411_attr); i++)
			device_remove_file(&client->dev,
					   &tmp411_attr[i].dev_attr);
	}

	kfree(data);
	return 0;
}