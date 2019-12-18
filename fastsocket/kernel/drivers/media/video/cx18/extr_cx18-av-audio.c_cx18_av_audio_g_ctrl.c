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
struct v4l2_control {int id; int /*<<< orphan*/  value; } ;
struct cx18 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_AUDIO_BALANCE 132 
#define  V4L2_CID_AUDIO_BASS 131 
#define  V4L2_CID_AUDIO_MUTE 130 
#define  V4L2_CID_AUDIO_TREBLE 129 
#define  V4L2_CID_AUDIO_VOLUME 128 
 int /*<<< orphan*/  get_balance (struct cx18*) ; 
 int /*<<< orphan*/  get_bass (struct cx18*) ; 
 int /*<<< orphan*/  get_mute (struct cx18*) ; 
 int /*<<< orphan*/  get_treble (struct cx18*) ; 
 int /*<<< orphan*/  get_volume (struct cx18*) ; 

int cx18_av_audio_g_ctrl(struct cx18 *cx, struct v4l2_control *ctrl)
{
	switch (ctrl->id) {
	case V4L2_CID_AUDIO_VOLUME:
		ctrl->value = get_volume(cx);
		break;
	case V4L2_CID_AUDIO_BASS:
		ctrl->value = get_bass(cx);
		break;
	case V4L2_CID_AUDIO_TREBLE:
		ctrl->value = get_treble(cx);
		break;
	case V4L2_CID_AUDIO_BALANCE:
		ctrl->value = get_balance(cx);
		break;
	case V4L2_CID_AUDIO_MUTE:
		ctrl->value = get_mute(cx);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}