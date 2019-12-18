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
typedef  scalar_t__ u8 ;
struct i2c_client {int /*<<< orphan*/  addr; struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct device {int dummy; } ;
struct i2c_adapter {struct device dev; } ;

/* Variables and functions */
 scalar_t__ DME1737_COMPANY_SMSC ; 
 int /*<<< orphan*/  DME1737_REG_COMPANY ; 
 int /*<<< orphan*/  DME1737_REG_VERSTEP ; 
 scalar_t__ DME1737_VERSTEP ; 
 scalar_t__ DME1737_VERSTEP_MASK ; 
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 scalar_t__ SCH5027_VERSTEP ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int dme1737 ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int sch5027 ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dme1737_i2c_detect(struct i2c_client *client, int kind,
			      struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	struct device *dev = &adapter->dev;
	u8 company, verstep = 0;
	const char *name;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) {
		return -ENODEV;
	}

	/* A negative kind means that the driver was loaded with no force
	 * parameter (default), so we must identify the chip. */
	if (kind < 0) {
		company = i2c_smbus_read_byte_data(client, DME1737_REG_COMPANY);
		verstep = i2c_smbus_read_byte_data(client, DME1737_REG_VERSTEP);

		if (company == DME1737_COMPANY_SMSC &&
		    (verstep & DME1737_VERSTEP_MASK) == DME1737_VERSTEP) {
			kind = dme1737;
		} else if (company == DME1737_COMPANY_SMSC &&
			   verstep == SCH5027_VERSTEP) {
			kind = sch5027;
		} else {
			return -ENODEV;
		}
	}

	if (kind == sch5027) {
		name = "sch5027";
	} else {
		kind = dme1737;
		name = "dme1737";
	}

	dev_info(dev, "Found a %s chip at 0x%02x (rev 0x%02x).\n",
		 kind == sch5027 ? "SCH5027" : "DME1737", client->addr,
		 verstep);
	strlcpy(info->type, name, I2C_NAME_SIZE);

	return 0;
}