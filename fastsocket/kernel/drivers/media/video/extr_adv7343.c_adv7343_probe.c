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
struct i2c_device_id {int dummy; } ;
struct i2c_client {int addr; TYPE_1__* adapter; } ;
struct adv7343_state {int reg00; int reg01; int reg02; int reg35; int /*<<< orphan*/  sd; int /*<<< orphan*/  std; int /*<<< orphan*/  output; int /*<<< orphan*/  reg82; int /*<<< orphan*/  reg80; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV7343_COMPOSITE_ID ; 
 int /*<<< orphan*/  ADV7343_SD_MODE_REG1_DEFAULT ; 
 int /*<<< orphan*/  ADV7343_SD_MODE_REG2_DEFAULT ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  V4L2_STD_NTSC ; 
 int adv7343_initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adv7343_ops ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct adv7343_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (int /*<<< orphan*/ *,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adv7343_probe(struct i2c_client *client,
				const struct i2c_device_id *id)
{
	struct adv7343_state *state;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	state = kzalloc(sizeof(struct adv7343_state), GFP_KERNEL);
	if (state == NULL)
		return -ENOMEM;

	state->reg00	= 0x80;
	state->reg01	= 0x00;
	state->reg02	= 0x20;
	state->reg35	= 0x00;
	state->reg80	= ADV7343_SD_MODE_REG1_DEFAULT;
	state->reg82	= ADV7343_SD_MODE_REG2_DEFAULT;

	state->output = ADV7343_COMPOSITE_ID;
	state->std = V4L2_STD_NTSC;

	v4l2_i2c_subdev_init(&state->sd, client, &adv7343_ops);
	return adv7343_initialize(&state->sd);
}