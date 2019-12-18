#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_5__ {int /*<<< orphan*/  xclk; } ;
struct TYPE_6__ {int addr; } ;
struct em28xx {size_t model; int sensor_xres; int sensor_yres; int sensor_xtal; int vinmode; int vinctl; int /*<<< orphan*/  em28xx_sensor; TYPE_1__ board; TYPE_2__ i2c_client; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 void* EM2750_BOARD_UNKNOWN ; 
 size_t EM2820_BOARD_SILVERCREST_WEBCAM ; 
 int /*<<< orphan*/  EM28XX_MT9M001 ; 
 int /*<<< orphan*/  EM28XX_MT9M111 ; 
 int /*<<< orphan*/  EM28XX_MT9V011 ; 
 int /*<<< orphan*/  EM28XX_XCLK_FREQUENCY_48MHZ ; 
 int /*<<< orphan*/  EM28XX_XCLK_FREQUENCY_4_3MHZ ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_4__* em28xx_boards ; 
 int /*<<< orphan*/  em28xx_errdev (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em28xx_initialize_mt9m001 (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_initialize_mt9m111 (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_pre_card_setup (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_set_model (struct em28xx*) ; 
 int i2c_master_recv (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  i2c_master_send (TYPE_2__*,unsigned char*,int) ; 
 int /*<<< orphan*/  printk (char*,int) ; 

__attribute__((used)) static int em28xx_hint_sensor(struct em28xx *dev)
{
	int rc;
	char *sensor_name;
	unsigned char cmd;
	__be16 version_be;
	u16 version;

	/* Micron sensor detection */
	dev->i2c_client.addr = 0xba >> 1;
	cmd = 0;
	i2c_master_send(&dev->i2c_client, &cmd, 1);
	rc = i2c_master_recv(&dev->i2c_client, (char *)&version_be, 2);
	if (rc != 2)
		return -EINVAL;

	version = be16_to_cpu(version_be);
	switch (version) {
	case 0x8232:		/* mt9v011 640x480 1.3 Mpix sensor */
	case 0x8243:		/* mt9v011 rev B 640x480 1.3 Mpix sensor */
		dev->model = EM2820_BOARD_SILVERCREST_WEBCAM;
		em28xx_set_model(dev);

		sensor_name = "mt9v011";
		dev->em28xx_sensor = EM28XX_MT9V011;
		dev->sensor_xres = 640;
		dev->sensor_yres = 480;
		/*
		 * FIXME: mt9v011 uses I2S speed as xtal clk - at least with
		 * the Silvercrest cam I have here for testing - for higher
		 * resolutions, a high clock cause horizontal artifacts, so we
		 * need to use a lower xclk frequency.
		 * Yet, it would be possible to adjust xclk depending on the
		 * desired resolution, since this affects directly the
		 * frame rate.
		 */
		dev->board.xclk = EM28XX_XCLK_FREQUENCY_4_3MHZ;
		dev->sensor_xtal = 4300000;

		/* probably means GRGB 16 bit bayer */
		dev->vinmode = 0x0d;
		dev->vinctl = 0x00;

		break;

	case 0x143a:    /* MT9M111 as found in the ECS G200 */
		dev->model = EM2750_BOARD_UNKNOWN;
		em28xx_set_model(dev);

		sensor_name = "mt9m111";
		dev->board.xclk = EM28XX_XCLK_FREQUENCY_48MHZ;
		dev->em28xx_sensor = EM28XX_MT9M111;
		em28xx_initialize_mt9m111(dev);
		dev->sensor_xres = 640;
		dev->sensor_yres = 512;

		dev->vinmode = 0x0a;
		dev->vinctl = 0x00;

		break;

	case 0x8431:
		dev->model = EM2750_BOARD_UNKNOWN;
		em28xx_set_model(dev);

		sensor_name = "mt9m001";
		dev->em28xx_sensor = EM28XX_MT9M001;
		em28xx_initialize_mt9m001(dev);
		dev->sensor_xres = 1280;
		dev->sensor_yres = 1024;

		/* probably means BGGR 16 bit bayer */
		dev->vinmode = 0x0c;
		dev->vinctl = 0x00;

		break;
	default:
		printk("Unknown Micron Sensor 0x%04x\n", version);
		return -EINVAL;
	}

	/* Setup webcam defaults */
	em28xx_pre_card_setup(dev);

	em28xx_errdev("Sensor is %s, using model %s entry.\n",
		      sensor_name, em28xx_boards[dev->model].name);

	return 0;
}