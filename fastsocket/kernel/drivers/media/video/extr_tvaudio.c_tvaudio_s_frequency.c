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
struct v4l2_frequency {int dummy; } ;
struct CHIPSTATE {int prevmode; int /*<<< orphan*/  wt; scalar_t__ thread; scalar_t__ mode; struct CHIPDESC* desc; } ;
struct CHIPDESC {int /*<<< orphan*/  (* setmode ) (struct CHIPSTATE*,int) ;} ;

/* Variables and functions */
 int V4L2_TUNER_MODE_MONO ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  stub1 (struct CHIPSTATE*,int) ; 
 struct CHIPSTATE* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int tvaudio_s_frequency(struct v4l2_subdev *sd, struct v4l2_frequency *freq)
{
	struct CHIPSTATE *chip = to_state(sd);
	struct CHIPDESC *desc = chip->desc;

	chip->mode = 0; /* automatic */

	/* For chips that provide getmode and setmode, and doesn't
	   automatically follows the stereo carrier, a kthread is
	   created to set the audio standard. In this case, when then
	   the video channel is changed, tvaudio starts on MONO mode.
	   After waiting for 2 seconds, the kernel thread is called,
	   to follow whatever audio standard is pointed by the
	   audio carrier.
	 */
	if (chip->thread) {
		desc->setmode(chip, V4L2_TUNER_MODE_MONO);
		if (chip->prevmode != V4L2_TUNER_MODE_MONO)
			chip->prevmode = -1; /* reset previous mode */
		mod_timer(&chip->wt, jiffies+msecs_to_jiffies(2000));
	}
	return 0;
}