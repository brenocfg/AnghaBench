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
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int height; int width; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; } ;
struct mt9m111_datafmt {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; } ;
struct mt9m111 {struct mt9m111_datafmt* fmt; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 void* ALIGN (int,int) ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int MT9M111_MAX_HEIGHT ; 
 int MT9M111_MAX_WIDTH ; 
 int /*<<< orphan*/  V4L2_MBUS_FMT_SBGGR10_2X8_PADHI_LE ; 
 int /*<<< orphan*/  V4L2_MBUS_FMT_SBGGR8_1X8 ; 
 int /*<<< orphan*/  mt9m111_colour_fmts ; 
 struct mt9m111_datafmt* mt9m111_find_datafmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mt9m111* to_mt9m111 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9m111_try_fmt(struct v4l2_subdev *sd,
			   struct v4l2_mbus_framefmt *mf)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct mt9m111 *mt9m111 = to_mt9m111(client);
	const struct mt9m111_datafmt *fmt;
	bool bayer = mf->code == V4L2_MBUS_FMT_SBGGR8_1X8 ||
		mf->code == V4L2_MBUS_FMT_SBGGR10_2X8_PADHI_LE;

	fmt = mt9m111_find_datafmt(mf->code, mt9m111_colour_fmts,
				   ARRAY_SIZE(mt9m111_colour_fmts));
	if (!fmt) {
		fmt = mt9m111->fmt;
		mf->code = fmt->code;
	}

	/*
	 * With Bayer format enforce even side lengths, but let the user play
	 * with the starting pixel
	 */

	if (mf->height > MT9M111_MAX_HEIGHT)
		mf->height = MT9M111_MAX_HEIGHT;
	else if (mf->height < 2)
		mf->height = 2;
	else if (bayer)
		mf->height = ALIGN(mf->height, 2);

	if (mf->width > MT9M111_MAX_WIDTH)
		mf->width = MT9M111_MAX_WIDTH;
	else if (mf->width < 2)
		mf->width = 2;
	else if (bayer)
		mf->width = ALIGN(mf->width, 2);

	mf->colorspace = fmt->colorspace;

	return 0;
}