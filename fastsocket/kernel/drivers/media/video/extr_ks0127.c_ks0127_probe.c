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
struct ks0127 {struct v4l2_subdev sd; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int addr; TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_KS0127_ADDON ; 
 int /*<<< orphan*/  KS_CMDA ; 
 int /*<<< orphan*/  init_reg_defaults () ; 
 int /*<<< orphan*/  ks0127_init (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  ks0127_ops ; 
 int /*<<< orphan*/  ks0127_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 struct ks0127* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ks0127_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct ks0127 *ks;
	struct v4l2_subdev *sd;

	v4l_info(client, "%s chip found @ 0x%x (%s)\n",
		client->addr == (I2C_KS0127_ADDON >> 1) ? "addon" : "on-board",
		client->addr << 1, client->adapter->name);

	ks = kzalloc(sizeof(*ks), GFP_KERNEL);
	if (ks == NULL)
		return -ENOMEM;
	sd = &ks->sd;
	v4l2_i2c_subdev_init(sd, client, &ks0127_ops);

	/* power up */
	init_reg_defaults();
	ks0127_write(sd, KS_CMDA, 0x2c);
	mdelay(10);

	/* reset the device */
	ks0127_init(sd);
	return 0;
}