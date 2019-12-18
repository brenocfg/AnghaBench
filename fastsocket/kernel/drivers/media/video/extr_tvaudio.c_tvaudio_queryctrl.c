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
struct v4l2_queryctrl {int id; } ;
struct CHIPSTATE {struct CHIPDESC* desc; } ;
struct CHIPDESC {int flags; } ;

/* Variables and functions */
 int CHIP_HAS_BASSTREBLE ; 
 int CHIP_HAS_INPUTSEL ; 
 int CHIP_HAS_VOLUME ; 
 int EINVAL ; 
#define  V4L2_CID_AUDIO_BALANCE 132 
#define  V4L2_CID_AUDIO_BASS 131 
#define  V4L2_CID_AUDIO_MUTE 130 
#define  V4L2_CID_AUDIO_TREBLE 129 
#define  V4L2_CID_AUDIO_VOLUME 128 
 struct CHIPSTATE* to_state (struct v4l2_subdev*) ; 
 int v4l2_ctrl_query_fill (struct v4l2_queryctrl*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int tvaudio_queryctrl(struct v4l2_subdev *sd, struct v4l2_queryctrl *qc)
{
	struct CHIPSTATE *chip = to_state(sd);
	struct CHIPDESC *desc = chip->desc;

	switch (qc->id) {
	case V4L2_CID_AUDIO_MUTE:
		if (desc->flags & CHIP_HAS_INPUTSEL)
			return v4l2_ctrl_query_fill(qc, 0, 1, 1, 0);
		break;
	case V4L2_CID_AUDIO_VOLUME:
		if (desc->flags & CHIP_HAS_VOLUME)
			return v4l2_ctrl_query_fill(qc, 0, 65535, 65535 / 100, 58880);
		break;
	case V4L2_CID_AUDIO_BALANCE:
		if (desc->flags & CHIP_HAS_VOLUME)
			return v4l2_ctrl_query_fill(qc, 0, 65535, 65535 / 100, 32768);
		break;
	case V4L2_CID_AUDIO_BASS:
	case V4L2_CID_AUDIO_TREBLE:
		if (desc->flags & CHIP_HAS_BASSTREBLE)
			return v4l2_ctrl_query_fill(qc, 0, 65535, 65535 / 100, 32768);
		break;
	default:
		break;
	}
	return -EINVAL;
}