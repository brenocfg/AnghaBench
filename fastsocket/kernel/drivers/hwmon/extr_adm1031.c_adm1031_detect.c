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
struct i2c_client {struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int adm1030 ; 
 int adm1031 ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adm1031_detect(struct i2c_client *client, int kind,
			  struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	const char *name = "";

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	if (kind < 0) {
		int id, co;
		id = i2c_smbus_read_byte_data(client, 0x3d);
		co = i2c_smbus_read_byte_data(client, 0x3e);

		if (!((id == 0x31 || id == 0x30) && co == 0x41))
			return -ENODEV;
		kind = (id == 0x30) ? adm1030 : adm1031;
	}

	if (kind <= 0)
		kind = adm1031;

	/* Given the detected chip type, set the chip name and the
	 * auto fan control helper table. */
	if (kind == adm1030) {
		name = "adm1030";
	} else if (kind == adm1031) {
		name = "adm1031";
	}
	strlcpy(info->type, name, I2C_NAME_SIZE);

	return 0;
}