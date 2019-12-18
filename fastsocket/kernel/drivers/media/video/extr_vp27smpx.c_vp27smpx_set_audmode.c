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
typedef  int u8 ;
typedef  int u32 ;
struct vp27smpx_state {int audmode; } ;
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
#define  V4L2_TUNER_MODE_LANG1 132 
#define  V4L2_TUNER_MODE_LANG1_LANG2 131 
#define  V4L2_TUNER_MODE_LANG2 130 
#define  V4L2_TUNER_MODE_MONO 129 
#define  V4L2_TUNER_MODE_STEREO 128 
 int i2c_master_send (struct i2c_client*,int*,int) ; 
 struct vp27smpx_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static void vp27smpx_set_audmode(struct v4l2_subdev *sd, u32 audmode)
{
	struct vp27smpx_state *state = to_state(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	u8 data[3] = { 0x00, 0x00, 0x04 };

	switch (audmode) {
	case V4L2_TUNER_MODE_MONO:
	case V4L2_TUNER_MODE_LANG1:
		break;
	case V4L2_TUNER_MODE_STEREO:
	case V4L2_TUNER_MODE_LANG1_LANG2:
		data[1] = 0x01;
		break;
	case V4L2_TUNER_MODE_LANG2:
		data[1] = 0x02;
		break;
	}

	if (i2c_master_send(client, data, sizeof(data)) != sizeof(data))
		v4l2_err(sd, "I/O error setting audmode\n");
	else
		state->audmode = audmode;
}