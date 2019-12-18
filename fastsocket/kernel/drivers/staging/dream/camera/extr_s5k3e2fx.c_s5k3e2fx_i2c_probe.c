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
struct s5k3e2fx_work {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*,...) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct i2c_client* s5k3e2fx_client ; 
 int /*<<< orphan*/  s5k3e2fx_init_client (struct i2c_client*) ; 
 int /*<<< orphan*/  s5k3e2fx_sensorw ; 

__attribute__((used)) static int s5k3e2fx_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	int rc = 0;
	CDBG("s5k3e2fx_probe called!\n");

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		CDBG("i2c_check_functionality failed\n");
		goto probe_failure;
	}

	s5k3e2fx_sensorw = kzalloc(sizeof(struct s5k3e2fx_work), GFP_KERNEL);
	if (!s5k3e2fx_sensorw) {
		CDBG("kzalloc failed.\n");
		rc = -ENOMEM;
		goto probe_failure;
	}

	i2c_set_clientdata(client, s5k3e2fx_sensorw);
	s5k3e2fx_init_client(client);
	s5k3e2fx_client = client;

	mdelay(50);

	CDBG("s5k3e2fx_probe successed! rc = %d\n", rc);
	return 0;

probe_failure:
	CDBG("s5k3e2fx_probe failed! rc = %d\n", rc);
	return rc;
}