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
struct i2c_board_info {char* name; unsigned short addr; struct i2c_board_info* platform_data; int /*<<< orphan*/  internal_get_key_func; int /*<<< orphan*/  type; int /*<<< orphan*/  ir_codes; int /*<<< orphan*/  get_key; } ;
struct cx88_core {scalar_t__ i2c_rc; int boardnr; int /*<<< orphan*/  i2c_adap; struct i2c_board_info init_data; } ;

/* Variables and functions */
#define  CX88_BOARD_LEADTEK_PVR2000 128 
 int I2C_CLIENT_END ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  I2C_SMBUS_QUICK ; 
 int /*<<< orphan*/  I2C_SMBUS_READ ; 
 int /*<<< orphan*/  IR_KBD_GET_KEY_HAUP_XVR ; 
 int /*<<< orphan*/  RC_MAP_EMPTY ; 
 int /*<<< orphan*/  RC_MAP_HAUPPAUGE_NEW ; 
 int /*<<< orphan*/  RC_TYPE_RC5 ; 
 int /*<<< orphan*/  RC_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  get_key_pvr2000 ; 
 int /*<<< orphan*/  i2c_new_device (int /*<<< orphan*/ *,struct i2c_board_info*) ; 
 scalar_t__ i2c_smbus_xfer (int /*<<< orphan*/ *,unsigned short const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct i2c_board_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void cx88_i2c_init_ir(struct cx88_core *core)
{
	struct i2c_board_info info;
	const unsigned short default_addr_list[] = {
		0x18, 0x6b, 0x71,
		I2C_CLIENT_END
	};
	const unsigned short pvr2000_addr_list[] = {
		0x18, 0x1a,
		I2C_CLIENT_END
	};
	const unsigned short *addr_list = default_addr_list;
	const unsigned short *addrp;
	/* Instantiate the IR receiver device, if present */
	if (0 != core->i2c_rc)
		return;

	memset(&info, 0, sizeof(struct i2c_board_info));
	strlcpy(info.type, "ir_video", I2C_NAME_SIZE);

	switch (core->boardnr) {
	case CX88_BOARD_LEADTEK_PVR2000:
		addr_list = pvr2000_addr_list;
		core->init_data.name = "cx88 Leadtek PVR 2000 remote";
		core->init_data.type = RC_TYPE_UNKNOWN;
		core->init_data.get_key = get_key_pvr2000;
		core->init_data.ir_codes = RC_MAP_EMPTY;
		break;
	}

	/*
	 * We can't call i2c_new_probed_device() because it uses
	 * quick writes for probing and at least some RC receiver
	 * devices only reply to reads.
	 * Also, Hauppauge XVR needs to be specified, as address 0x71
	 * conflicts with another remote type used with saa7134
	 */
	for (addrp = addr_list; *addrp != I2C_CLIENT_END; addrp++) {
		info.platform_data = NULL;
		memset(&core->init_data, 0, sizeof(core->init_data));

		if (*addrp == 0x71) {
			/* Hauppauge XVR */
			core->init_data.name = "cx88 Hauppauge XVR remote";
			core->init_data.ir_codes = RC_MAP_HAUPPAUGE_NEW;
			core->init_data.type = RC_TYPE_RC5;
			core->init_data.internal_get_key_func = IR_KBD_GET_KEY_HAUP_XVR;

			info.platform_data = &core->init_data;
		}
		if (i2c_smbus_xfer(&core->i2c_adap, *addrp, 0,
					I2C_SMBUS_READ, 0,
					I2C_SMBUS_QUICK, NULL) >= 0) {
			info.addr = *addrp;
			i2c_new_device(&core->i2c_adap, &info);
			break;
		}
	}
}