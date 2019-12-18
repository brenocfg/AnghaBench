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
struct v4l2_rect {int width; int height; int left; int top; } ;
struct mt9m111 {TYPE_1__* fmt; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {scalar_t__ code; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLUMN_START ; 
 int MT9M111_MAX_HEIGHT ; 
 int MT9M111_MAX_WIDTH ; 
 int /*<<< orphan*/  REDUCER_XSIZE_A ; 
 int /*<<< orphan*/  REDUCER_XSIZE_B ; 
 int /*<<< orphan*/  REDUCER_XZOOM_A ; 
 int /*<<< orphan*/  REDUCER_XZOOM_B ; 
 int /*<<< orphan*/  REDUCER_YSIZE_A ; 
 int /*<<< orphan*/  REDUCER_YSIZE_B ; 
 int /*<<< orphan*/  REDUCER_YZOOM_A ; 
 int /*<<< orphan*/  REDUCER_YZOOM_B ; 
 int /*<<< orphan*/  ROW_START ; 
 scalar_t__ V4L2_MBUS_FMT_SBGGR10_2X8_PADHI_LE ; 
 scalar_t__ V4L2_MBUS_FMT_SBGGR8_1X8 ; 
 int /*<<< orphan*/  WINDOW_HEIGHT ; 
 int /*<<< orphan*/  WINDOW_WIDTH ; 
 int reg_write (int /*<<< orphan*/ ,int) ; 
 struct mt9m111* to_mt9m111 (struct i2c_client*) ; 

__attribute__((used)) static int mt9m111_setup_rect(struct i2c_client *client,
			      struct v4l2_rect *rect)
{
	struct mt9m111 *mt9m111 = to_mt9m111(client);
	int ret, is_raw_format;
	int width = rect->width;
	int height = rect->height;

	if (mt9m111->fmt->code == V4L2_MBUS_FMT_SBGGR8_1X8 ||
	    mt9m111->fmt->code == V4L2_MBUS_FMT_SBGGR10_2X8_PADHI_LE)
		is_raw_format = 1;
	else
		is_raw_format = 0;

	ret = reg_write(COLUMN_START, rect->left);
	if (!ret)
		ret = reg_write(ROW_START, rect->top);

	if (is_raw_format) {
		if (!ret)
			ret = reg_write(WINDOW_WIDTH, width);
		if (!ret)
			ret = reg_write(WINDOW_HEIGHT, height);
	} else {
		if (!ret)
			ret = reg_write(REDUCER_XZOOM_B, MT9M111_MAX_WIDTH);
		if (!ret)
			ret = reg_write(REDUCER_YZOOM_B, MT9M111_MAX_HEIGHT);
		if (!ret)
			ret = reg_write(REDUCER_XSIZE_B, width);
		if (!ret)
			ret = reg_write(REDUCER_YSIZE_B, height);
		if (!ret)
			ret = reg_write(REDUCER_XZOOM_A, MT9M111_MAX_WIDTH);
		if (!ret)
			ret = reg_write(REDUCER_YZOOM_A, MT9M111_MAX_HEIGHT);
		if (!ret)
			ret = reg_write(REDUCER_XSIZE_A, width);
		if (!ret)
			ret = reg_write(REDUCER_YSIZE_A, height);
	}

	return ret;
}