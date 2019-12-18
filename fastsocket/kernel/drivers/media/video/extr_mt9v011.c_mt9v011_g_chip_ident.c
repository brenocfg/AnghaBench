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
struct v4l2_dbg_chip_ident {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R00_MT9V011_CHIP_VERSION ; 
 int /*<<< orphan*/  V4L2_IDENT_MT9V011 ; 
 int /*<<< orphan*/  mt9v011_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int v4l2_chip_ident_i2c_client (struct i2c_client*,struct v4l2_dbg_chip_ident*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9v011_g_chip_ident(struct v4l2_subdev *sd,
				struct v4l2_dbg_chip_ident *chip)
{
	u16 version;
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	version = mt9v011_read(sd, R00_MT9V011_CHIP_VERSION);

	return v4l2_chip_ident_i2c_client(client, chip, V4L2_IDENT_MT9V011,
					  version);
}