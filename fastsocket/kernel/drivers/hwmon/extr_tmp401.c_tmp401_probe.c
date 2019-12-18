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
struct tmp401_data {int kind; int /*<<< orphan*/ * hwmon_dev; int /*<<< orphan*/  update_lock; } ;
struct i2c_device_id {int driver_data; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_attr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char const*) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hwmon_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tmp401_data*) ; 
 struct tmp401_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* tmp401_attr ; 
 int /*<<< orphan*/  tmp401_init_client (struct i2c_client*) ; 
 int /*<<< orphan*/  tmp401_remove (struct i2c_client*) ; 
 int tmp411 ; 
 TYPE_1__* tmp411_attr ; 

__attribute__((used)) static int tmp401_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int i, err = 0;
	struct tmp401_data *data;
	const char *names[] = { "TMP401", "TMP411" };

	data = kzalloc(sizeof(struct tmp401_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);
	data->kind = id->driver_data;

	/* Initialize the TMP401 chip */
	tmp401_init_client(client);

	/* Register sysfs hooks */
	for (i = 0; i < ARRAY_SIZE(tmp401_attr); i++) {
		err = device_create_file(&client->dev,
					 &tmp401_attr[i].dev_attr);
		if (err)
			goto exit_remove;
	}

	/* Register aditional tmp411 sysfs hooks */
	if (data->kind == tmp411) {
		for (i = 0; i < ARRAY_SIZE(tmp411_attr); i++) {
			err = device_create_file(&client->dev,
						 &tmp411_attr[i].dev_attr);
			if (err)
				goto exit_remove;
		}
	}

	data->hwmon_dev = hwmon_device_register(&client->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		data->hwmon_dev = NULL;
		goto exit_remove;
	}

	dev_info(&client->dev, "Detected TI %s chip\n",
		 names[data->kind - 1]);

	return 0;

exit_remove:
	tmp401_remove(client); /* will also free data for us */
	return err;
}