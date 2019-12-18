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
struct wm8775_state {int /*<<< orphan*/  input; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_ctrl {int id; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  R14 ; 
 int /*<<< orphan*/  R15 ; 
 int /*<<< orphan*/  R21 ; 
#define  V4L2_CID_AUDIO_MUTE 128 
 struct v4l2_subdev* to_sd (struct v4l2_ctrl*) ; 
 struct wm8775_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  wm8775_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8775_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = to_sd(ctrl);
	struct wm8775_state *state = to_state(sd);

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
		wm8775_write(sd, R21, 0x0c0);
		wm8775_write(sd, R14, 0x1d4);
		wm8775_write(sd, R15, 0x1d4);
		if (!ctrl->val)
			wm8775_write(sd, R21, 0x100 + state->input);
		return 0;
	}
	return -EINVAL;
}