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
struct v4l2_tuner {int audmode; } ;
struct v4l2_subdev {int dummy; } ;
struct CHIPSTATE {int audmode; int mode; scalar_t__ watch_stereo; scalar_t__ radio; struct CHIPDESC* desc; } ;
struct CHIPDESC {int /*<<< orphan*/  (* setmode ) (struct CHIPSTATE*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_TUNER_MODE_LANG1 132 
#define  V4L2_TUNER_MODE_LANG1_LANG2 131 
#define  V4L2_TUNER_MODE_LANG2 130 
#define  V4L2_TUNER_MODE_MONO 129 
#define  V4L2_TUNER_MODE_STEREO 128 
 int /*<<< orphan*/  stub1 (struct CHIPSTATE*,int) ; 
 struct CHIPSTATE* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int tvaudio_s_tuner(struct v4l2_subdev *sd, struct v4l2_tuner *vt)
{
	struct CHIPSTATE *chip = to_state(sd);
	struct CHIPDESC *desc = chip->desc;
	int mode = 0;

	if (!desc->setmode)
		return 0;
	if (chip->radio)
		return 0;

	switch (vt->audmode) {
	case V4L2_TUNER_MODE_MONO:
	case V4L2_TUNER_MODE_STEREO:
	case V4L2_TUNER_MODE_LANG1:
	case V4L2_TUNER_MODE_LANG2:
		mode = vt->audmode;
		break;
	case V4L2_TUNER_MODE_LANG1_LANG2:
		mode = V4L2_TUNER_MODE_STEREO;
		break;
	default:
		return -EINVAL;
	}
	chip->audmode = vt->audmode;

	if (mode) {
		chip->watch_stereo = 0;
		/* del_timer(&chip->wt); */
		chip->mode = mode;
		desc->setmode(chip, mode);
	}
	return 0;
}