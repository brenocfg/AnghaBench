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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct tvp5150 {int enable; int bright; int contrast; int sat; scalar_t__ hue; int /*<<< orphan*/  input; int /*<<< orphan*/  norm; struct v4l2_subdev sd; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int addr; TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_SMBUS_READ_BYTE ; 
 int I2C_FUNC_SMBUS_WRITE_BYTE_DATA ; 
 int /*<<< orphan*/  TVP5150_COMPOSITE1 ; 
 int /*<<< orphan*/  TVP5150_LSB_DEV_ID ; 
 int /*<<< orphan*/  TVP5150_MSB_DEV_ID ; 
 int /*<<< orphan*/  TVP5150_REV_SELECT ; 
 int /*<<< orphan*/  TVP5150_ROM_MAJOR_VER ; 
 int /*<<< orphan*/  TVP5150_ROM_MINOR_VER ; 
 int /*<<< orphan*/  V4L2_STD_ALL ; 
 int debug ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_1__*,int) ; 
 struct tvp5150* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvp5150_log_status (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  tvp5150_ops ; 
 int tvp5150_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvp5150_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,int,int) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tvp5150_probe(struct i2c_client *c,
			 const struct i2c_device_id *id)
{
	struct tvp5150 *core;
	struct v4l2_subdev *sd;
	u8 msb_id, lsb_id, msb_rom, lsb_rom;

	/* Check if the adapter supports the needed features */
	if (!i2c_check_functionality(c->adapter,
	     I2C_FUNC_SMBUS_READ_BYTE | I2C_FUNC_SMBUS_WRITE_BYTE_DATA))
		return -EIO;

	core = kzalloc(sizeof(struct tvp5150), GFP_KERNEL);
	if (!core) {
		return -ENOMEM;
	}
	sd = &core->sd;
	v4l2_i2c_subdev_init(sd, c, &tvp5150_ops);
	v4l_info(c, "chip found @ 0x%02x (%s)\n",
		 c->addr << 1, c->adapter->name);

	msb_id = tvp5150_read(sd, TVP5150_MSB_DEV_ID);
	lsb_id = tvp5150_read(sd, TVP5150_LSB_DEV_ID);
	msb_rom = tvp5150_read(sd, TVP5150_ROM_MAJOR_VER);
	lsb_rom = tvp5150_read(sd, TVP5150_ROM_MINOR_VER);

	if (msb_rom == 4 && lsb_rom == 0) { /* Is TVP5150AM1 */
		v4l2_info(sd, "tvp%02x%02xam1 detected.\n", msb_id, lsb_id);

		/* ITU-T BT.656.4 timing */
		tvp5150_write(sd, TVP5150_REV_SELECT, 0);
	} else {
		if (msb_rom == 3 || lsb_rom == 0x21) { /* Is TVP5150A */
			v4l2_info(sd, "tvp%02x%02xa detected.\n", msb_id, lsb_id);
		} else {
			v4l2_info(sd, "*** unknown tvp%02x%02x chip detected.\n",
					msb_id, lsb_id);
			v4l2_info(sd, "*** Rom ver is %d.%d\n", msb_rom, lsb_rom);
		}
	}

	core->norm = V4L2_STD_ALL;	/* Default is autodetect */
	core->input = TVP5150_COMPOSITE1;
	core->enable = 1;
	core->bright = 128;
	core->contrast = 128;
	core->hue = 0;
	core->sat = 128;

	if (debug > 1)
		tvp5150_log_status(sd);
	return 0;
}