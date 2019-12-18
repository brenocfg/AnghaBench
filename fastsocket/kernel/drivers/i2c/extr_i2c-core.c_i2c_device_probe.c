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
struct i2c_driver {int (* probe ) (struct i2c_client*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  id_table; } ;
struct i2c_client {int flags; struct i2c_driver* driver; int /*<<< orphan*/  dev; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int ENODEV ; 
 int I2C_CLIENT_WAKE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  device_can_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_match_id (int /*<<< orphan*/ ,struct i2c_client*) ; 
 struct i2c_client* i2c_verify_client (struct device*) ; 
 int stub1 (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct i2c_driver* to_i2c_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_device_probe(struct device *dev)
{
	struct i2c_client	*client = i2c_verify_client(dev);
	struct i2c_driver	*driver;
	int status;

	if (!client)
		return 0;

	driver = to_i2c_driver(dev->driver);
	if (!driver->probe || !driver->id_table)
		return -ENODEV;
	client->driver = driver;
	if (!device_can_wakeup(&client->dev))
		device_init_wakeup(&client->dev,
					client->flags & I2C_CLIENT_WAKE);
	dev_dbg(dev, "probe\n");

	status = driver->probe(client, i2c_match_id(driver->id_table, client));
	if (status)
		client->driver = NULL;
	return status;
}