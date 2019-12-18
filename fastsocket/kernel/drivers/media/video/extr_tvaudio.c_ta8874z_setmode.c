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
struct CHIPSTATE {struct v4l2_subdev sd; } ;
typedef  int /*<<< orphan*/  audiocmd ;

/* Variables and functions */
#define  V4L2_TUNER_MODE_LANG1 131 
#define  V4L2_TUNER_MODE_LANG2 130 
#define  V4L2_TUNER_MODE_MONO 129 
#define  V4L2_TUNER_MODE_STEREO 128 
 int /*<<< orphan*/  chip_cmd (struct CHIPSTATE*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  ta8874z_main ; 
 int /*<<< orphan*/  ta8874z_mono ; 
 int /*<<< orphan*/  ta8874z_stereo ; 
 int /*<<< orphan*/  ta8874z_sub ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int) ; 

__attribute__((used)) static void ta8874z_setmode(struct CHIPSTATE *chip, int mode)
{
	struct v4l2_subdev *sd = &chip->sd;
	int update = 1;
	audiocmd *t = NULL;

	v4l2_dbg(1, debug, sd, "ta8874z_setmode(): mode: 0x%02x\n", mode);

	switch(mode){
	case V4L2_TUNER_MODE_MONO:
		t = &ta8874z_mono;
		break;
	case V4L2_TUNER_MODE_STEREO:
		t = &ta8874z_stereo;
		break;
	case V4L2_TUNER_MODE_LANG1:
		t = &ta8874z_main;
		break;
	case V4L2_TUNER_MODE_LANG2:
		t = &ta8874z_sub;
		break;
	default:
		update = 0;
	}

	if(update)
		chip_cmd(chip, "TA8874Z", t);
}