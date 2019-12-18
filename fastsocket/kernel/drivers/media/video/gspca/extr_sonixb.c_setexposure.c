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
struct sd {int sensor; int exposure; int reg11; int /*<<< orphan*/  autogain; } ;
struct gspca_dev {int width; } ;
typedef  int __u8 ;
typedef  int __u16 ;
struct TYPE_2__ {int sensor_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_ERR ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
#define  SENSOR_HV7131D 134 
#define  SENSOR_OV6650 133 
#define  SENSOR_OV7630 132 
#define  SENSOR_PAS106 131 
#define  SENSOR_PAS202 130 
#define  SENSOR_TAS5110C 129 
#define  SENSOR_TAS5110D 128 
 int /*<<< orphan*/  i2c_w (struct gspca_dev*,int const*) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int*,int) ; 
 TYPE_1__* sensor_data ; 

__attribute__((used)) static void setexposure(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	switch (sd->sensor) {
	case SENSOR_HV7131D: {
		/* Note the datasheet wrongly says line mode exposure uses reg
		   0x26 and 0x27, testing has shown 0x25 + 0x26 */
		__u8 i2c[] = {0xc0, 0x11, 0x25, 0x00, 0x00, 0x00, 0x00, 0x17};
		/* The HV7131D's exposure goes from 0 - 65535, we scale our
		   exposure of 0-1023 to 0-6138. There are 2 reasons for this:
		   1) This puts our exposure knee of 200 at approx the point
		      where the framerate starts dropping
		   2) At 6138 the framerate has already dropped to 2 fps,
		      going any lower makes little sense */
		__u16 reg = sd->exposure * 6;
		i2c[3] = reg >> 8;
		i2c[4] = reg & 0xff;
		if (i2c_w(gspca_dev, i2c) != 0)
			goto err;
		break;
	    }
	case SENSOR_TAS5110C:
	case SENSOR_TAS5110D: {
		/* register 19's high nibble contains the sn9c10x clock divider
		   The high nibble configures the no fps according to the
		   formula: 60 / high_nibble. With a maximum of 30 fps */
		__u8 reg = sd->exposure;
		reg = (reg << 4) | 0x0b;
		reg_w(gspca_dev, 0x19, &reg, 1);
		break;
	    }
	case SENSOR_OV6650:
	case SENSOR_OV7630: {
		/* The ov6650 / ov7630 have 2 registers which both influence
		   exposure, register 11, whose low nibble sets the nr off fps
		   according to: fps = 30 / (low_nibble + 1)

		   The fps configures the maximum exposure setting, but it is
		   possible to use less exposure then what the fps maximum
		   allows by setting register 10. register 10 configures the
		   actual exposure as quotient of the full exposure, with 0
		   being no exposure at all (not very usefull) and reg10_max
		   being max exposure possible at that framerate.

		   The code maps our 0 - 510 ms exposure ctrl to these 2
		   registers, trying to keep fps as high as possible.
		*/
		__u8 i2c[] = {0xb0, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x10};
		int reg10, reg11, reg10_max;

		/* ov6645 datasheet says reg10_max is 9a, but that uses
		   tline * 2 * reg10 as formula for calculating texpo, the
		   ov6650 probably uses the same formula as the 7730 which uses
		   tline * 4 * reg10, which explains why the reg10max we've
		   found experimentally for the ov6650 is exactly half that of
		   the ov6645. The ov7630 datasheet says the max is 0x41. */
		if (sd->sensor == SENSOR_OV6650) {
			reg10_max = 0x4d;
			i2c[4] = 0xc0; /* OV6650 needs non default vsync pol */
		} else
			reg10_max = 0x41;

		reg11 = (15 * sd->exposure + 999) / 1000;
		if (reg11 < 1)
			reg11 = 1;
		else if (reg11 > 16)
			reg11 = 16;

		/* In 640x480, if the reg11 has less than 4, the image is
		   unstable (the bridge goes into a higher compression mode
		   which we have not reverse engineered yet). */
		if (gspca_dev->width == 640 && reg11 < 4)
			reg11 = 4;

		/* frame exposure time in ms = 1000 * reg11 / 30    ->
		reg10 = (sd->exposure / 2) * reg10_max / (1000 * reg11 / 30) */
		reg10 = (sd->exposure * 15 * reg10_max) / (1000 * reg11);

		/* Don't allow this to get below 10 when using autogain, the
		   steps become very large (relatively) when below 10 causing
		   the image to oscilate from much too dark, to much too bright
		   and back again. */
		if (sd->autogain && reg10 < 10)
			reg10 = 10;
		else if (reg10 > reg10_max)
			reg10 = reg10_max;

		/* Write reg 10 and reg11 low nibble */
		i2c[1] = sensor_data[sd->sensor].sensor_addr;
		i2c[3] = reg10;
		i2c[4] |= reg11 - 1;

		/* If register 11 didn't change, don't change it */
		if (sd->reg11 == reg11)
			i2c[0] = 0xa0;

		if (i2c_w(gspca_dev, i2c) == 0)
			sd->reg11 = reg11;
		else
			goto err;
		break;
	    }
	case SENSOR_PAS202: {
		__u8 i2cpframerate[] =
			{0xb0, 0x40, 0x04, 0x00, 0x00, 0x00, 0x00, 0x16};
		__u8 i2cpexpo[] =
			{0xa0, 0x40, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x16};
		const __u8 i2cpdoit[] =
			{0xa0, 0x40, 0x11, 0x01, 0x00, 0x00, 0x00, 0x16};
		int framerate_ctrl;

		/* The exposure knee for the autogain algorithm is 200
		   (100 ms / 10 fps on other sensors), for values below this
		   use the control for setting the partial frame expose time,
		   above that use variable framerate. This way we run at max
		   framerate (640x480@7.5 fps, 320x240@10fps) until the knee
		   is reached. Using the variable framerate control above 200
		   is better then playing around with both clockdiv + partial
		   frame exposure times (like we are doing with the ov chips),
		   as that sometimes leads to jumps in the exposure control,
		   which are bad for auto exposure. */
		if (sd->exposure < 200) {
			i2cpexpo[3] = 255 - (sd->exposure * 255) / 200;
			framerate_ctrl = 500;
		} else {
			/* The PAS202's exposure control goes from 0 - 4095,
			   but anything below 500 causes vsync issues, so scale
			   our 200-1023 to 500-4095 */
			framerate_ctrl = (sd->exposure - 200) * 1000 / 229 +
					 500;
		}

		i2cpframerate[3] = framerate_ctrl >> 6;
		i2cpframerate[4] = framerate_ctrl & 0x3f;
		if (i2c_w(gspca_dev, i2cpframerate) < 0)
			goto err;
		if (i2c_w(gspca_dev, i2cpexpo) < 0)
			goto err;
		if (i2c_w(gspca_dev, i2cpdoit) < 0)
			goto err;
		break;
	    }
	case SENSOR_PAS106: {
		__u8 i2cpframerate[] =
			{0xb1, 0x40, 0x03, 0x00, 0x00, 0x00, 0x00, 0x14};
		__u8 i2cpexpo[] =
			{0xa1, 0x40, 0x05, 0x00, 0x00, 0x00, 0x00, 0x14};
		const __u8 i2cpdoit[] =
			{0xa1, 0x40, 0x13, 0x01, 0x00, 0x00, 0x00, 0x14};
		int framerate_ctrl;

		/* For values below 150 use partial frame exposure, above
		   that use framerate ctrl */
		if (sd->exposure < 150) {
			i2cpexpo[3] = 150 - sd->exposure;
			framerate_ctrl = 300;
		} else {
			/* The PAS106's exposure control goes from 0 - 4095,
			   but anything below 300 causes vsync issues, so scale
			   our 150-1023 to 300-4095 */
			framerate_ctrl = (sd->exposure - 150) * 1000 / 230 +
					 300;
		}

		i2cpframerate[3] = framerate_ctrl >> 4;
		i2cpframerate[4] = framerate_ctrl & 0x0f;
		if (i2c_w(gspca_dev, i2cpframerate) < 0)
			goto err;
		if (i2c_w(gspca_dev, i2cpexpo) < 0)
			goto err;
		if (i2c_w(gspca_dev, i2cpdoit) < 0)
			goto err;
		break;
	    }
	}
	return;
err:
	PDEBUG(D_ERR, "i2c error exposure");
}