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
struct v4l2_mbus_framefmt {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; scalar_t__ height; int /*<<< orphan*/  width; } ;
struct mt9m001_datafmt {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; } ;
struct mt9m001 {scalar_t__ fmts; struct mt9m001_datafmt* fmt; int /*<<< orphan*/  num_fmts; scalar_t__ y_skip_top; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int) ; 
 scalar_t__ MT9M001_MAX_HEIGHT ; 
 int /*<<< orphan*/  MT9M001_MAX_WIDTH ; 
 scalar_t__ MT9M001_MIN_HEIGHT ; 
 int /*<<< orphan*/  MT9M001_MIN_WIDTH ; 
 scalar_t__ mt9m001_colour_fmts ; 
 struct mt9m001_datafmt* mt9m001_find_datafmt (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct mt9m001* to_mt9m001 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt9m001_try_fmt(struct v4l2_subdev *sd,
			   struct v4l2_mbus_framefmt *mf)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct mt9m001 *mt9m001 = to_mt9m001(client);
	const struct mt9m001_datafmt *fmt;

	v4l_bound_align_image(&mf->width, MT9M001_MIN_WIDTH,
		MT9M001_MAX_WIDTH, 1,
		&mf->height, MT9M001_MIN_HEIGHT + mt9m001->y_skip_top,
		MT9M001_MAX_HEIGHT + mt9m001->y_skip_top, 0, 0);

	if (mt9m001->fmts == mt9m001_colour_fmts)
		mf->height = ALIGN(mf->height - 1, 2);

	fmt = mt9m001_find_datafmt(mf->code, mt9m001->fmts,
				   mt9m001->num_fmts);
	if (!fmt) {
		fmt = mt9m001->fmt;
		mf->code = fmt->code;
	}

	mf->colorspace	= fmt->colorspace;

	return 0;
}