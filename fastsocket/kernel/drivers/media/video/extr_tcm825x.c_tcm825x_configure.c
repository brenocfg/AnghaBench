#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct v4l2_pix_format {int pixelformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_int_device {struct tcm825x_sensor* priv; } ;
struct v4l2_fract {int denominator; int numerator; } ;
struct tcm825x_sensor {TYPE_2__* i2c_client; TYPE_1__* platform_data; struct v4l2_fract timeperframe; struct v4l2_pix_format pix; } ;
typedef  enum pixel_format { ____Placeholder_pixel_format } pixel_format ;
typedef  enum image_size { ____Placeholder_image_size } image_size ;
struct TYPE_11__ {int val; int /*<<< orphan*/  reg; } ;
struct TYPE_10__ {int val; int /*<<< orphan*/  reg; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* default_regs ) () ;} ;

/* Variables and functions */
 int HIGH_FPS_MODE_LOWER_LIMIT ; 
 int RGB565 ; 
#define  V4L2_PIX_FMT_RGB565 129 
#define  V4L2_PIX_FMT_UYVY 128 
 int YUV422 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  stub1 () ; 
 int tcm825x_find_size (struct v4l2_int_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__** tcm825x_fmt_reg ; 
 int tcm825x_read_reg (TYPE_2__*,int) ; 
 TYPE_5__** tcm825x_siz_reg ; 
 int tcm825x_write_default_regs (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcm825x_write_reg (TYPE_2__*,int,int) ; 
 int tcm825x_write_reg_mask (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tcm825x_configure(struct v4l2_int_device *s)
{
	struct tcm825x_sensor *sensor = s->priv;
	struct v4l2_pix_format *pix = &sensor->pix;
	enum image_size isize = tcm825x_find_size(s, pix->width, pix->height);
	struct v4l2_fract *fper = &sensor->timeperframe;
	enum pixel_format pfmt;
	int err;
	u32 tgt_fps;
	u8 val;

	/* common register initialization */
	err = tcm825x_write_default_regs(
		sensor->i2c_client, sensor->platform_data->default_regs());
	if (err)
		return err;

	/* configure image size */
	val = tcm825x_siz_reg[isize]->val;
	dev_dbg(&sensor->i2c_client->dev,
		"configuring image size %d\n", isize);
	err = tcm825x_write_reg_mask(sensor->i2c_client,
				     tcm825x_siz_reg[isize]->reg, val);
	if (err)
		return err;

	/* configure pixel format */
	switch (pix->pixelformat) {
	default:
	case V4L2_PIX_FMT_RGB565:
		pfmt = RGB565;
		break;
	case V4L2_PIX_FMT_UYVY:
		pfmt = YUV422;
		break;
	}

	dev_dbg(&sensor->i2c_client->dev,
		"configuring pixel format %d\n", pfmt);
	val = tcm825x_fmt_reg[pfmt]->val;

	err = tcm825x_write_reg_mask(sensor->i2c_client,
				     tcm825x_fmt_reg[pfmt]->reg, val);
	if (err)
		return err;

	/*
	 * For frame rate < 15, the FPS reg (addr 0x02, bit 7) must be
	 * set. Frame rate will be halved from the normal.
	 */
	tgt_fps = fper->denominator / fper->numerator;
	if (tgt_fps <= HIGH_FPS_MODE_LOWER_LIMIT) {
		val = tcm825x_read_reg(sensor->i2c_client, 0x02);
		val |= 0x80;
		tcm825x_write_reg(sensor->i2c_client, 0x02, val);
	}

	return 0;
}