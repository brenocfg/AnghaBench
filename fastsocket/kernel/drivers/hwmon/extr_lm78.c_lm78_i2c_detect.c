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
struct lm78_data {int /*<<< orphan*/  update_lock; } ;
struct i2c_client {int addr; struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int LM78_REG_CHIPID ; 
 int LM78_REG_CONFIG ; 
 int LM78_REG_I2C_ADDR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_adapter_id (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 int lm78 ; 
 scalar_t__ lm78_alias_detect (struct i2c_client*,int) ; 
 struct lm78_data* lm78_data_if_isa () ; 
#define  lm79 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm78_i2c_detect(struct i2c_client *client, int kind,
			   struct i2c_board_info *info)
{
	int i;
	struct lm78_data *isa = lm78_data_if_isa();
	const char *client_name;
	struct i2c_adapter *adapter = client->adapter;
	int address = client->addr;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	/* We block updates of the ISA device to minimize the risk of
	   concurrent access to the same LM78 chip through different
	   interfaces. */
	if (isa)
		mutex_lock(&isa->update_lock);

	if (kind < 0) {
		if ((i2c_smbus_read_byte_data(client, LM78_REG_CONFIG) & 0x80)
		 || i2c_smbus_read_byte_data(client, LM78_REG_I2C_ADDR)
		    != address)
			goto err_nodev;

		/* Explicitly prevent the misdetection of Winbond chips */
		i = i2c_smbus_read_byte_data(client, 0x4f);
		if (i == 0xa3 || i == 0x5c)
			goto err_nodev;
	}

	/* Determine the chip type. */
	if (kind <= 0) {
		i = i2c_smbus_read_byte_data(client, LM78_REG_CHIPID);
		if (i == 0x00 || i == 0x20	/* LM78 */
		 || i == 0x40)			/* LM78-J */
			kind = lm78;
		else if ((i & 0xfe) == 0xc0)
			kind = lm79;
		else {
			if (kind == 0)
				dev_warn(&adapter->dev, "Ignoring 'force' "
					"parameter for unknown chip at "
					"adapter %d, address 0x%02x\n",
					i2c_adapter_id(adapter), address);
			goto err_nodev;
		}

		if (lm78_alias_detect(client, i)) {
			dev_dbg(&adapter->dev, "Device at 0x%02x appears to "
				"be the same as ISA device\n", address);
			goto err_nodev;
		}
	}

	if (isa)
		mutex_unlock(&isa->update_lock);

	switch (kind) {
	case lm79:
		client_name = "lm79";
		break;
	default:
		client_name = "lm78";
	}
	strlcpy(info->type, client_name, I2C_NAME_SIZE);

	return 0;

 err_nodev:
	if (isa)
		mutex_unlock(&isa->update_lock);
	return -ENODEV;
}