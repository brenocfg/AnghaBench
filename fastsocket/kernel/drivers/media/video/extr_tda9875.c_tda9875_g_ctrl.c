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
struct tda9875 {int /*<<< orphan*/  treble; int /*<<< orphan*/  bass; int /*<<< orphan*/  rvol; int /*<<< orphan*/  lvol; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_AUDIO_BALANCE 131 
#define  V4L2_CID_AUDIO_BASS 130 
#define  V4L2_CID_AUDIO_TREBLE 129 
#define  V4L2_CID_AUDIO_VOLUME 128 
 void* max (int,int) ; 
 int min (int,int) ; 
 struct tda9875* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int tda9875_g_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
{
	struct tda9875 *t = to_state(sd);

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_VOLUME:
	{
		int left = (t->lvol+84)*606;
		int right = (t->rvol+84)*606;

		ctrl->value=max(left,right);
		return 0;
	}
	case V4L2_CID_AUDIO_BALANCE:
	{
		int left = (t->lvol+84)*606;
		int right = (t->rvol+84)*606;
		int volume = max(left,right);
		int balance = (32768*min(left,right))/
			      (volume ? volume : 1);
		ctrl->value=(left<right)?
			(65535-balance) : balance;
		return 0;
	}
	case V4L2_CID_AUDIO_BASS:
		ctrl->value = (t->bass+12)*2427;    /* min -12 max +15 */
		return 0;
	case V4L2_CID_AUDIO_TREBLE:
		ctrl->value = (t->treble+12)*2730;/* min -12 max +12 */
		return 0;
	}
	return -EINVAL;
}