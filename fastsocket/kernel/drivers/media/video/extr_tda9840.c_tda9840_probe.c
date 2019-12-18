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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_SMBUS_READ_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_WRITE_BYTE_DATA ; 
 int /*<<< orphan*/  LEVEL_ADJUST ; 
 int /*<<< orphan*/  STEREO_ADJUST ; 
 int /*<<< orphan*/  SWITCH ; 
 int /*<<< orphan*/  TDA9840_SET_STEREO ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_1__*,int) ; 
 struct v4l2_subdev* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda9840_ops ; 
 int /*<<< orphan*/  tda9840_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tda9840_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct v4l2_subdev *sd;

	/* let's see whether this adapter can support what we need */
	if (!i2c_check_functionality(client->adapter,
			I2C_FUNC_SMBUS_READ_BYTE_DATA |
			I2C_FUNC_SMBUS_WRITE_BYTE_DATA))
		return -EIO;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	sd = kmalloc(sizeof(struct v4l2_subdev), GFP_KERNEL);
	if (sd == NULL)
		return -ENOMEM;
	v4l2_i2c_subdev_init(sd, client, &tda9840_ops);

	/* set initial values for level & stereo - adjustment, mode */
	tda9840_write(sd, LEVEL_ADJUST, 0);
	tda9840_write(sd, STEREO_ADJUST, 0);
	tda9840_write(sd, SWITCH, TDA9840_SET_STEREO);
	return 0;
}