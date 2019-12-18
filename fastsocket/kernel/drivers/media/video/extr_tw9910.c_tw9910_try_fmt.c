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
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; int /*<<< orphan*/  field; } ;
struct tw9910_scale_ctrl {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct soc_camera_device {int dummy; } ;
struct TYPE_2__ {struct soc_camera_device* platform_data; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_JPEG ; 
 int /*<<< orphan*/  V4L2_FIELD_ANY ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED_BT ; 
 int /*<<< orphan*/  V4L2_MBUS_FMT_UYVY8_2X8 ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 struct tw9910_scale_ctrl* tw9910_select_norm (struct soc_camera_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int tw9910_try_fmt(struct v4l2_subdev *sd,
			  struct v4l2_mbus_framefmt *mf)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct soc_camera_device *icd = client->dev.platform_data;
	const struct tw9910_scale_ctrl *scale;

	if (V4L2_FIELD_ANY == mf->field) {
		mf->field = V4L2_FIELD_INTERLACED_BT;
	} else if (V4L2_FIELD_INTERLACED_BT != mf->field) {
		dev_err(&client->dev, "Field type %d invalid.\n", mf->field);
		return -EINVAL;
	}

	mf->code = V4L2_MBUS_FMT_UYVY8_2X8;
	mf->colorspace = V4L2_COLORSPACE_JPEG;

	/*
	 * select suitable norm
	 */
	scale = tw9910_select_norm(icd, mf->width, mf->height);
	if (!scale)
		return -EINVAL;

	mf->width	= scale->width;
	mf->height	= scale->height;

	return 0;
}