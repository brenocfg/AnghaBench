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
struct usb_ov511 {int maxwidth; int maxheight; int minwidth; int minheight; int has_decoder; int num_inputs; int brightness; int contrast; int colour; int hue; scalar_t__ bclass; TYPE_1__* dev; int /*<<< orphan*/  sensor; scalar_t__ stop_during_set; int /*<<< orphan*/  norm; scalar_t__ pal; } ;
struct ov511_regvals {int member_1; int member_2; int /*<<< orphan*/  const member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BCL_OV511 ; 
#define  OV511_DONE_BUS 129 
#define  OV511_I2C_BUS 128 
 int /*<<< orphan*/  PDEBUG (int,char*) ; 
 int /*<<< orphan*/  SEN_SAA7111A ; 
 int /*<<< orphan*/  VIDEO_MODE_AUTO ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  err (char*) ; 
 int i2c_r (struct usb_ov511*,int) ; 
 scalar_t__ ov51x_init_saa_sensor (struct usb_ov511*) ; 
 int /*<<< orphan*/  reg_w (struct usb_ov511*,int,int) ; 
 scalar_t__ write_regvals (struct usb_ov511*,struct ov511_regvals*) ; 

__attribute__((used)) static int
saa7111a_configure(struct usb_ov511 *ov)
{
	int rc;

	/* Since there is no register reset command, all registers must be
	 * written, otherwise gives erratic results */
	static struct ov511_regvals aRegvalsNormSAA7111A[] = {
		{ OV511_I2C_BUS, 0x06, 0xce },
		{ OV511_I2C_BUS, 0x07, 0x00 },
		{ OV511_I2C_BUS, 0x10, 0x44 }, /* YUV422, 240/286 lines */
		{ OV511_I2C_BUS, 0x0e, 0x01 }, /* NTSC M or PAL BGHI */
		{ OV511_I2C_BUS, 0x00, 0x00 },
		{ OV511_I2C_BUS, 0x01, 0x00 },
		{ OV511_I2C_BUS, 0x03, 0x23 },
		{ OV511_I2C_BUS, 0x04, 0x00 },
		{ OV511_I2C_BUS, 0x05, 0x00 },
		{ OV511_I2C_BUS, 0x08, 0xc8 }, /* Auto field freq */
		{ OV511_I2C_BUS, 0x09, 0x01 }, /* Chrom. trap off, APER=0.25 */
		{ OV511_I2C_BUS, 0x0a, 0x80 }, /* BRIG=128 */
		{ OV511_I2C_BUS, 0x0b, 0x40 }, /* CONT=1.0 */
		{ OV511_I2C_BUS, 0x0c, 0x40 }, /* SATN=1.0 */
		{ OV511_I2C_BUS, 0x0d, 0x00 }, /* HUE=0 */
		{ OV511_I2C_BUS, 0x0f, 0x00 },
		{ OV511_I2C_BUS, 0x11, 0x0c },
		{ OV511_I2C_BUS, 0x12, 0x00 },
		{ OV511_I2C_BUS, 0x13, 0x00 },
		{ OV511_I2C_BUS, 0x14, 0x00 },
		{ OV511_I2C_BUS, 0x15, 0x00 },
		{ OV511_I2C_BUS, 0x16, 0x00 },
		{ OV511_I2C_BUS, 0x17, 0x00 },
		{ OV511_I2C_BUS, 0x02, 0xc0 },	/* Composite input 0 */
		{ OV511_DONE_BUS, 0x0, 0x00 },
	};

// FIXME: I don't know how to sync or reset it yet
#if 0
	if (ov51x_init_saa_sensor(ov) < 0) {
		err("Failed to initialize the SAA7111A");
		return -1;
	} else {
		PDEBUG(1, "SAA7111A sensor detected");
	}
#endif

	/* 640x480 not supported with PAL */
	if (ov->pal) {
		ov->maxwidth = 320;
		ov->maxheight = 240;		/* Even field only */
	} else {
		ov->maxwidth = 640;
		ov->maxheight = 480;		/* Even/Odd fields */
	}

	ov->minwidth = 320;
	ov->minheight = 240;		/* Even field only */

	ov->has_decoder = 1;
	ov->num_inputs = 8;
	ov->norm = VIDEO_MODE_AUTO;
	ov->stop_during_set = 0;	/* Decoder guarantees stable image */

	/* Decoder doesn't change these values, so we use these instead of
	 * acutally reading the registers (which doesn't work) */
	ov->brightness = 0x80 << 8;
	ov->contrast = 0x40 << 9;
	ov->colour = 0x40 << 9;
	ov->hue = 32768;

	PDEBUG(4, "Writing SAA7111A registers");
	if (write_regvals(ov, aRegvalsNormSAA7111A))
		return -1;

	/* Detect version of decoder. This must be done after writing the
	 * initial regs or the decoder will lock up. */
	rc = i2c_r(ov, 0x00);

	if (rc < 0) {
		err("Error detecting sensor version");
		return -1;
	} else {
		dev_info(&ov->dev->dev,
			 "Sensor is an SAA7111A (version 0x%x)\n", rc);
		ov->sensor = SEN_SAA7111A;
	}

	// FIXME: Fix this for OV518(+)
	/* Latch to negative edge of clock. Otherwise, we get incorrect
	 * colors and jitter in the digital signal. */
	if (ov->bclass == BCL_OV511)
		reg_w(ov, 0x11, 0x00);
	else
		dev_warn(&ov->dev->dev,
			 "SAA7111A not yet supported with OV518/OV518+\n");

	return 0;
}