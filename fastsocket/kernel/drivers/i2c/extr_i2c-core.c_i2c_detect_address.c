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
struct TYPE_2__ {char* name; } ;
struct i2c_driver {int (* detect ) (struct i2c_client*,int,struct i2c_board_info*) ;int /*<<< orphan*/  clients; TYPE_1__ driver; } ;
struct i2c_client {int addr; int /*<<< orphan*/  detected; struct i2c_adapter* adapter; } ;
struct i2c_board_info {int addr; char* type; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  I2C_SMBUS_QUICK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ i2c_check_addr (struct i2c_adapter*,int) ; 
 struct i2c_client* i2c_new_device (struct i2c_adapter*,struct i2c_board_info*) ; 
 scalar_t__ i2c_smbus_xfer (struct i2c_adapter*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct i2c_board_info*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct i2c_client*,int,struct i2c_board_info*) ; 

__attribute__((used)) static int i2c_detect_address(struct i2c_client *temp_client, int kind,
			      struct i2c_driver *driver)
{
	struct i2c_board_info info;
	struct i2c_adapter *adapter = temp_client->adapter;
	int addr = temp_client->addr;
	int err;

	/* Make sure the address is valid */
	if (addr < 0x03 || addr > 0x77) {
		dev_warn(&adapter->dev, "Invalid probe address 0x%02x\n",
			 addr);
		return -EINVAL;
	}

	/* Skip if already in use */
	if (i2c_check_addr(adapter, addr))
		return 0;

	/* Make sure there is something at this address, unless forced */
	if (kind < 0) {
		if (i2c_smbus_xfer(adapter, addr, 0, 0, 0,
				   I2C_SMBUS_QUICK, NULL) < 0)
			return 0;

		/* prevent 24RF08 corruption */
		if ((addr & ~0x0f) == 0x50)
			i2c_smbus_xfer(adapter, addr, 0, 0, 0,
				       I2C_SMBUS_QUICK, NULL);
	}

	/* Finally call the custom detection function */
	memset(&info, 0, sizeof(struct i2c_board_info));
	info.addr = addr;
	err = driver->detect(temp_client, kind, &info);
	if (err) {
		/* -ENODEV is returned if the detection fails. We catch it
		   here as this isn't an error. */
		return err == -ENODEV ? 0 : err;
	}

	/* Consistency check */
	if (info.type[0] == '\0') {
		dev_err(&adapter->dev, "%s detection function provided "
			"no name for 0x%x\n", driver->driver.name,
			addr);
	} else {
		struct i2c_client *client;

		/* Detection succeeded, instantiate the device */
		dev_dbg(&adapter->dev, "Creating %s at 0x%02x\n",
			info.type, info.addr);
		client = i2c_new_device(adapter, &info);
		if (client)
			list_add_tail(&client->detected, &driver->clients);
		else
			dev_err(&adapter->dev, "Failed creating %s at 0x%02x\n",
				info.type, info.addr);
	}
	return 0;
}