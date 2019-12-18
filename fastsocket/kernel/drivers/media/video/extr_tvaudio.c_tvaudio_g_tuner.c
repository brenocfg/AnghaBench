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
struct v4l2_tuner {int rxsubchans; int capability; int /*<<< orphan*/  audmode; } ;
struct v4l2_subdev {int dummy; } ;
struct CHIPSTATE {int /*<<< orphan*/  audmode; scalar_t__ radio; struct CHIPDESC* desc; } ;
struct CHIPDESC {int (* getmode ) (struct CHIPSTATE*) ;} ;

/* Variables and functions */
 int V4L2_TUNER_CAP_LANG1 ; 
 int V4L2_TUNER_CAP_LANG2 ; 
 int V4L2_TUNER_CAP_STEREO ; 
 int V4L2_TUNER_MODE_LANG1 ; 
 int V4L2_TUNER_MODE_MONO ; 
 int V4L2_TUNER_MODE_STEREO ; 
 int V4L2_TUNER_SUB_LANG1 ; 
 int V4L2_TUNER_SUB_LANG2 ; 
 int V4L2_TUNER_SUB_MONO ; 
 int V4L2_TUNER_SUB_STEREO ; 
 int stub1 (struct CHIPSTATE*) ; 
 struct CHIPSTATE* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int tvaudio_g_tuner(struct v4l2_subdev *sd, struct v4l2_tuner *vt)
{
	struct CHIPSTATE *chip = to_state(sd);
	struct CHIPDESC *desc = chip->desc;
	int mode = V4L2_TUNER_MODE_MONO;

	if (!desc->getmode)
		return 0;
	if (chip->radio)
		return 0;

	vt->audmode = chip->audmode;
	vt->rxsubchans = 0;
	vt->capability = V4L2_TUNER_CAP_STEREO |
		V4L2_TUNER_CAP_LANG1 | V4L2_TUNER_CAP_LANG2;

	mode = desc->getmode(chip);

	if (mode & V4L2_TUNER_MODE_MONO)
		vt->rxsubchans |= V4L2_TUNER_SUB_MONO;
	if (mode & V4L2_TUNER_MODE_STEREO)
		vt->rxsubchans |= V4L2_TUNER_SUB_STEREO;
	/* Note: for SAP it should be mono/lang2 or stereo/lang2.
	   When this module is converted fully to v4l2, then this
	   should change for those chips that can detect SAP. */
	if (mode & V4L2_TUNER_MODE_LANG1)
		vt->rxsubchans = V4L2_TUNER_SUB_LANG1 |
			V4L2_TUNER_SUB_LANG2;
	return 0;
}