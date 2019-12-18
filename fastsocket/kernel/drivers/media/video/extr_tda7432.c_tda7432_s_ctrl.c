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
struct tda7432 {int muted; int volume; int rr; int rf; int lr; int lf; int bass; int treble; } ;

/* Variables and functions */
 int EINVAL ; 
 void* TDA7432_ATTEN_0DB ; 
 int TDA7432_LD_ON ; 
 int /*<<< orphan*/  TDA7432_LF ; 
 int /*<<< orphan*/  TDA7432_LR ; 
 int TDA7432_MUTE ; 
 int /*<<< orphan*/  TDA7432_RF ; 
 int /*<<< orphan*/  TDA7432_RR ; 
 int /*<<< orphan*/  TDA7432_TN ; 
 int /*<<< orphan*/  TDA7432_VL ; 
#define  V4L2_CID_AUDIO_BALANCE 132 
#define  V4L2_CID_AUDIO_BASS 131 
#define  V4L2_CID_AUDIO_MUTE 130 
#define  V4L2_CID_AUDIO_TREBLE 129 
#define  V4L2_CID_AUDIO_VOLUME 128 
 int /*<<< orphan*/  loudness ; 
 int /*<<< orphan*/  maxvol ; 
 int /*<<< orphan*/  tda7432_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 struct tda7432* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int tda7432_s_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
{
	struct tda7432 *t = to_state(sd);

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
		t->muted=ctrl->value;
		break;
	case V4L2_CID_AUDIO_VOLUME:
		if(!maxvol){ /* max +20db */
			t->volume = 0x6f - ((ctrl->value)/630);
		} else {    /* max 0db   */
			t->volume = 0x6f - ((ctrl->value)/829);
		}
		if (loudness)		/* Turn on the loudness bit */
			t->volume |= TDA7432_LD_ON;

		tda7432_write(sd, TDA7432_VL, t->volume);
		return 0;
	case V4L2_CID_AUDIO_BALANCE:
		if (ctrl->value < 32768) {
			/* shifted to left, attenuate right */
			t->rr = (32768 - ctrl->value)/1057;
			t->rf = t->rr;
			t->lr = TDA7432_ATTEN_0DB;
			t->lf = TDA7432_ATTEN_0DB;
		} else if(ctrl->value > 32769) {
			/* shifted to right, attenuate left */
			t->lf = (ctrl->value - 32768)/1057;
			t->lr = t->lf;
			t->rr = TDA7432_ATTEN_0DB;
			t->rf = TDA7432_ATTEN_0DB;
		} else {
			/* centered */
			t->rr = TDA7432_ATTEN_0DB;
			t->rf = TDA7432_ATTEN_0DB;
			t->lf = TDA7432_ATTEN_0DB;
			t->lr = TDA7432_ATTEN_0DB;
		}
		break;
	case V4L2_CID_AUDIO_BASS:
		t->bass = ctrl->value >> 12;
		if(t->bass>= 0x8)
				t->bass = (~t->bass & 0xf) + 0x8 ;

		tda7432_write(sd, TDA7432_TN, 0x10 | (t->bass << 4) | t->treble);
		return 0;
	case V4L2_CID_AUDIO_TREBLE:
		t->treble= ctrl->value >> 12;
		if(t->treble>= 0x8)
				t->treble = (~t->treble & 0xf) + 0x8 ;

		tda7432_write(sd, TDA7432_TN, 0x10 | (t->bass << 4) | t->treble);
		return 0;
	default:
		return -EINVAL;
	}

	/* Used for both mute and balance changes */
	if (t->muted)
	{
		/* Mute & update balance*/
		tda7432_write(sd, TDA7432_LF, t->lf | TDA7432_MUTE);
		tda7432_write(sd, TDA7432_LR, t->lr | TDA7432_MUTE);
		tda7432_write(sd, TDA7432_RF, t->rf | TDA7432_MUTE);
		tda7432_write(sd, TDA7432_RR, t->rr | TDA7432_MUTE);
	} else {
		tda7432_write(sd, TDA7432_LF, t->lf);
		tda7432_write(sd, TDA7432_LR, t->lr);
		tda7432_write(sd, TDA7432_RF, t->rf);
		tda7432_write(sd, TDA7432_RR, t->rr);
	}
	return 0;
}