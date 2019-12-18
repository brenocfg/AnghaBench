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
struct v4l2_subdev {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct v4l2_ctrl_handler {int error; } ;
struct saa717x_state {int input; int enable; int audio; int audio_input; int audio_main_vol_l; int audio_main_vol_r; int /*<<< orphan*/  tuner_audio_mode; scalar_t__ playback; int /*<<< orphan*/  std; struct v4l2_ctrl_handler hdl; struct v4l2_subdev sd; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int addr; TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TUNER_AUDIO_STEREO ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_BALANCE ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_BASS ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_MUTE ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_TREBLE ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_VOLUME ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_CONTRAST ; 
 int /*<<< orphan*/  V4L2_CID_HUE ; 
 int /*<<< orphan*/  V4L2_CID_SATURATION ; 
 int /*<<< orphan*/  V4L2_STD_NTSC ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct saa717x_state*) ; 
 struct saa717x_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_init_initialize ; 
 int /*<<< orphan*/  saa717x_ctrl_ops ; 
 int /*<<< orphan*/  saa717x_ops ; 
 int saa717x_read (struct v4l2_subdev*,int) ; 
 scalar_t__ saa717x_write (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  saa717x_write_regs (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout (int) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (struct v4l2_ctrl_handler*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (struct v4l2_ctrl_handler*) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,...) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int saa717x_probe(struct i2c_client *client,
			 const struct i2c_device_id *did)
{
	struct saa717x_state *decoder;
	struct v4l2_ctrl_handler *hdl;
	struct v4l2_subdev *sd;
	u8 id = 0;
	char *p = "";

	/* Check if the adapter supports the needed features */
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -EIO;

	decoder = kzalloc(sizeof(struct saa717x_state), GFP_KERNEL);
	if (decoder == NULL)
		return -ENOMEM;

	sd = &decoder->sd;
	v4l2_i2c_subdev_init(sd, client, &saa717x_ops);

	if (saa717x_write(sd, 0x5a4, 0xfe) &&
			saa717x_write(sd, 0x5a5, 0x0f) &&
			saa717x_write(sd, 0x5a6, 0x00) &&
			saa717x_write(sd, 0x5a7, 0x01))
		id = saa717x_read(sd, 0x5a0);
	if (id != 0xc2 && id != 0x32 && id != 0xf2 && id != 0x6c) {
		v4l2_dbg(1, debug, sd, "saa717x not found (id=%02x)\n", id);
		kfree(decoder);
		return -ENODEV;
	}
	if (id == 0xc2)
		p = "saa7173";
	else if (id == 0x32)
		p = "saa7174A";
	else if (id == 0x6c)
		p = "saa7174HL";
	else
		p = "saa7171";
	v4l2_info(sd, "%s found @ 0x%x (%s)\n", p,
			client->addr << 1, client->adapter->name);

	hdl = &decoder->hdl;
	v4l2_ctrl_handler_init(hdl, 9);
	/* add in ascending ID order */
	v4l2_ctrl_new_std(hdl, &saa717x_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
	v4l2_ctrl_new_std(hdl, &saa717x_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 255, 1, 68);
	v4l2_ctrl_new_std(hdl, &saa717x_ctrl_ops,
			V4L2_CID_SATURATION, 0, 255, 1, 64);
	v4l2_ctrl_new_std(hdl, &saa717x_ctrl_ops,
			V4L2_CID_HUE, -128, 127, 1, 0);
	v4l2_ctrl_new_std(hdl, &saa717x_ctrl_ops,
			V4L2_CID_AUDIO_VOLUME, 0, 65535, 65535 / 100, 42000);
	v4l2_ctrl_new_std(hdl, &saa717x_ctrl_ops,
			V4L2_CID_AUDIO_BALANCE, 0, 65535, 65535 / 100, 32768);
	v4l2_ctrl_new_std(hdl, &saa717x_ctrl_ops,
			V4L2_CID_AUDIO_BASS, -16, 15, 1, 0);
	v4l2_ctrl_new_std(hdl, &saa717x_ctrl_ops,
			V4L2_CID_AUDIO_TREBLE, -16, 15, 1, 0);
	v4l2_ctrl_new_std(hdl, &saa717x_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	sd->ctrl_handler = hdl;
	if (hdl->error) {
		int err = hdl->error;

		v4l2_ctrl_handler_free(hdl);
		kfree(decoder);
		return err;
	}

	decoder->std = V4L2_STD_NTSC;
	decoder->input = -1;
	decoder->enable = 1;

	/* FIXME!! */
	decoder->playback = 0;	/* initially capture mode used */
	decoder->audio = 1; /* DECODER_AUDIO_48_KHZ */

	decoder->audio_input = 2; /* FIXME!! */

	decoder->tuner_audio_mode = TUNER_AUDIO_STEREO;
	/* set volume, bass and treble */
	decoder->audio_main_vol_l = 6;
	decoder->audio_main_vol_r = 6;

	v4l2_dbg(1, debug, sd, "writing init values\n");

	/* FIXME!! */
	saa717x_write_regs(sd, reg_init_initialize);

	v4l2_ctrl_handler_setup(hdl);

	set_current_state(TASK_INTERRUPTIBLE);
	schedule_timeout(2*HZ);
	return 0;
}