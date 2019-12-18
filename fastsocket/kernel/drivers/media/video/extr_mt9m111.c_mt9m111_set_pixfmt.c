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
struct mt9m111 {int swap_yuv_y_chromas; int swap_yuv_cb_cr; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  enum v4l2_mbus_pixelcode { ____Placeholder_v4l2_mbus_pixelcode } v4l2_mbus_pixelcode ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_MBUS_FMT_RGB555_2X8_PADHI_LE 135 
#define  V4L2_MBUS_FMT_RGB565_2X8_LE 134 
#define  V4L2_MBUS_FMT_SBGGR10_2X8_PADHI_LE 133 
#define  V4L2_MBUS_FMT_SBGGR8_1X8 132 
#define  V4L2_MBUS_FMT_UYVY8_2X8 131 
#define  V4L2_MBUS_FMT_VYUY8_2X8 130 
#define  V4L2_MBUS_FMT_YUYV8_2X8 129 
#define  V4L2_MBUS_FMT_YVYU8_2X8 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int mt9m111_setfmt_bayer10 (struct i2c_client*) ; 
 int mt9m111_setfmt_bayer8 (struct i2c_client*) ; 
 int mt9m111_setfmt_rgb555 (struct i2c_client*) ; 
 int mt9m111_setfmt_rgb565 (struct i2c_client*) ; 
 int mt9m111_setfmt_yuv (struct i2c_client*) ; 
 struct mt9m111* to_mt9m111 (struct i2c_client*) ; 

__attribute__((used)) static int mt9m111_set_pixfmt(struct i2c_client *client,
			      enum v4l2_mbus_pixelcode code)
{
	struct mt9m111 *mt9m111 = to_mt9m111(client);
	int ret;

	switch (code) {
	case V4L2_MBUS_FMT_SBGGR8_1X8:
		ret = mt9m111_setfmt_bayer8(client);
		break;
	case V4L2_MBUS_FMT_SBGGR10_2X8_PADHI_LE:
		ret = mt9m111_setfmt_bayer10(client);
		break;
	case V4L2_MBUS_FMT_RGB555_2X8_PADHI_LE:
		ret = mt9m111_setfmt_rgb555(client);
		break;
	case V4L2_MBUS_FMT_RGB565_2X8_LE:
		ret = mt9m111_setfmt_rgb565(client);
		break;
	case V4L2_MBUS_FMT_UYVY8_2X8:
		mt9m111->swap_yuv_y_chromas = 0;
		mt9m111->swap_yuv_cb_cr = 0;
		ret = mt9m111_setfmt_yuv(client);
		break;
	case V4L2_MBUS_FMT_VYUY8_2X8:
		mt9m111->swap_yuv_y_chromas = 0;
		mt9m111->swap_yuv_cb_cr = 1;
		ret = mt9m111_setfmt_yuv(client);
		break;
	case V4L2_MBUS_FMT_YUYV8_2X8:
		mt9m111->swap_yuv_y_chromas = 1;
		mt9m111->swap_yuv_cb_cr = 0;
		ret = mt9m111_setfmt_yuv(client);
		break;
	case V4L2_MBUS_FMT_YVYU8_2X8:
		mt9m111->swap_yuv_y_chromas = 1;
		mt9m111->swap_yuv_cb_cr = 1;
		ret = mt9m111_setfmt_yuv(client);
		break;
	default:
		dev_err(&client->dev, "Pixel format not handled : %x\n",
			code);
		ret = -EINVAL;
	}

	return ret;
}