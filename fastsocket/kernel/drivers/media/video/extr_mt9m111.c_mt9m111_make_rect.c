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
struct v4l2_rect {void* height; int /*<<< orphan*/  top; void* width; int /*<<< orphan*/  left; } ;
struct mt9m111 {TYPE_1__* fmt; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {scalar_t__ code; } ;

/* Variables and functions */
 void* ALIGN (void*,int) ; 
 int /*<<< orphan*/  MT9M111_MAX_HEIGHT ; 
 int /*<<< orphan*/  MT9M111_MAX_WIDTH ; 
 int /*<<< orphan*/  MT9M111_MIN_DARK_COLS ; 
 int /*<<< orphan*/  MT9M111_MIN_DARK_ROWS ; 
 scalar_t__ V4L2_MBUS_FMT_SBGGR10_2X8_PADHI_LE ; 
 scalar_t__ V4L2_MBUS_FMT_SBGGR8_1X8 ; 
 int mt9m111_setup_rect (struct i2c_client*,struct v4l2_rect*) ; 
 int /*<<< orphan*/  soc_camera_limit_side (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct mt9m111* to_mt9m111 (struct i2c_client*) ; 

__attribute__((used)) static int mt9m111_make_rect(struct i2c_client *client,
			     struct v4l2_rect *rect)
{
	struct mt9m111 *mt9m111 = to_mt9m111(client);

	if (mt9m111->fmt->code == V4L2_MBUS_FMT_SBGGR8_1X8 ||
	    mt9m111->fmt->code == V4L2_MBUS_FMT_SBGGR10_2X8_PADHI_LE) {
		/* Bayer format - even size lengths */
		rect->width	= ALIGN(rect->width, 2);
		rect->height	= ALIGN(rect->height, 2);
		/* Let the user play with the starting pixel */
	}

	/* FIXME: the datasheet doesn't specify minimum sizes */
	soc_camera_limit_side(&rect->left, &rect->width,
		     MT9M111_MIN_DARK_COLS, 2, MT9M111_MAX_WIDTH);

	soc_camera_limit_side(&rect->top, &rect->height,
		     MT9M111_MIN_DARK_ROWS, 2, MT9M111_MAX_HEIGHT);

	return mt9m111_setup_rect(client, rect);
}