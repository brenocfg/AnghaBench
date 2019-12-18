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
struct IR_i2c_init_data {char* name; void* type; int /*<<< orphan*/  ir_codes; int /*<<< orphan*/  get_key; int /*<<< orphan*/  internal_get_key_func; } ;
struct i2c_adapter {int dummy; } ;
struct ivtv {int hw_flags; char* card_name; struct IR_i2c_init_data ir_i2c_init_data; struct i2c_adapter i2c_adap; } ;
struct i2c_board_info {int /*<<< orphan*/  type; struct IR_i2c_init_data* platform_data; } ;

/* Variables and functions */
 unsigned short I2C_CLIENT_END ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  IR_KBD_GET_KEY_AVERMEDIA_CARDBUS ; 
 int /*<<< orphan*/  IR_KBD_GET_KEY_HAUP ; 
 int /*<<< orphan*/  IR_KBD_GET_KEY_HAUP_XVR ; 
#define  IVTV_HW_I2C_IR_RX_ADAPTEC 132 
#define  IVTV_HW_I2C_IR_RX_AVER 131 
#define  IVTV_HW_I2C_IR_RX_HAUP_EXT 130 
#define  IVTV_HW_I2C_IR_RX_HAUP_INT 129 
 int IVTV_HW_IR_RX_ANY ; 
 int IVTV_HW_IR_TX_ANY ; 
#define  IVTV_HW_Z8F0811_IR_RX_HAUP 128 
 int /*<<< orphan*/  RC_MAP_AVERMEDIA_CARDBUS ; 
 int /*<<< orphan*/  RC_MAP_EMPTY ; 
 int /*<<< orphan*/  RC_MAP_HAUPPAUGE_NEW ; 
 int /*<<< orphan*/  RC_MAP_RC5_TV ; 
 void* RC_TYPE_OTHER ; 
 void* RC_TYPE_RC5 ; 
 void* RC_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  get_key_adaptec ; 
 int /*<<< orphan*/ * i2c_new_probed_device (struct i2c_adapter*,struct i2c_board_info*,unsigned short*) ; 
 int /*<<< orphan*/  memset (struct i2c_board_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ivtv_i2c_new_ir(struct ivtv *itv, u32 hw, const char *type, u8 addr)
{
	struct i2c_board_info info;
	struct i2c_adapter *adap = &itv->i2c_adap;
	struct IR_i2c_init_data *init_data = &itv->ir_i2c_init_data;
	unsigned short addr_list[2] = { addr, I2C_CLIENT_END };

	/* Only allow one IR transmitter to be registered per board */
	if (hw & IVTV_HW_IR_TX_ANY) {
		if (itv->hw_flags & IVTV_HW_IR_TX_ANY)
			return -1;
		memset(&info, 0, sizeof(struct i2c_board_info));
		strlcpy(info.type, type, I2C_NAME_SIZE);
		return i2c_new_probed_device(adap, &info, addr_list)
							   == NULL ? -1 : 0;
	}

	/* Only allow one IR receiver to be registered per board */
	if (itv->hw_flags & IVTV_HW_IR_RX_ANY)
		return -1;

	/* Our default information for ir-kbd-i2c.c to use */
	switch (hw) {
	case IVTV_HW_I2C_IR_RX_AVER:
		init_data->ir_codes = RC_MAP_AVERMEDIA_CARDBUS;
		init_data->internal_get_key_func =
					IR_KBD_GET_KEY_AVERMEDIA_CARDBUS;
		init_data->type = RC_TYPE_OTHER;
		init_data->name = "AVerMedia AVerTV card";
		break;
	case IVTV_HW_I2C_IR_RX_HAUP_EXT:
	case IVTV_HW_I2C_IR_RX_HAUP_INT:
		/* Default to old black remote */
		init_data->ir_codes = RC_MAP_RC5_TV;
		init_data->internal_get_key_func = IR_KBD_GET_KEY_HAUP;
		init_data->type = RC_TYPE_RC5;
		init_data->name = itv->card_name;
		break;
	case IVTV_HW_Z8F0811_IR_RX_HAUP:
		/* Default to grey remote */
		init_data->ir_codes = RC_MAP_HAUPPAUGE_NEW;
		init_data->internal_get_key_func = IR_KBD_GET_KEY_HAUP_XVR;
		init_data->type = RC_TYPE_RC5;
		init_data->name = itv->card_name;
		break;
	case IVTV_HW_I2C_IR_RX_ADAPTEC:
		init_data->get_key = get_key_adaptec;
		init_data->name = itv->card_name;
		/* FIXME: The protocol and RC_MAP needs to be corrected */
		init_data->ir_codes = RC_MAP_EMPTY;
		init_data->type = RC_TYPE_UNKNOWN;
		break;
	}

	memset(&info, 0, sizeof(struct i2c_board_info));
	info.platform_data = init_data;
	strlcpy(info.type, type, I2C_NAME_SIZE);

	return i2c_new_probed_device(adap, &info, addr_list) == NULL ?
	       -1 : 0;
}