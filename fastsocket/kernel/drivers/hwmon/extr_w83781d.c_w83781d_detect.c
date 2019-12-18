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
struct w83781d_data {int /*<<< orphan*/  update_lock; } ;
struct i2c_client {int addr; struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  W83781D_REG_BANK ; 
 int /*<<< orphan*/  W83781D_REG_CHIPMAN ; 
 int /*<<< orphan*/  W83781D_REG_CONFIG ; 
 int /*<<< orphan*/  W83781D_REG_I2C_ADDR ; 
 int /*<<< orphan*/  W83781D_REG_WCHIPID ; 
 int as99127f ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int w83781d ; 
 scalar_t__ w83781d_alias_detect (struct i2c_client*,int) ; 
 struct w83781d_data* w83781d_data_if_isa () ; 
 int w83782d ; 
 int w83783s ; 

__attribute__((used)) static int
w83781d_detect(struct i2c_client *client, int kind,
	       struct i2c_board_info *info)
{
	int val1 = 0, val2;
	struct w83781d_data *isa = w83781d_data_if_isa();
	struct i2c_adapter *adapter = client->adapter;
	int address = client->addr;
	const char *client_name = "";
	enum vendor { winbond, asus } vendid;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	/* We block updates of the ISA device to minimize the risk of
	   concurrent access to the same W83781D chip through different
	   interfaces. */
	if (isa)
		mutex_lock(&isa->update_lock);

	/* The w8378?d may be stuck in some other bank than bank 0. This may
	   make reading other information impossible. Specify a force=... or
	   force_*=... parameter, and the Winbond will be reset to the right
	   bank. */
	if (kind < 0) {
		if (i2c_smbus_read_byte_data
		    (client, W83781D_REG_CONFIG) & 0x80) {
			dev_dbg(&adapter->dev, "Detection of w83781d chip "
				"failed at step 3\n");
			goto err_nodev;
		}
		val1 = i2c_smbus_read_byte_data(client, W83781D_REG_BANK);
		val2 = i2c_smbus_read_byte_data(client, W83781D_REG_CHIPMAN);
		/* Check for Winbond or Asus ID if in bank 0 */
		if ((!(val1 & 0x07)) &&
		    (((!(val1 & 0x80)) && (val2 != 0xa3) && (val2 != 0xc3))
		     || ((val1 & 0x80) && (val2 != 0x5c) && (val2 != 0x12)))) {
			dev_dbg(&adapter->dev, "Detection of w83781d chip "
				"failed at step 4\n");
			goto err_nodev;
		}
		/* If Winbond SMBus, check address at 0x48.
		   Asus doesn't support, except for as99127f rev.2 */
		if ((!(val1 & 0x80) && (val2 == 0xa3)) ||
		    ((val1 & 0x80) && (val2 == 0x5c))) {
			if (i2c_smbus_read_byte_data
			    (client, W83781D_REG_I2C_ADDR) != address) {
				dev_dbg(&adapter->dev, "Detection of w83781d "
					"chip failed at step 5\n");
				goto err_nodev;
			}
		}
	}

	/* We have either had a force parameter, or we have already detected the
	   Winbond. Put it now into bank 0 and Vendor ID High Byte */
	i2c_smbus_write_byte_data(client, W83781D_REG_BANK,
		(i2c_smbus_read_byte_data(client, W83781D_REG_BANK)
		 & 0x78) | 0x80);

	/* Determine the chip type. */
	if (kind <= 0) {
		/* get vendor ID */
		val2 = i2c_smbus_read_byte_data(client, W83781D_REG_CHIPMAN);
		if (val2 == 0x5c)
			vendid = winbond;
		else if (val2 == 0x12)
			vendid = asus;
		else {
			dev_dbg(&adapter->dev, "w83781d chip vendor is "
				"neither Winbond nor Asus\n");
			goto err_nodev;
		}

		val1 = i2c_smbus_read_byte_data(client, W83781D_REG_WCHIPID);
		if ((val1 == 0x10 || val1 == 0x11) && vendid == winbond)
			kind = w83781d;
		else if (val1 == 0x30 && vendid == winbond)
			kind = w83782d;
		else if (val1 == 0x40 && vendid == winbond && address == 0x2d)
			kind = w83783s;
		else if (val1 == 0x31)
			kind = as99127f;
		else {
			if (kind == 0)
				dev_warn(&adapter->dev, "Ignoring 'force' "
					 "parameter for unknown chip at "
					 "address 0x%02x\n", address);
			goto err_nodev;
		}

		if ((kind == w83781d || kind == w83782d)
		 && w83781d_alias_detect(client, val1)) {
			dev_dbg(&adapter->dev, "Device at 0x%02x appears to "
				"be the same as ISA device\n", address);
			goto err_nodev;
		}
	}

	if (isa)
		mutex_unlock(&isa->update_lock);

	if (kind == w83781d) {
		client_name = "w83781d";
	} else if (kind == w83782d) {
		client_name = "w83782d";
	} else if (kind == w83783s) {
		client_name = "w83783s";
	} else if (kind == as99127f) {
		client_name = "as99127f";
	}

	strlcpy(info->type, client_name, I2C_NAME_SIZE);

	return 0;

 err_nodev:
	if (isa)
		mutex_unlock(&isa->update_lock);
	return -ENODEV;
}