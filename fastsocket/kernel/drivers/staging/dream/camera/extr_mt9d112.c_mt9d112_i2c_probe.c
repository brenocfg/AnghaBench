#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mt9d112_work {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*) ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 struct i2c_client* mt9d112_client ; 
 int /*<<< orphan*/  mt9d112_init_client (struct i2c_client*) ; 
 int /*<<< orphan*/ * mt9d112_sensorw ; 

__attribute__((used)) static int mt9d112_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	int rc = 0;
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		rc = -ENOTSUPP;
		goto probe_failure;
	}

	mt9d112_sensorw =
		kzalloc(sizeof(struct mt9d112_work), GFP_KERNEL);

	if (!mt9d112_sensorw) {
		rc = -ENOMEM;
		goto probe_failure;
	}

	i2c_set_clientdata(client, mt9d112_sensorw);
	mt9d112_init_client(client);
	mt9d112_client = client;

	CDBG("mt9d112_probe succeeded!\n");

	return 0;

probe_failure:
	kfree(mt9d112_sensorw);
	mt9d112_sensorw = NULL;
	CDBG("mt9d112_probe failed!\n");
	return rc;
}