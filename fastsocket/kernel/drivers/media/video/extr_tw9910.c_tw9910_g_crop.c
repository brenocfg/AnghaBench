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
struct v4l2_subdev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ top; scalar_t__ left; } ;
struct v4l2_crop {int /*<<< orphan*/  type; TYPE_1__ c; } ;
struct tw9910_priv {TYPE_2__* scale; } ;
struct i2c_client {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 struct tw9910_priv* to_tw9910 (struct i2c_client*) ; 
 int tw9910_s_crop (struct v4l2_subdev*,struct v4l2_crop*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int tw9910_g_crop(struct v4l2_subdev *sd, struct v4l2_crop *a)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct tw9910_priv *priv = to_tw9910(client);

	if (!priv->scale) {
		int ret;
		struct v4l2_crop crop = {
			.c = {
				.left	= 0,
				.top	= 0,
				.width	= 640,
				.height	= 480,
			},
		};
		ret = tw9910_s_crop(sd, &crop);
		if (ret < 0)
			return ret;
	}

	a->c.left	= 0;
	a->c.top	= 0;
	a->c.width	= priv->scale->width;
	a->c.height	= priv->scale->height;
	a->type		= V4L2_BUF_TYPE_VIDEO_CAPTURE;

	return 0;
}