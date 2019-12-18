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
struct i2c_client {struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  FSCHMD_REG_IDENT_0 ; 
 int /*<<< orphan*/  FSCHMD_REG_IDENT_1 ; 
 int /*<<< orphan*/  FSCHMD_REG_IDENT_2 ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int fschds ; 
 int fscher ; 
 int fschmd ; 
 TYPE_1__* fschmd_id ; 
 int fschrc ; 
 int fscpos ; 
 int fscscy ; 
 int fscsyl ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 char i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fschmd_detect(struct i2c_client *client, int kind,
			 struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	/* Detect & Identify the chip */
	if (kind <= 0) {
		char id[4];

		id[0] = i2c_smbus_read_byte_data(client,
				FSCHMD_REG_IDENT_0);
		id[1] = i2c_smbus_read_byte_data(client,
				FSCHMD_REG_IDENT_1);
		id[2] = i2c_smbus_read_byte_data(client,
				FSCHMD_REG_IDENT_2);
		id[3] = '\0';

		if (!strcmp(id, "PEG"))
			kind = fscpos;
		else if (!strcmp(id, "HER"))
			kind = fscher;
		else if (!strcmp(id, "SCY"))
			kind = fscscy;
		else if (!strcmp(id, "HRC"))
			kind = fschrc;
		else if (!strcmp(id, "HMD"))
			kind = fschmd;
		else if (!strcmp(id, "HDS"))
			kind = fschds;
		else if (!strcmp(id, "SYL"))
			kind = fscsyl;
		else
			return -ENODEV;
	}

	strlcpy(info->type, fschmd_id[kind - 1].name, I2C_NAME_SIZE);

	return 0;
}