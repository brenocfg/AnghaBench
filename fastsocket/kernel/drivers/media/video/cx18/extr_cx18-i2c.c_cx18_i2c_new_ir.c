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
typedef  unsigned short u8 ;
typedef  int u32 ;
struct i2c_board_info {struct IR_i2c_init_data* platform_data; int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;
struct IR_i2c_init_data {int /*<<< orphan*/  name; int /*<<< orphan*/  type; int /*<<< orphan*/  internal_get_key_func; int /*<<< orphan*/  ir_codes; } ;
struct cx18 {int /*<<< orphan*/  card_name; struct IR_i2c_init_data ir_i2c_init_data; } ;

/* Variables and functions */
#define  CX18_HW_Z8F0811_IR_RX_HAUP 128 
 unsigned short I2C_CLIENT_END ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  IR_KBD_GET_KEY_HAUP_XVR ; 
 int /*<<< orphan*/  RC_MAP_HAUPPAUGE_NEW ; 
 int /*<<< orphan*/  RC_TYPE_RC5 ; 
 int /*<<< orphan*/ * i2c_new_probed_device (struct i2c_adapter*,struct i2c_board_info*,unsigned short*) ; 
 int /*<<< orphan*/  memset (struct i2c_board_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cx18_i2c_new_ir(struct cx18 *cx, struct i2c_adapter *adap, u32 hw,
			   const char *type, u8 addr)
{
	struct i2c_board_info info;
	struct IR_i2c_init_data *init_data = &cx->ir_i2c_init_data;
	unsigned short addr_list[2] = { addr, I2C_CLIENT_END };

	memset(&info, 0, sizeof(struct i2c_board_info));
	strlcpy(info.type, type, I2C_NAME_SIZE);

	/* Our default information for ir-kbd-i2c.c to use */
	switch (hw) {
	case CX18_HW_Z8F0811_IR_RX_HAUP:
		init_data->ir_codes = RC_MAP_HAUPPAUGE_NEW;
		init_data->internal_get_key_func = IR_KBD_GET_KEY_HAUP_XVR;
		init_data->type = RC_TYPE_RC5;
		init_data->name = cx->card_name;
		info.platform_data = init_data;
		break;
	}

	return i2c_new_probed_device(adap, &info, addr_list) == NULL ?
	       -1 : 0;
}