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
struct mt9v022 {int chip_control; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MT9V022_CHIP_CONTROL ; 
 scalar_t__ reg_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct mt9v022* to_mt9v022 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9v022_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct mt9v022 *mt9v022 = to_mt9v022(client);

	if (enable)
		/* Switch to master "normal" mode */
		mt9v022->chip_control &= ~0x10;
	else
		/* Switch to snapshot mode */
		mt9v022->chip_control |= 0x10;

	if (reg_write(client, MT9V022_CHIP_CONTROL, mt9v022->chip_control) < 0)
		return -EIO;
	return 0;
}