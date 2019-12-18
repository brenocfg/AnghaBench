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
struct i2c_board_info {char* name; struct i2c_board_info* platform_data; int /*<<< orphan*/  get_key; int /*<<< orphan*/  ir_codes; int /*<<< orphan*/  type; } ;
struct em28xx {int model; int /*<<< orphan*/  i2c_adap; struct i2c_board_info init_data; } ;

/* Variables and functions */
#define  EM2800_BOARD_TERRATEC_CINERGY_200 132 
#define  EM2820_BOARD_HAUPPAUGE_WINTV_USB_2 131 
#define  EM2820_BOARD_LEADTEK_WINFAST_USBII_DELUXE 130 
#define  EM2820_BOARD_PINNACLE_USB_2 129 
#define  EM2820_BOARD_TERRATEC_CINERGY_250 128 
 int I2C_CLIENT_END ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  RC_MAP_EM_TERRATEC ; 
 int /*<<< orphan*/  RC_MAP_PINNACLE_GREY ; 
 int /*<<< orphan*/  RC_MAP_RC5_HAUPPAUGE_NEW ; 
 int /*<<< orphan*/  RC_MAP_WINFAST_USBII_DELUXE ; 
 scalar_t__ disable_ir ; 
 int /*<<< orphan*/  em28xx_get_key_em_haup ; 
 int /*<<< orphan*/  em28xx_get_key_pinnacle_usb_grey ; 
 int /*<<< orphan*/  em28xx_get_key_terratec ; 
 int /*<<< orphan*/  em28xx_get_key_winfast_usbii_deluxe ; 
 int /*<<< orphan*/  i2c_new_probed_device (int /*<<< orphan*/ *,struct i2c_board_info*,unsigned short const*) ; 
 int /*<<< orphan*/  memset (struct i2c_board_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void em28xx_register_i2c_ir(struct em28xx *dev)
{
	/* Leadtek winfast tv USBII deluxe can find a non working IR-device */
	/* at address 0x18, so if that address is needed for another board in */
	/* the future, please put it after 0x1f. */
	struct i2c_board_info info;
	const unsigned short addr_list[] = {
		 0x1f, 0x30, 0x47, I2C_CLIENT_END
	};

	if (disable_ir)
		return;

	memset(&info, 0, sizeof(struct i2c_board_info));
	memset(&dev->init_data, 0, sizeof(dev->init_data));
	strlcpy(info.type, "ir_video", I2C_NAME_SIZE);

	/* detect & configure */
	switch (dev->model) {
	case EM2800_BOARD_TERRATEC_CINERGY_200:
	case EM2820_BOARD_TERRATEC_CINERGY_250:
		dev->init_data.ir_codes = RC_MAP_EM_TERRATEC;
		dev->init_data.get_key = em28xx_get_key_terratec;
		dev->init_data.name = "i2c IR (EM28XX Terratec)";
		break;
	case EM2820_BOARD_PINNACLE_USB_2:
		dev->init_data.ir_codes = RC_MAP_PINNACLE_GREY;
		dev->init_data.get_key = em28xx_get_key_pinnacle_usb_grey;
		dev->init_data.name = "i2c IR (EM28XX Pinnacle PCTV)";
		break;
	case EM2820_BOARD_HAUPPAUGE_WINTV_USB_2:
		dev->init_data.ir_codes = RC_MAP_RC5_HAUPPAUGE_NEW;
		dev->init_data.get_key = em28xx_get_key_em_haup;
		dev->init_data.name = "i2c IR (EM2840 Hauppauge)";
		break;
	case EM2820_BOARD_LEADTEK_WINFAST_USBII_DELUXE:
		dev->init_data.ir_codes = RC_MAP_WINFAST_USBII_DELUXE;
		dev->init_data.get_key = em28xx_get_key_winfast_usbii_deluxe;
		dev->init_data.name = "i2c IR (EM2820 Winfast TV USBII Deluxe)";
		break;
	}

	if (dev->init_data.name)
		info.platform_data = &dev->init_data;
	i2c_new_probed_device(&dev->i2c_adap, &info, addr_list);
}