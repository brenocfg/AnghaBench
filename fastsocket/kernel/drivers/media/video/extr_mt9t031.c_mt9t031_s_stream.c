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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MT9T031_OUTPUT_CONTROL ; 
 int reg_clear (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int reg_set (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9t031_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int ret;

	if (enable)
		/* Switch to master "normal" mode */
		ret = reg_set(client, MT9T031_OUTPUT_CONTROL, 2);
	else
		/* Stop sensor readout */
		ret = reg_clear(client, MT9T031_OUTPUT_CONTROL, 2);

	if (ret < 0)
		return -EIO;

	return 0;
}