#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct wm8739_state {TYPE_3__* mute; TYPE_2__* volume; TYPE_1__* balance; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_ctrl {int id; } ;
struct TYPE_6__ {scalar_t__ val; } ;
struct TYPE_5__ {int val; } ;
struct TYPE_4__ {scalar_t__ val; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R1 ; 
#define  V4L2_CID_AUDIO_VOLUME 128 
 int min (scalar_t__,int) ; 
 struct v4l2_subdev* to_sd (struct v4l2_ctrl*) ; 
 struct wm8739_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  wm8739_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8739_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = to_sd(ctrl);
	struct wm8739_state *state = to_state(sd);
	unsigned int work_l, work_r;
	u8 vol_l;	/* +12dB to -34.5dB 1.5dB step (5bit) def:0dB */
	u8 vol_r;	/* +12dB to -34.5dB 1.5dB step (5bit) def:0dB */
	u16 mute;

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_VOLUME:
		break;

	default:
		return -EINVAL;
	}

	/* normalize ( 65535 to 0 -> 31 to 0 (12dB to -34.5dB) ) */
	work_l = (min(65536 - state->balance->val, 32768) * state->volume->val) / 32768;
	work_r = (min(state->balance->val, 32768) * state->volume->val) / 32768;

	vol_l = (long)work_l * 31 / 65535;
	vol_r = (long)work_r * 31 / 65535;

	/* set audio volume etc. */
	mute = state->mute->val ? 0x80 : 0;

	/* Volume setting: bits 0-4, 0x1f = 12 dB, 0x00 = -34.5 dB
	 * Default setting: 0x17 = 0 dB
	 */
	wm8739_write(sd, R0, (vol_l & 0x1f) | mute);
	wm8739_write(sd, R1, (vol_r & 0x1f) | mute);
	return 0;
}