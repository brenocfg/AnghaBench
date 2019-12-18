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
struct i2c_driver {int class; int /*<<< orphan*/  detect; struct i2c_client_address_data* address_data; } ;
struct i2c_client_address_data {unsigned short** forces; unsigned short const* probe; unsigned short const* normal_i2c; unsigned short const* ignore; } ;
struct i2c_client {unsigned short addr; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int class; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned short const ANY_I2C_BUS ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned short const I2C_CLIENT_END ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_QUICK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,unsigned short const,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int i2c_adapter_id (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_detect_address (struct i2c_client*,int,struct i2c_driver*) ; 
 int /*<<< orphan*/  kfree (struct i2c_client*) ; 
 struct i2c_client* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_detect(struct i2c_adapter *adapter, struct i2c_driver *driver)
{
	const struct i2c_client_address_data *address_data;
	struct i2c_client *temp_client;
	int i, err = 0;
	int adap_id = i2c_adapter_id(adapter);

	address_data = driver->address_data;
	if (!driver->detect || !address_data)
		return 0;

	/* Set up a temporary client to help detect callback */
	temp_client = kzalloc(sizeof(struct i2c_client), GFP_KERNEL);
	if (!temp_client)
		return -ENOMEM;
	temp_client->adapter = adapter;

	/* Force entries are done first, and are not affected by ignore
	   entries */
	if (address_data->forces) {
		const unsigned short * const *forces = address_data->forces;
		int kind;

		for (kind = 0; forces[kind]; kind++) {
			for (i = 0; forces[kind][i] != I2C_CLIENT_END;
			     i += 2) {
				if (forces[kind][i] == adap_id
				 || forces[kind][i] == ANY_I2C_BUS) {
					dev_dbg(&adapter->dev, "found force "
						"parameter for adapter %d, "
						"addr 0x%02x, kind %d\n",
						adap_id, forces[kind][i + 1],
						kind);
					temp_client->addr = forces[kind][i + 1];
					err = i2c_detect_address(temp_client,
						kind, driver);
					if (err)
						goto exit_free;
				}
			}
		}
	}

	/* Stop here if the classes do not match */
	if (!(adapter->class & driver->class))
		goto exit_free;

	/* Stop here if we can't use SMBUS_QUICK */
	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_QUICK)) {
		if (address_data->probe[0] == I2C_CLIENT_END
		 && address_data->normal_i2c[0] == I2C_CLIENT_END)
			goto exit_free;

		dev_warn(&adapter->dev, "SMBus Quick command not supported, "
			 "can't probe for chips\n");
		err = -EOPNOTSUPP;
		goto exit_free;
	}

	/* Probe entries are done second, and are not affected by ignore
	   entries either */
	for (i = 0; address_data->probe[i] != I2C_CLIENT_END; i += 2) {
		if (address_data->probe[i] == adap_id
		 || address_data->probe[i] == ANY_I2C_BUS) {
			dev_dbg(&adapter->dev, "found probe parameter for "
				"adapter %d, addr 0x%02x\n", adap_id,
				address_data->probe[i + 1]);
			temp_client->addr = address_data->probe[i + 1];
			err = i2c_detect_address(temp_client, -1, driver);
			if (err)
				goto exit_free;
		}
	}

	/* Normal entries are done last, unless shadowed by an ignore entry */
	for (i = 0; address_data->normal_i2c[i] != I2C_CLIENT_END; i += 1) {
		int j, ignore;

		ignore = 0;
		for (j = 0; address_data->ignore[j] != I2C_CLIENT_END;
		     j += 2) {
			if ((address_data->ignore[j] == adap_id ||
			     address_data->ignore[j] == ANY_I2C_BUS)
			 && address_data->ignore[j + 1]
			    == address_data->normal_i2c[i]) {
				dev_dbg(&adapter->dev, "found ignore "
					"parameter for adapter %d, "
					"addr 0x%02x\n", adap_id,
					address_data->ignore[j + 1]);
				ignore = 1;
				break;
			}
		}
		if (ignore)
			continue;

		dev_dbg(&adapter->dev, "found normal entry for adapter %d, "
			"addr 0x%02x\n", adap_id,
			address_data->normal_i2c[i]);
		temp_client->addr = address_data->normal_i2c[i];
		err = i2c_detect_address(temp_client, -1, driver);
		if (err)
			goto exit_free;
	}

 exit_free:
	kfree(temp_client);
	return err;
}