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
struct tlv320aic23b_state {scalar_t__ muted; struct v4l2_subdev sd; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int addr; TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct tlv320aic23b_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlv320aic23b_ops ; 
 int /*<<< orphan*/  tlv320aic23b_write (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tlv320aic23b_probe(struct i2c_client *client,
			      const struct i2c_device_id *id)
{
	struct tlv320aic23b_state *state;
	struct v4l2_subdev *sd;

	/* Check if the adapter supports the needed features */
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -EIO;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	state = kzalloc(sizeof(struct tlv320aic23b_state), GFP_KERNEL);
	if (state == NULL)
		return -ENOMEM;
	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &tlv320aic23b_ops);
	state->muted = 0;

	/* Initialize tlv320aic23b */

	/* RESET */
	tlv320aic23b_write(sd, 15, 0x000);
	/* turn off DAC & mic input */
	tlv320aic23b_write(sd, 6, 0x00A);
	/* left-justified, 24-bit, master mode */
	tlv320aic23b_write(sd, 7, 0x049);
	/* set gain on both channels to +3.0 dB */
	tlv320aic23b_write(sd, 0, 0x119);
	/* set sample rate to 48 kHz */
	tlv320aic23b_write(sd, 8, 0x000);
	/* activate digital interface */
	tlv320aic23b_write(sd, 9, 0x001);
	return 0;
}