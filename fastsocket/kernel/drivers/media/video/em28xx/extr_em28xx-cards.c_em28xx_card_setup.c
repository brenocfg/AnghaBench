#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct tveeprom {int /*<<< orphan*/  audio_processor; scalar_t__ tuner_type; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct TYPE_6__ {int has_msp34xx; scalar_t__ valid; scalar_t__ decoder; scalar_t__ adecoder; scalar_t__ tvaudio_addr; scalar_t__ tuner_type; scalar_t__ radio_addr; TYPE_1__ radio; scalar_t__ has_snapshot_button; scalar_t__ has_ir_i2c; int /*<<< orphan*/  tuner_gpio; int /*<<< orphan*/  name; scalar_t__ is_webcam; } ;
struct TYPE_7__ {int addr; } ;
struct em28xx {int progressive; int model; scalar_t__ tuner_addr; int tda9887_conf; int i2s_speed; scalar_t__ em28xx_sensor; int /*<<< orphan*/  i2c_adap; int /*<<< orphan*/  v4l2_dev; TYPE_2__ board; int /*<<< orphan*/  sensor_xtal; scalar_t__ tuner_type; int /*<<< orphan*/  eedata; TYPE_3__ i2c_client; } ;
typedef  enum v4l2_i2c_tuner_type { ____Placeholder_v4l2_i2c_tuner_type } v4l2_i2c_tuner_type ;
struct TYPE_8__ {scalar_t__ tuner_addr; int tda9887_conf; scalar_t__ tuner_type; } ;

/* Variables and functions */
 int ADDRS_DEMOD ; 
 int ADDRS_TV ; 
 int ADDRS_TV_WITH_DEMOD ; 
#define  EM2800_BOARD_UNKNOWN 138 
#define  EM2820_BOARD_HAUPPAUGE_WINTV_USB_2 137 
#define  EM2820_BOARD_KWORLD_PVRTV2800RF 136 
#define  EM2820_BOARD_UNKNOWN 135 
#define  EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900 134 
#define  EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900_R2 133 
#define  EM2880_BOARD_MSI_DIGIVOX_AD 132 
#define  EM2882_BOARD_KWORLD_ATSC_315U 131 
#define  EM2882_BOARD_KWORLD_VS_DVBT 130 
#define  EM2883_BOARD_HAUPPAUGE_WINTV_HVR_850 129 
#define  EM2883_BOARD_HAUPPAUGE_WINTV_HVR_950 128 
 int /*<<< orphan*/  EM28XX_ANALOG_MODE ; 
 scalar_t__ EM28XX_BOARD_NOT_VALIDATED ; 
 scalar_t__ EM28XX_MT9V011 ; 
 int EM28XX_R08_GPIO ; 
 scalar_t__ EM28XX_SAA711X ; 
 scalar_t__ EM28XX_TVAUDIO ; 
 scalar_t__ EM28XX_TVP5150 ; 
 int TDA9887_PRESENT ; 
 scalar_t__ TUNER_ABSENT ; 
 int /*<<< orphan*/  V4L2_IDENT_MSPX4XX ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  disable_ir ; 
 TYPE_4__* em28xx_boards ; 
 int /*<<< orphan*/  em28xx_errdev (char*) ; 
 int /*<<< orphan*/  em28xx_gpio_set (struct em28xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em28xx_hint_board (struct em28xx*) ; 
 scalar_t__ em28xx_hint_sensor (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_info (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  em28xx_ir_init (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_pre_card_setup (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_register_snapshot_button (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_set_mode (struct em28xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em28xx_set_model (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_tuner_setup (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_write_reg (struct em28xx*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/ * msp3400_addrs ; 
 int /*<<< orphan*/ * mt9v011_addrs ; 
 int /*<<< orphan*/  request_module (char*) ; 
 int /*<<< orphan*/  s_config ; 
 int /*<<< orphan*/ * saa711x_addrs ; 
 scalar_t__ tuner ; 
 int /*<<< orphan*/  tveeprom_hauppauge_analog (TYPE_3__*,struct tveeprom*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tvp5150_addrs ; 
 struct v4l2_subdev* v4l2_i2c_new_subdev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_i2c_subdev_addr (struct v4l2_subdev*) ; 
 int /*<<< orphan*/ * v4l2_i2c_tuner_addrs (int) ; 
 int /*<<< orphan*/  v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void em28xx_card_setup(struct em28xx *dev)
{
	/*
	 * If the device can be a webcam, seek for a sensor.
	 * If sensor is not found, then it isn't a webcam.
	 */
	if (dev->board.is_webcam) {
		if (em28xx_hint_sensor(dev) < 0)
			dev->board.is_webcam = 0;
		else
			dev->progressive = 1;
	}

	if (!dev->board.is_webcam) {
		switch (dev->model) {
		case EM2820_BOARD_UNKNOWN:
		case EM2800_BOARD_UNKNOWN:
		/*
		 * The K-WORLD DVB-T 310U is detected as an MSI Digivox AD.
		 *
		 * This occurs because they share identical USB vendor and
		 * product IDs.
		 *
		 * What we do here is look up the EEPROM hash of the K-WORLD
		 * and if it is found then we decide that we do not have
		 * a DIGIVOX and reset the device to the K-WORLD instead.
		 *
		 * This solution is only valid if they do not share eeprom
		 * hash identities which has not been determined as yet.
		 */
		if (em28xx_hint_board(dev) < 0)
			em28xx_errdev("Board not discovered\n");
		else {
			em28xx_set_model(dev);
			em28xx_pre_card_setup(dev);
		}
		break;
		default:
			em28xx_set_model(dev);
		}
	}

	em28xx_info("Identified as %s (card=%d)\n",
		    dev->board.name, dev->model);

	dev->tuner_type = em28xx_boards[dev->model].tuner_type;
	if (em28xx_boards[dev->model].tuner_addr)
		dev->tuner_addr = em28xx_boards[dev->model].tuner_addr;

	if (em28xx_boards[dev->model].tda9887_conf)
		dev->tda9887_conf = em28xx_boards[dev->model].tda9887_conf;

	/* request some modules */
	switch (dev->model) {
	case EM2820_BOARD_HAUPPAUGE_WINTV_USB_2:
	case EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900:
	case EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900_R2:
	case EM2883_BOARD_HAUPPAUGE_WINTV_HVR_850:
	case EM2883_BOARD_HAUPPAUGE_WINTV_HVR_950:
	{
		struct tveeprom tv;
#if defined(CONFIG_MODULES) && defined(MODULE)
		request_module("tveeprom");
#endif
		/* Call first TVeeprom */

		dev->i2c_client.addr = 0xa0 >> 1;
		tveeprom_hauppauge_analog(&dev->i2c_client, &tv, dev->eedata);

		dev->tuner_type = tv.tuner_type;

		if (tv.audio_processor == V4L2_IDENT_MSPX4XX) {
			dev->i2s_speed = 2048000;
			dev->board.has_msp34xx = 1;
		}
		break;
	}
	case EM2882_BOARD_KWORLD_ATSC_315U:
		em28xx_write_reg(dev, 0x0d, 0x42);
		msleep(10);
		em28xx_write_reg(dev, EM28XX_R08_GPIO, 0xfd);
		msleep(10);
		break;
	case EM2820_BOARD_KWORLD_PVRTV2800RF:
		/* GPIO enables sound on KWORLD PVR TV 2800RF */
		em28xx_write_reg(dev, EM28XX_R08_GPIO, 0xf9);
		break;
	case EM2820_BOARD_UNKNOWN:
	case EM2800_BOARD_UNKNOWN:
		/*
		 * The K-WORLD DVB-T 310U is detected as an MSI Digivox AD.
		 *
		 * This occurs because they share identical USB vendor and
		 * product IDs.
		 *
		 * What we do here is look up the EEPROM hash of the K-WORLD
		 * and if it is found then we decide that we do not have
		 * a DIGIVOX and reset the device to the K-WORLD instead.
		 *
		 * This solution is only valid if they do not share eeprom
		 * hash identities which has not been determined as yet.
		 */
	case EM2880_BOARD_MSI_DIGIVOX_AD:
		if (!em28xx_hint_board(dev))
			em28xx_set_model(dev);

		/* In cases where we had to use a board hint, the call to
		   em28xx_set_mode() in em28xx_pre_card_setup() was a no-op,
		   so make the call now so the analog GPIOs are set properly
		   before probing the i2c bus. */
		em28xx_gpio_set(dev, dev->board.tuner_gpio);
		em28xx_set_mode(dev, EM28XX_ANALOG_MODE);
		break;

/*
		 * The Dikom DK300 is detected as an Kworld VS-DVB-T 323UR.
		 *
		 * This occurs because they share identical USB vendor and
		 * product IDs.
		 *
		 * What we do here is look up the EEPROM hash of the Dikom
		 * and if it is found then we decide that we do not have
		 * a Kworld and reset the device to the Dikom instead.
		 *
		 * This solution is only valid if they do not share eeprom
		 * hash identities which has not been determined as yet.
		 */
	case EM2882_BOARD_KWORLD_VS_DVBT:
		if (!em28xx_hint_board(dev))
			em28xx_set_model(dev);

		/* In cases where we had to use a board hint, the call to
		   em28xx_set_mode() in em28xx_pre_card_setup() was a no-op,
		   so make the call now so the analog GPIOs are set properly
		   before probing the i2c bus. */
		em28xx_gpio_set(dev, dev->board.tuner_gpio);
		em28xx_set_mode(dev, EM28XX_ANALOG_MODE);
		break;
	}

#if defined(CONFIG_MODULES) && defined(MODULE)
	if (dev->board.has_ir_i2c && !disable_ir)
		request_module("ir-kbd-i2c");
#endif
	if (dev->board.has_snapshot_button)
		em28xx_register_snapshot_button(dev);

	if (dev->board.valid == EM28XX_BOARD_NOT_VALIDATED) {
		em28xx_errdev("\n\n");
		em28xx_errdev("The support for this board weren't "
			      "valid yet.\n");
		em28xx_errdev("Please send a report of having this working\n");
		em28xx_errdev("not to V4L mailing list (and/or to other "
				"addresses)\n\n");
	}

	/* Allow override tuner type by a module parameter */
	if (tuner >= 0)
		dev->tuner_type = tuner;

	/* request some modules */
	if (dev->board.has_msp34xx)
		v4l2_i2c_new_subdev(&dev->v4l2_dev, &dev->i2c_adap,
			"msp3400", 0, msp3400_addrs);

	if (dev->board.decoder == EM28XX_SAA711X)
		v4l2_i2c_new_subdev(&dev->v4l2_dev, &dev->i2c_adap,
			"saa7115_auto", 0, saa711x_addrs);

	if (dev->board.decoder == EM28XX_TVP5150)
		v4l2_i2c_new_subdev(&dev->v4l2_dev, &dev->i2c_adap,
			"tvp5150", 0, tvp5150_addrs);

	if (dev->em28xx_sensor == EM28XX_MT9V011) {
		struct v4l2_subdev *sd;

		sd = v4l2_i2c_new_subdev(&dev->v4l2_dev,
			 &dev->i2c_adap, "mt9v011", 0, mt9v011_addrs);
		v4l2_subdev_call(sd, core, s_config, 0, &dev->sensor_xtal);
	}


	if (dev->board.adecoder == EM28XX_TVAUDIO)
		v4l2_i2c_new_subdev(&dev->v4l2_dev, &dev->i2c_adap,
			"tvaudio", dev->board.tvaudio_addr, NULL);

	if (dev->board.tuner_type != TUNER_ABSENT) {
		int has_demod = (dev->tda9887_conf & TDA9887_PRESENT);

		if (dev->board.radio.type)
			v4l2_i2c_new_subdev(&dev->v4l2_dev, &dev->i2c_adap,
				"tuner", dev->board.radio_addr, NULL);

		if (has_demod)
			v4l2_i2c_new_subdev(&dev->v4l2_dev,
				&dev->i2c_adap, "tuner",
				0, v4l2_i2c_tuner_addrs(ADDRS_DEMOD));
		if (dev->tuner_addr == 0) {
			enum v4l2_i2c_tuner_type type =
				has_demod ? ADDRS_TV_WITH_DEMOD : ADDRS_TV;
			struct v4l2_subdev *sd;

			sd = v4l2_i2c_new_subdev(&dev->v4l2_dev,
				&dev->i2c_adap, "tuner",
				0, v4l2_i2c_tuner_addrs(type));

			if (sd)
				dev->tuner_addr = v4l2_i2c_subdev_addr(sd);
		} else {
			v4l2_i2c_new_subdev(&dev->v4l2_dev, &dev->i2c_adap,
				"tuner", dev->tuner_addr, NULL);
		}
	}

	em28xx_tuner_setup(dev);

	if(!disable_ir)
		em28xx_ir_init(dev);
}