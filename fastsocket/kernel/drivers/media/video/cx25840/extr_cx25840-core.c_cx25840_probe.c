#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct v4l2_subdev {TYPE_1__* ctrl_handler; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int addr; TYPE_5__* adapter; } ;
struct TYPE_6__ {int error; } ;
struct cx25840_state {int audclk_freq; int vbi_line_offset; int id; int rev; TYPE_1__ hdl; void* volume; void* mute; int /*<<< orphan*/  audmode; scalar_t__ pvr150_workaround; int /*<<< orphan*/  aud_input; int /*<<< orphan*/  vid_input; struct i2c_client* c; struct v4l2_subdev sd; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX25840_AUDIO8 ; 
 int /*<<< orphan*/  CX25840_COMPOSITE7 ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_BALANCE ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_BASS ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_MUTE ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_TREBLE ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_VOLUME ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_CONTRAST ; 
 int /*<<< orphan*/  V4L2_CID_HUE ; 
 int /*<<< orphan*/  V4L2_CID_SATURATION ; 
#define  V4L2_IDENT_CX2310X_AV 137 
#define  V4L2_IDENT_CX23885_AV 136 
#define  V4L2_IDENT_CX23887_AV 135 
#define  V4L2_IDENT_CX23888_AV 134 
#define  V4L2_IDENT_CX25836 133 
#define  V4L2_IDENT_CX25837 132 
#define  V4L2_IDENT_CX25840 131 
#define  V4L2_IDENT_CX25841 130 
#define  V4L2_IDENT_CX25842 129 
#define  V4L2_IDENT_CX25843 128 
 int V4L2_IDENT_NONE ; 
 int /*<<< orphan*/  V4L2_TUNER_MODE_LANG1 ; 
 int /*<<< orphan*/  cx25840_audio_ctrl_ops ; 
 int /*<<< orphan*/  cx25840_ctrl_ops ; 
 int /*<<< orphan*/  cx25840_debug ; 
 int /*<<< orphan*/  cx25840_ir_probe (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  cx25840_ops ; 
 int cx25840_read (struct i2c_client*,int) ; 
 int /*<<< orphan*/  cx25840_write (struct i2c_client*,int,int) ; 
 int get_cx2388x_ident (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_cx2583x (struct cx25840_state*) ; 
 int /*<<< orphan*/  kfree (struct cx25840_state*) ; 
 struct cx25840_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_cluster (int,void**) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_1__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (TYPE_1__*) ; 
 void* v4l2_ctrl_new_std (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*,...) ; 
 int /*<<< orphan*/  v4l_err (struct i2c_client*,char*,...) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,int,int,...) ; 

__attribute__((used)) static int cx25840_probe(struct i2c_client *client,
			 const struct i2c_device_id *did)
{
	struct cx25840_state *state;
	struct v4l2_subdev *sd;
	int default_volume;
	u32 id = V4L2_IDENT_NONE;
	u16 device_id;

	/* Check if the adapter supports the needed features */
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -EIO;

	v4l_dbg(1, cx25840_debug, client, "detecting cx25840 client on address 0x%x\n", client->addr << 1);

	device_id = cx25840_read(client, 0x101) << 8;
	device_id |= cx25840_read(client, 0x100);
	v4l_dbg(1, cx25840_debug, client, "device_id = 0x%04x\n", device_id);

	/* The high byte of the device ID should be
	 * 0x83 for the cx2583x and 0x84 for the cx2584x */
	if ((device_id & 0xff00) == 0x8300) {
		id = V4L2_IDENT_CX25836 + ((device_id >> 4) & 0xf) - 6;
	} else if ((device_id & 0xff00) == 0x8400) {
		id = V4L2_IDENT_CX25840 + ((device_id >> 4) & 0xf);
	} else if (device_id == 0x0000) {
		id = get_cx2388x_ident(client);
	} else if ((device_id & 0xfff0) == 0x5A30) {
		/* The CX23100 (0x5A3C = 23100) doesn't have an A/V decoder */
		id = V4L2_IDENT_CX2310X_AV;
	} else if ((device_id & 0xff) == (device_id >> 8)) {
		v4l_err(client,
			"likely a confused/unresponsive cx2388[578] A/V decoder"
			" found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);
		v4l_err(client, "A method to reset it from the cx25840 driver"
			" software is not known at this time\n");
		return -ENODEV;
	} else {
		v4l_dbg(1, cx25840_debug, client, "cx25840 not found\n");
		return -ENODEV;
	}

	state = kzalloc(sizeof(struct cx25840_state), GFP_KERNEL);
	if (state == NULL)
		return -ENOMEM;

	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &cx25840_ops);

	switch (id) {
	case V4L2_IDENT_CX23885_AV:
		v4l_info(client, "cx23885 A/V decoder found @ 0x%x (%s)\n",
			 client->addr << 1, client->adapter->name);
		break;
	case V4L2_IDENT_CX23887_AV:
		v4l_info(client, "cx23887 A/V decoder found @ 0x%x (%s)\n",
			 client->addr << 1, client->adapter->name);
		break;
	case V4L2_IDENT_CX23888_AV:
		v4l_info(client, "cx23888 A/V decoder found @ 0x%x (%s)\n",
			 client->addr << 1, client->adapter->name);
		break;
	case V4L2_IDENT_CX2310X_AV:
		v4l_info(client, "cx%d A/V decoder found @ 0x%x (%s)\n",
			 device_id, client->addr << 1, client->adapter->name);
		break;
	case V4L2_IDENT_CX25840:
	case V4L2_IDENT_CX25841:
	case V4L2_IDENT_CX25842:
	case V4L2_IDENT_CX25843:
		/* Note: revision '(device_id & 0x0f) == 2' was never built. The
		   marking skips from 0x1 == 22 to 0x3 == 23. */
		v4l_info(client, "cx25%3x-2%x found @ 0x%x (%s)\n",
			 (device_id & 0xfff0) >> 4,
			 (device_id & 0x0f) < 3 ? (device_id & 0x0f) + 1
						: (device_id & 0x0f),
			 client->addr << 1, client->adapter->name);
		break;
	case V4L2_IDENT_CX25836:
	case V4L2_IDENT_CX25837:
	default:
		v4l_info(client, "cx25%3x-%x found @ 0x%x (%s)\n",
			 (device_id & 0xfff0) >> 4, device_id & 0x0f,
			 client->addr << 1, client->adapter->name);
		break;
	}

	state->c = client;
	state->vid_input = CX25840_COMPOSITE7;
	state->aud_input = CX25840_AUDIO8;
	state->audclk_freq = 48000;
	state->pvr150_workaround = 0;
	state->audmode = V4L2_TUNER_MODE_LANG1;
	state->vbi_line_offset = 8;
	state->id = id;
	state->rev = device_id;
	v4l2_ctrl_handler_init(&state->hdl, 9);
	v4l2_ctrl_new_std(&state->hdl, &cx25840_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
	v4l2_ctrl_new_std(&state->hdl, &cx25840_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 127, 1, 64);
	v4l2_ctrl_new_std(&state->hdl, &cx25840_ctrl_ops,
			V4L2_CID_SATURATION, 0, 127, 1, 64);
	v4l2_ctrl_new_std(&state->hdl, &cx25840_ctrl_ops,
			V4L2_CID_HUE, -128, 127, 1, 0);
	if (!is_cx2583x(state)) {
		default_volume = cx25840_read(client, 0x8d4);
		/*
		 * Enforce the legacy PVR-350/MSP3400 to PVR-150/CX25843 volume
		 * scale mapping limits to avoid -ERANGE errors when
		 * initializing the volume control
		 */
		if (default_volume > 228) {
			/* Bottom out at -96 dB, v4l2 vol range 0x2e00-0x2fff */
			default_volume = 228;
			cx25840_write(client, 0x8d4, 228);
		}
		else if (default_volume < 20) {
			/* Top out at + 8 dB, v4l2 vol range 0xfe00-0xffff */
			default_volume = 20;
			cx25840_write(client, 0x8d4, 20);
		}
		default_volume = (((228 - default_volume) >> 1) + 23) << 9;

		state->volume = v4l2_ctrl_new_std(&state->hdl,
			&cx25840_audio_ctrl_ops, V4L2_CID_AUDIO_VOLUME,
			0, 65535, 65535 / 100, default_volume);
		state->mute = v4l2_ctrl_new_std(&state->hdl,
			&cx25840_audio_ctrl_ops, V4L2_CID_AUDIO_MUTE,
			0, 1, 1, 0);
		v4l2_ctrl_new_std(&state->hdl, &cx25840_audio_ctrl_ops,
			V4L2_CID_AUDIO_BALANCE,
			0, 65535, 65535 / 100, 32768);
		v4l2_ctrl_new_std(&state->hdl, &cx25840_audio_ctrl_ops,
			V4L2_CID_AUDIO_BASS,
			0, 65535, 65535 / 100, 32768);
		v4l2_ctrl_new_std(&state->hdl, &cx25840_audio_ctrl_ops,
			V4L2_CID_AUDIO_TREBLE,
			0, 65535, 65535 / 100, 32768);
	}
	sd->ctrl_handler = &state->hdl;
	if (state->hdl.error) {
		int err = state->hdl.error;

		v4l2_ctrl_handler_free(&state->hdl);
		kfree(state);
		return err;
	}
	if (!is_cx2583x(state))
		v4l2_ctrl_cluster(2, &state->volume);
	v4l2_ctrl_handler_setup(&state->hdl);

	cx25840_ir_probe(sd);
	return 0;
}