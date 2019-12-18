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
struct v4l2_sliced_vbi_data {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct saa7127_state {scalar_t__ ident; struct v4l2_subdev sd; } ;
struct i2c_device_id {scalar_t__ driver_data; } ;
struct i2c_client {int addr; TYPE_1__* adapter; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  SAA7127_INPUT_TYPE_NORMAL ; 
 int /*<<< orphan*/  SAA7127_INPUT_TYPE_TEST_IMAGE ; 
 int /*<<< orphan*/  SAA7127_OUTPUT_TYPE_BOTH ; 
 int SAA7129_REG_FADE_KEY_COL2 ; 
 scalar_t__ V4L2_IDENT_SAA7127 ; 
 scalar_t__ V4L2_IDENT_SAA7129 ; 
 int /*<<< orphan*/  V4L2_STD_NTSC ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct saa7127_state*) ; 
 struct saa7127_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7127_init_config_common ; 
 int /*<<< orphan*/  saa7127_ops ; 
 int saa7127_read (struct v4l2_subdev*,int) ; 
 int /*<<< orphan*/  saa7127_set_cc (struct v4l2_subdev*,struct v4l2_sliced_vbi_data*) ; 
 int /*<<< orphan*/  saa7127_set_input_type (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7127_set_output_type (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7127_set_std (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7127_set_video_enable (struct v4l2_subdev*,int) ; 
 int /*<<< orphan*/  saa7127_set_vps (struct v4l2_subdev*,struct v4l2_sliced_vbi_data*) ; 
 int /*<<< orphan*/  saa7127_set_wss (struct v4l2_subdev*,struct v4l2_sliced_vbi_data*) ; 
 int /*<<< orphan*/  saa7127_set_xds (struct v4l2_subdev*,struct v4l2_sliced_vbi_data*) ; 
 int /*<<< orphan*/  saa7127_write (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  saa7127_write_inittab (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7129_init_config_extra ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int test_image ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*,int) ; 

__attribute__((used)) static int saa7127_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct saa7127_state *state;
	struct v4l2_subdev *sd;
	struct v4l2_sliced_vbi_data vbi = { 0, 0, 0, 0 };  /* set to disabled */

	/* Check if the adapter supports the needed features */
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -EIO;

	v4l_dbg(1, debug, client, "detecting saa7127 client on address 0x%x\n",
			client->addr << 1);

	state = kzalloc(sizeof(struct saa7127_state), GFP_KERNEL);
	if (state == NULL)
		return -ENOMEM;

	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &saa7127_ops);

	/* First test register 0: Bits 5-7 are a version ID (should be 0),
	   and bit 2 should also be 0.
	   This is rather general, so the second test is more specific and
	   looks at the 'ending point of burst in clock cycles' which is
	   0x1d after a reset and not expected to ever change. */
	if ((saa7127_read(sd, 0) & 0xe4) != 0 ||
			(saa7127_read(sd, 0x29) & 0x3f) != 0x1d) {
		v4l2_dbg(1, debug, sd, "saa7127 not found\n");
		kfree(state);
		return -ENODEV;
	}

	if (id->driver_data) {	/* Chip type is already known */
		state->ident = id->driver_data;
	} else {		/* Needs detection */
		int read_result;

		/* Detect if it's an saa7129 */
		read_result = saa7127_read(sd, SAA7129_REG_FADE_KEY_COL2);
		saa7127_write(sd, SAA7129_REG_FADE_KEY_COL2, 0xaa);
		if (saa7127_read(sd, SAA7129_REG_FADE_KEY_COL2) == 0xaa) {
			saa7127_write(sd, SAA7129_REG_FADE_KEY_COL2,
					read_result);
			state->ident = V4L2_IDENT_SAA7129;
			strlcpy(client->name, "saa7129", I2C_NAME_SIZE);
		} else {
			state->ident = V4L2_IDENT_SAA7127;
			strlcpy(client->name, "saa7127", I2C_NAME_SIZE);
		}
	}

	v4l2_info(sd, "%s found @ 0x%x (%s)\n", client->name,
			client->addr << 1, client->adapter->name);

	v4l2_dbg(1, debug, sd, "Configuring encoder\n");
	saa7127_write_inittab(sd, saa7127_init_config_common);
	saa7127_set_std(sd, V4L2_STD_NTSC);
	saa7127_set_output_type(sd, SAA7127_OUTPUT_TYPE_BOTH);
	saa7127_set_vps(sd, &vbi);
	saa7127_set_wss(sd, &vbi);
	saa7127_set_cc(sd, &vbi);
	saa7127_set_xds(sd, &vbi);
	if (test_image == 1)
		/* The Encoder has an internal Colorbar generator */
		/* This can be used for debugging */
		saa7127_set_input_type(sd, SAA7127_INPUT_TYPE_TEST_IMAGE);
	else
		saa7127_set_input_type(sd, SAA7127_INPUT_TYPE_NORMAL);
	saa7127_set_video_enable(sd, 1);

	if (state->ident == V4L2_IDENT_SAA7129)
		saa7127_write_inittab(sd, saa7129_init_config_extra);
	return 0;
}