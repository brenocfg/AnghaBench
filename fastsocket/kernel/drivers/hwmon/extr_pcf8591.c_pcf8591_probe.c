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
struct pcf8591_data {int /*<<< orphan*/  update_lock; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_attr_in2_input ; 
 int /*<<< orphan*/  dev_attr_in3_input ; 
 int device_create_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct pcf8591_data*) ; 
 int input_mode ; 
 int /*<<< orphan*/  kfree (struct pcf8591_data*) ; 
 struct pcf8591_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcf8591_attr_group ; 
 int /*<<< orphan*/  pcf8591_attr_group_opt ; 
 int /*<<< orphan*/  pcf8591_init_client (struct i2c_client*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcf8591_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct pcf8591_data *data;
	int err;

	if (!(data = kzalloc(sizeof(struct pcf8591_data), GFP_KERNEL))) {
		err = -ENOMEM;
		goto exit;
	}

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	/* Initialize the PCF8591 chip */
	pcf8591_init_client(client);

	/* Register sysfs hooks */
	err = sysfs_create_group(&client->dev.kobj, &pcf8591_attr_group);
	if (err)
		goto exit_kfree;

	/* Register input2 if not in "two differential inputs" mode */
	if (input_mode != 3) {
		if ((err = device_create_file(&client->dev,
					      &dev_attr_in2_input)))
			goto exit_sysfs_remove;
	}

	/* Register input3 only in "four single ended inputs" mode */
	if (input_mode == 0) {
		if ((err = device_create_file(&client->dev,
					      &dev_attr_in3_input)))
			goto exit_sysfs_remove;
	}

	return 0;

exit_sysfs_remove:
	sysfs_remove_group(&client->dev.kobj, &pcf8591_attr_group_opt);
	sysfs_remove_group(&client->dev.kobj, &pcf8591_attr_group);
exit_kfree:
	kfree(data);
exit:
	return err;
}