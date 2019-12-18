#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sd {size_t sensor; scalar_t__ bridge; int reg11; int /*<<< orphan*/  avg_lum; scalar_t__ exp_too_low_cnt; scalar_t__ exp_too_high_cnt; scalar_t__ autogain_ignore_frames; scalar_t__ frames_to_drop; } ;
struct cam {TYPE_1__* cam_mode; } ;
struct gspca_dev {size_t curr_mode; struct cam cam; } ;
typedef  int __u8 ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  sensor_init_size; int /*<<< orphan*/  sensor_init; int /*<<< orphan*/  bridge_init; } ;
struct TYPE_3__ {int priv; } ;

/* Variables and functions */
 scalar_t__ BRIDGE_103 ; 
 int F_SIF ; 
 int MODE_RAW ; 
 int MODE_REDUCED_SIF ; 
#define  SENSOR_OV7630 130 
#define  SENSOR_PAS202 129 
#define  SENSOR_TAS5130CXX 128 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_w (struct gspca_dev*,int const*) ; 
 int /*<<< orphan*/  i2c_w_vector (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int*,int) ; 
 TYPE_2__* sensor_data ; 
 int /*<<< orphan*/  setbrightness (struct gspca_dev*) ; 
 int /*<<< orphan*/  setexposure (struct gspca_dev*) ; 
 int /*<<< orphan*/  setfreq (struct gspca_dev*) ; 
 int /*<<< orphan*/  setgain (struct gspca_dev*) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam = &gspca_dev->cam;
	int i, mode;
	__u8 regs[0x31];

	mode = cam->cam_mode[gspca_dev->curr_mode].priv & 0x07;
	/* Copy registers 0x01 - 0x19 from the template */
	memcpy(&regs[0x01], sensor_data[sd->sensor].bridge_init, 0x19);
	/* Set the mode */
	regs[0x18] |= mode << 4;

	/* Set bridge gain to 1.0 */
	if (sd->bridge == BRIDGE_103) {
		regs[0x05] = 0x20; /* Red */
		regs[0x06] = 0x20; /* Green */
		regs[0x07] = 0x20; /* Blue */
	} else {
		regs[0x10] = 0x00; /* Red and blue */
		regs[0x11] = 0x00; /* Green */
	}

	/* Setup pixel numbers and auto exposure window */
	if (sensor_data[sd->sensor].flags & F_SIF) {
		regs[0x1a] = 0x14; /* HO_SIZE 640, makes no sense */
		regs[0x1b] = 0x0a; /* VO_SIZE 320, makes no sense */
		regs[0x1c] = 0x02; /* AE H-start 64 */
		regs[0x1d] = 0x02; /* AE V-start 64 */
		regs[0x1e] = 0x09; /* AE H-end 288 */
		regs[0x1f] = 0x07; /* AE V-end 224 */
	} else {
		regs[0x1a] = 0x1d; /* HO_SIZE 960, makes no sense */
		regs[0x1b] = 0x10; /* VO_SIZE 512, makes no sense */
		regs[0x1c] = 0x05; /* AE H-start 160 */
		regs[0x1d] = 0x03; /* AE V-start 96 */
		regs[0x1e] = 0x0f; /* AE H-end 480 */
		regs[0x1f] = 0x0c; /* AE V-end 384 */
	}

	/* Setup the gamma table (only used with the sn9c103 bridge) */
	for (i = 0; i < 16; i++)
		regs[0x20 + i] = i * 16;
	regs[0x20 + i] = 255;

	/* Special cases where some regs depend on mode or bridge */
	switch (sd->sensor) {
	case SENSOR_TAS5130CXX:
		/* FIXME / TESTME
		   probably not mode specific at all most likely the upper
		   nibble of 0x19 is exposure (clock divider) just as with
		   the tas5110, we need someone to test this. */
		regs[0x19] = mode ? 0x23 : 0x43;
		break;
	case SENSOR_OV7630:
		/* FIXME / TESTME for some reason with the 101/102 bridge the
		   clock is set to 12 Mhz (reg1 == 0x04), rather then 24.
		   Also the hstart needs to go from 1 to 2 when using a 103,
		   which is likely related. This does not seem right. */
		if (sd->bridge == BRIDGE_103) {
			regs[0x01] = 0x44; /* Select 24 Mhz clock */
			regs[0x12] = 0x02; /* Set hstart to 2 */
		}
	}
	/* Disable compression when the raw bayer format has been selected */
	if (cam->cam_mode[gspca_dev->curr_mode].priv & MODE_RAW)
		regs[0x18] &= ~0x80;

	/* Vga mode emulation on SIF sensor? */
	if (cam->cam_mode[gspca_dev->curr_mode].priv & MODE_REDUCED_SIF) {
		regs[0x12] += 16;	/* hstart adjust */
		regs[0x13] += 24;	/* vstart adjust */
		regs[0x15]  = 320 / 16; /* hsize */
		regs[0x16]  = 240 / 16; /* vsize */
	}

	/* reg 0x01 bit 2 video transfert on */
	reg_w(gspca_dev, 0x01, &regs[0x01], 1);
	/* reg 0x17 SensorClk enable inv Clk 0x60 */
	reg_w(gspca_dev, 0x17, &regs[0x17], 1);
	/* Set the registers from the template */
	reg_w(gspca_dev, 0x01, &regs[0x01],
	      (sd->bridge == BRIDGE_103) ? 0x30 : 0x1f);

	/* Init the sensor */
	i2c_w_vector(gspca_dev, sensor_data[sd->sensor].sensor_init,
			sensor_data[sd->sensor].sensor_init_size);

	/* Mode / bridge specific sensor setup */
	switch (sd->sensor) {
	case SENSOR_PAS202: {
		const __u8 i2cpclockdiv[] =
			{0xa0, 0x40, 0x02, 0x03, 0x00, 0x00, 0x00, 0x10};
		/* clockdiv from 4 to 3 (7.5 -> 10 fps) when in low res mode */
		if (mode)
			i2c_w(gspca_dev, i2cpclockdiv);
		break;
	    }
	case SENSOR_OV7630:
		/* FIXME / TESTME We should be able to handle this identical
		   for the 101/102 and the 103 case */
		if (sd->bridge == BRIDGE_103) {
			const __u8 i2c[] = { 0xa0, 0x21, 0x13,
					     0x80, 0x00, 0x00, 0x00, 0x10 };
			i2c_w(gspca_dev, i2c);
		}
		break;
	}
	/* H_size V_size 0x28, 0x1e -> 640x480. 0x16, 0x12 -> 352x288 */
	reg_w(gspca_dev, 0x15, &regs[0x15], 2);
	/* compression register */
	reg_w(gspca_dev, 0x18, &regs[0x18], 1);
	/* H_start */
	reg_w(gspca_dev, 0x12, &regs[0x12], 1);
	/* V_START */
	reg_w(gspca_dev, 0x13, &regs[0x13], 1);
	/* reset 0x17 SensorClk enable inv Clk 0x60 */
				/*fixme: ov7630 [17]=68 8f (+20 if 102)*/
	reg_w(gspca_dev, 0x17, &regs[0x17], 1);
	/*MCKSIZE ->3 */	/*fixme: not ov7630*/
	reg_w(gspca_dev, 0x19, &regs[0x19], 1);
	/* AE_STRX AE_STRY AE_ENDX AE_ENDY */
	reg_w(gspca_dev, 0x1c, &regs[0x1c], 4);
	/* Enable video transfert */
	reg_w(gspca_dev, 0x01, &regs[0x01], 1);
	/* Compression */
	reg_w(gspca_dev, 0x18, &regs[0x18], 2);
	msleep(20);

	sd->reg11 = -1;

	setgain(gspca_dev);
	setbrightness(gspca_dev);
	setexposure(gspca_dev);
	setfreq(gspca_dev);

	sd->frames_to_drop = 0;
	sd->autogain_ignore_frames = 0;
	sd->exp_too_high_cnt = 0;
	sd->exp_too_low_cnt = 0;
	atomic_set(&sd->avg_lum, -1);
	return 0;
}