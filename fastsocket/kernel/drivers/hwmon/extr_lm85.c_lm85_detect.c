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
struct i2c_client {int addr; struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int LM85_COMPANY_ANALOG_DEV ; 
 int LM85_COMPANY_NATIONAL ; 
 int LM85_COMPANY_SMSC ; 
 int /*<<< orphan*/  LM85_REG_COMPANY ; 
 int /*<<< orphan*/  LM85_REG_VERSTEP ; 
#define  LM85_VERSTEP_ADM1027 146 
#define  LM85_VERSTEP_ADT7463 145 
#define  LM85_VERSTEP_ADT7463C 144 
#define  LM85_VERSTEP_ADT7468_1 143 
#define  LM85_VERSTEP_ADT7468_2 142 
#define  LM85_VERSTEP_EMC6D100_A0 141 
#define  LM85_VERSTEP_EMC6D100_A1 140 
#define  LM85_VERSTEP_EMC6D102 139 
 int LM85_VERSTEP_GENERIC ; 
 int LM85_VERSTEP_GENERIC2 ; 
#define  LM85_VERSTEP_LM85B 138 
#define  LM85_VERSTEP_LM85C 137 
#define  LM85_VERSTEP_LM96000_1 136 
#define  LM85_VERSTEP_LM96000_2 135 
 int LM85_VERSTEP_VMASK ; 
#define  adm1027 134 
#define  adt7463 133 
#define  adt7468 132 
 int any_chip ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
#define  emc6d100 131 
#define  emc6d102 130 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm85_is_fake (struct i2c_client*) ; 
 int lm85_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
#define  lm85b 129 
#define  lm85c 128 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm85_detect(struct i2c_client *client, int kind,
		       struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	int address = client->addr;
	const char *type_name;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) {
		/* We need to be able to do byte I/O */
		return -ENODEV;
	}

	/* If auto-detecting, determine the chip type */
	if (kind < 0) {
		int company = lm85_read_value(client, LM85_REG_COMPANY);
		int verstep = lm85_read_value(client, LM85_REG_VERSTEP);

		dev_dbg(&adapter->dev, "Detecting device at 0x%02x with "
			"COMPANY: 0x%02x and VERSTEP: 0x%02x\n",
			address, company, verstep);

		/* All supported chips have the version in common */
		if ((verstep & LM85_VERSTEP_VMASK) != LM85_VERSTEP_GENERIC &&
		    (verstep & LM85_VERSTEP_VMASK) != LM85_VERSTEP_GENERIC2) {
			dev_dbg(&adapter->dev, "Autodetection failed: "
				"unsupported version\n");
			return -ENODEV;
		}
		kind = any_chip;

		/* Now, refine the detection */
		if (company == LM85_COMPANY_NATIONAL) {
			switch (verstep) {
			case LM85_VERSTEP_LM85C:
				kind = lm85c;
				break;
			case LM85_VERSTEP_LM85B:
				kind = lm85b;
				break;
			case LM85_VERSTEP_LM96000_1:
			case LM85_VERSTEP_LM96000_2:
				/* Check for Winbond WPCD377I */
				if (lm85_is_fake(client)) {
					dev_dbg(&adapter->dev,
						"Found Winbond WPCD377I, "
						"ignoring\n");
					return -ENODEV;
				}
				break;
			}
		} else if (company == LM85_COMPANY_ANALOG_DEV) {
			switch (verstep) {
			case LM85_VERSTEP_ADM1027:
				kind = adm1027;
				break;
			case LM85_VERSTEP_ADT7463:
			case LM85_VERSTEP_ADT7463C:
				kind = adt7463;
				break;
			case LM85_VERSTEP_ADT7468_1:
			case LM85_VERSTEP_ADT7468_2:
				kind = adt7468;
				break;
			}
		} else if (company == LM85_COMPANY_SMSC) {
			switch (verstep) {
			case LM85_VERSTEP_EMC6D100_A0:
			case LM85_VERSTEP_EMC6D100_A1:
				/* Note: we can't tell a '100 from a '101 */
				kind = emc6d100;
				break;
			case LM85_VERSTEP_EMC6D102:
				kind = emc6d102;
				break;
			}
		} else {
			dev_dbg(&adapter->dev, "Autodetection failed: "
				"unknown vendor\n");
			return -ENODEV;
		}
	}

	switch (kind) {
	case lm85b:
		type_name = "lm85b";
		break;
	case lm85c:
		type_name = "lm85c";
		break;
	case adm1027:
		type_name = "adm1027";
		break;
	case adt7463:
		type_name = "adt7463";
		break;
	case adt7468:
		type_name = "adt7468";
		break;
	case emc6d100:
		type_name = "emc6d100";
		break;
	case emc6d102:
		type_name = "emc6d102";
		break;
	default:
		type_name = "lm85";
	}
	strlcpy(info->type, type_name, I2C_NAME_SIZE);

	return 0;
}