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
struct pca9532_platform_data {int dummy; } ;
struct pca9532_data {int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_2__ {struct pca9532_platform_data* platform_data; } ;
struct i2c_client {TYPE_1__ dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pca9532_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct pca9532_data*) ; 
 int /*<<< orphan*/  kfree (struct pca9532_data*) ; 
 struct pca9532_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int pca9532_configure (struct i2c_client*,struct pca9532_data*,struct pca9532_platform_data*) ; 

__attribute__((used)) static int pca9532_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	struct pca9532_data *data = i2c_get_clientdata(client);
	struct pca9532_platform_data *pca9532_pdata = client->dev.platform_data;
	int err;

	if (!pca9532_pdata)
		return -EIO;

	if (!i2c_check_functionality(client->adapter,
		I2C_FUNC_SMBUS_BYTE_DATA))
		return -EIO;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	dev_info(&client->dev, "setting platform data\n");
	i2c_set_clientdata(client, data);
	data->client = client;
	mutex_init(&data->update_lock);

	err = pca9532_configure(client, data, pca9532_pdata);
	if (err) {
		kfree(data);
		i2c_set_clientdata(client, NULL);
	}

	return err;
}