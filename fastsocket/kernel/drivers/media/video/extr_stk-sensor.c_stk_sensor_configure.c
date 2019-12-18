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
struct TYPE_2__ {int mode; int palette; scalar_t__ vflip; scalar_t__ hflip; } ;
struct stk_camera {TYPE_1__ vsettings; } ;
struct regval {int dummy; } ;

/* Variables and functions */
 int COM7_FMT_CIF ; 
 int COM7_FMT_QCIF ; 
 int COM7_FMT_QVGA ; 
 int COM7_FMT_SXGA ; 
 int COM7_FMT_VGA ; 
 int COM7_PBAYER ; 
 int COM7_RGB ; 
 int COM7_YUV ; 
 int EFAULT ; 
#define  MODE_CIF 137 
#define  MODE_QCIF 136 
#define  MODE_QVGA 135 
#define  MODE_SXGA 134 
#define  MODE_VGA 133 
 int MVFP_FLIP ; 
 int MVFP_MIRROR ; 
 int /*<<< orphan*/  REG_ADVFH ; 
 int /*<<< orphan*/  REG_ADVFL ; 
 int /*<<< orphan*/  REG_COM7 ; 
 int /*<<< orphan*/  REG_MVFP ; 
 int /*<<< orphan*/  REG_TSLB ; 
 int /*<<< orphan*/  STK_ERROR (char*,...) ; 
#define  V4L2_PIX_FMT_RGB565 132 
#define  V4L2_PIX_FMT_RGB565X 131 
#define  V4L2_PIX_FMT_SBGGR8 130 
#define  V4L2_PIX_FMT_UYVY 129 
#define  V4L2_PIX_FMT_YUYV 128 
 int /*<<< orphan*/  msleep (int) ; 
 struct regval* ov_fmt_bayer ; 
 struct regval* ov_fmt_rgbp ; 
 struct regval* ov_fmt_rgbr ; 
 struct regval* ov_fmt_uyvy ; 
 struct regval* ov_fmt_yuyv ; 
 int /*<<< orphan*/  stk_sensor_outb (struct stk_camera*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stk_sensor_set_hw (struct stk_camera*,int,int,int,int) ; 
 int /*<<< orphan*/  stk_sensor_write_regvals (struct stk_camera*,struct regval*) ; 

int stk_sensor_configure(struct stk_camera *dev)
{
	int com7;
	/*
	 * We setup the sensor to output dummy lines in low-res modes,
	 * so we don't get absurdly hight framerates.
	 */
	unsigned dummylines;
	int flip;
	struct regval *rv;

	switch (dev->vsettings.mode) {
	case MODE_QCIF: com7 = COM7_FMT_QCIF;
		dummylines = 604;
		break;
	case MODE_QVGA: com7 = COM7_FMT_QVGA;
		dummylines = 267;
		break;
	case MODE_CIF: com7 = COM7_FMT_CIF;
		dummylines = 412;
		break;
	case MODE_VGA: com7 = COM7_FMT_VGA;
		dummylines = 11;
		break;
	case MODE_SXGA: com7 = COM7_FMT_SXGA;
		dummylines = 0;
		break;
	default: STK_ERROR("Unsupported mode %d\n", dev->vsettings.mode);
		return -EFAULT;
	}
	switch (dev->vsettings.palette) {
	case V4L2_PIX_FMT_UYVY:
		com7 |= COM7_YUV;
		rv = ov_fmt_uyvy;
		break;
	case V4L2_PIX_FMT_YUYV:
		com7 |= COM7_YUV;
		rv = ov_fmt_yuyv;
		break;
	case V4L2_PIX_FMT_RGB565:
		com7 |= COM7_RGB;
		rv = ov_fmt_rgbp;
		break;
	case V4L2_PIX_FMT_RGB565X:
		com7 |= COM7_RGB;
		rv = ov_fmt_rgbr;
		break;
	case V4L2_PIX_FMT_SBGGR8:
		com7 |= COM7_PBAYER;
		rv = ov_fmt_bayer;
		break;
	default: STK_ERROR("Unsupported colorspace\n");
		return -EFAULT;
	}
	/*FIXME sometimes the sensor go to a bad state
	stk_sensor_write_regvals(dev, ov_initvals); */
	stk_sensor_outb(dev, REG_COM7, com7);
	msleep(50);
	stk_sensor_write_regvals(dev, rv);
	flip = (dev->vsettings.vflip?MVFP_FLIP:0)
		| (dev->vsettings.hflip?MVFP_MIRROR:0);
	stk_sensor_outb(dev, REG_MVFP, flip);
	if (dev->vsettings.palette == V4L2_PIX_FMT_SBGGR8
			&& !dev->vsettings.vflip)
		stk_sensor_outb(dev, REG_TSLB, 0x08);
	stk_sensor_outb(dev, REG_ADVFH, dummylines >> 8);
	stk_sensor_outb(dev, REG_ADVFL, dummylines & 0xff);
	msleep(50);
	switch (dev->vsettings.mode) {
	case MODE_VGA:
		if (stk_sensor_set_hw(dev, 302, 1582, 6, 486))
			STK_ERROR("stk_sensor_set_hw failed (VGA)\n");
		break;
	case MODE_SXGA:
	case MODE_CIF:
	case MODE_QVGA:
	case MODE_QCIF:
		/*FIXME These settings seem ignored by the sensor
		if (stk_sensor_set_hw(dev, 220, 1500, 10, 1034))
			STK_ERROR("stk_sensor_set_hw failed (SXGA)\n");
		*/
		break;
	}
	msleep(10);
	return 0;
}