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
struct v4l2_subdev {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int addr; TYPE_1__* adapter; } ;
struct bt819 {int enable; int contrast; int sat; scalar_t__ hue; scalar_t__ bright; scalar_t__ input; int /*<<< orphan*/  norm; int /*<<< orphan*/  ident; struct v4l2_subdev sd; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  V4L2_IDENT_BT815A ; 
 int /*<<< orphan*/  V4L2_IDENT_BT817A ; 
 int /*<<< orphan*/  V4L2_IDENT_BT819A ; 
 int /*<<< orphan*/  V4L2_STD_NTSC ; 
 int bt819_init (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  bt819_ops ; 
 int bt819_read (struct bt819*,int) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct bt819* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bt819_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int i, ver;
	struct bt819 *decoder;
	struct v4l2_subdev *sd;
	const char *name;

	/* Check if the adapter supports the needed features */
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	decoder = kzalloc(sizeof(struct bt819), GFP_KERNEL);
	if (decoder == NULL)
		return -ENOMEM;
	sd = &decoder->sd;
	v4l2_i2c_subdev_init(sd, client, &bt819_ops);

	ver = bt819_read(decoder, 0x17);
	switch (ver & 0xf0) {
	case 0x70:
		name = "bt819a";
		decoder->ident = V4L2_IDENT_BT819A;
		break;
	case 0x60:
		name = "bt817a";
		decoder->ident = V4L2_IDENT_BT817A;
		break;
	case 0x20:
		name = "bt815a";
		decoder->ident = V4L2_IDENT_BT815A;
		break;
	default:
		v4l2_dbg(1, debug, sd,
			"unknown chip version 0x%02x\n", ver);
		return -ENODEV;
	}

	v4l_info(client, "%s found @ 0x%x (%s)\n", name,
			client->addr << 1, client->adapter->name);

	decoder->norm = V4L2_STD_NTSC;
	decoder->input = 0;
	decoder->enable = 1;
	decoder->bright = 0;
	decoder->contrast = 0xd8;	/* 100% of original signal */
	decoder->hue = 0;
	decoder->sat = 0xfe;		/* 100% of original signal */

	i = bt819_init(sd);
	if (i < 0)
		v4l2_dbg(1, debug, sd, "init status %d\n", i);
	return 0;
}