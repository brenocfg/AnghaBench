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
struct v4l2_subdev {int dummy; } ;
struct v4l2_control {int id; int value; } ;
struct tda7432 {int muted; int volume; int lf; int rf; int bass; int treble; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_AUDIO_BALANCE 132 
#define  V4L2_CID_AUDIO_BASS 131 
#define  V4L2_CID_AUDIO_MUTE 130 
#define  V4L2_CID_AUDIO_TREBLE 129 
#define  V4L2_CID_AUDIO_VOLUME 128 
 int /*<<< orphan*/  maxvol ; 
 struct tda7432* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int tda7432_g_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
{
	struct tda7432 *t = to_state(sd);

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
		ctrl->value=t->muted;
		return 0;
	case V4L2_CID_AUDIO_VOLUME:
		if (!maxvol){  /* max +20db */
			ctrl->value = ( 0x6f - (t->volume & 0x7F) ) * 630;
		} else {       /* max 0db   */
			ctrl->value = ( 0x6f - (t->volume & 0x7F) ) * 829;
		}
		return 0;
	case V4L2_CID_AUDIO_BALANCE:
	{
		if ( (t->lf) < (t->rf) )
			/* right is attenuated, balance shifted left */
			ctrl->value = (32768 - 1057*(t->rf));
		else
			/* left is attenuated, balance shifted right */
			ctrl->value = (32768 + 1057*(t->lf));
		return 0;
	}
	case V4L2_CID_AUDIO_BASS:
	{
		/* Bass/treble 4 bits each */
		int bass=t->bass;
		if(bass >= 0x8)
			bass = ~(bass - 0x8) & 0xf;
		ctrl->value = (bass << 12)+(bass << 8)+(bass << 4)+(bass);
		return 0;
	}
	case V4L2_CID_AUDIO_TREBLE:
	{
		int treble=t->treble;
		if(treble >= 0x8)
			treble = ~(treble - 0x8) & 0xf;
		ctrl->value = (treble << 12)+(treble << 8)+(treble << 4)+(treble);
		return 0;
	}
	}
	return -EINVAL;
}