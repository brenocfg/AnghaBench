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
struct v4l2_dbg_chip_ident {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TVP5150_ROM_MAJOR_VER ; 
 int /*<<< orphan*/  TVP5150_ROM_MINOR_VER ; 
 int /*<<< orphan*/  V4L2_IDENT_TVP5150 ; 
 int tvp5150_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int v4l2_chip_ident_i2c_client (struct i2c_client*,struct v4l2_dbg_chip_ident*,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int tvp5150_g_chip_ident(struct v4l2_subdev *sd,
				struct v4l2_dbg_chip_ident *chip)
{
	int rev;
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	rev = tvp5150_read(sd, TVP5150_ROM_MAJOR_VER) << 8 |
	      tvp5150_read(sd, TVP5150_ROM_MINOR_VER);

	return v4l2_chip_ident_i2c_client(client, chip, V4L2_IDENT_TVP5150,
					  rev);
}