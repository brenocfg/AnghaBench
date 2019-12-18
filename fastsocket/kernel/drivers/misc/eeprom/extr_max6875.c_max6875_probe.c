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
struct max6875_data {int /*<<< orphan*/  fake_client; int /*<<< orphan*/  update_lock; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {int addr; TYPE_1__ dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_SMBUS_READ_BYTE ; 
 int I2C_FUNC_SMBUS_WRITE_BYTE_DATA ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int) ; 
 int /*<<< orphan*/  i2c_new_dummy (struct i2c_adapter*,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct max6875_data*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct max6875_data*) ; 
 struct max6875_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_eeprom_attr ; 

__attribute__((used)) static int max6875_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = client->adapter;
	struct max6875_data *data;
	int err;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WRITE_BYTE_DATA
				     | I2C_FUNC_SMBUS_READ_BYTE))
		return -ENODEV;

	/* Only bind to even addresses */
	if (client->addr & 1)
		return -ENODEV;

	if (!(data = kzalloc(sizeof(struct max6875_data), GFP_KERNEL)))
		return -ENOMEM;

	/* A fake client is created on the odd address */
	data->fake_client = i2c_new_dummy(client->adapter, client->addr + 1);
	if (!data->fake_client) {
		err = -ENOMEM;
		goto exit_kfree;
	}

	/* Init real i2c_client */
	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	err = sysfs_create_bin_file(&client->dev.kobj, &user_eeprom_attr);
	if (err)
		goto exit_remove_fake;

	return 0;

exit_remove_fake:
	i2c_unregister_device(data->fake_client);
exit_kfree:
	kfree(data);
	return err;
}