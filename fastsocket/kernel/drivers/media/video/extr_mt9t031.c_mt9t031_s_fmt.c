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
typedef  int /*<<< orphan*/  u16 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct mt9t031 {struct v4l2_rect rect; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT9T031_MAX_HEIGHT ; 
 int /*<<< orphan*/  MT9T031_MAX_WIDTH ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_MBUS_FMT_SBGGR10_1X10 ; 
 int mt9t031_set_params (struct i2c_client*,struct v4l2_rect*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt9t031_skip (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mt9t031* to_mt9t031 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9t031_s_fmt(struct v4l2_subdev *sd,
			 struct v4l2_mbus_framefmt *mf)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct mt9t031 *mt9t031 = to_mt9t031(client);
	u16 xskip, yskip;
	struct v4l2_rect rect = mt9t031->rect;

	/*
	 * try_fmt has put width and height within limits.
	 * S_FMT: use binning and skipping for scaling
	 */
	xskip = mt9t031_skip(&rect.width, mf->width, MT9T031_MAX_WIDTH);
	yskip = mt9t031_skip(&rect.height, mf->height, MT9T031_MAX_HEIGHT);

	mf->code	= V4L2_MBUS_FMT_SBGGR10_1X10;
	mf->colorspace	= V4L2_COLORSPACE_SRGB;

	/* mt9t031_set_params() doesn't change width and height */
	return mt9t031_set_params(client, &rect, xskip, yskip);
}