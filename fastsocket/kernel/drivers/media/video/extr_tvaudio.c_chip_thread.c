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
struct CHIPSTATE {scalar_t__ mode; int prevmode; int /*<<< orphan*/  wt; scalar_t__ radio; struct v4l2_subdev sd; struct CHIPDESC* desc; } ;
struct CHIPDESC {int (* getmode ) (struct CHIPSTATE*) ;int /*<<< orphan*/  (* setmode ) (struct CHIPSTATE*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int V4L2_TUNER_MODE_LANG1 ; 
 int V4L2_TUNER_MODE_LANG1_LANG2 ; 
 int V4L2_TUNER_MODE_LANG2 ; 
 int V4L2_TUNER_MODE_MONO ; 
 int V4L2_TUNER_MODE_STEREO ; 
 int /*<<< orphan*/  debug ; 
 scalar_t__ jiffies ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int stub1 (struct CHIPSTATE*) ; 
 int /*<<< orphan*/  stub2 (struct CHIPSTATE*,int) ; 
 int /*<<< orphan*/  stub3 (struct CHIPSTATE*,int) ; 
 int /*<<< orphan*/  stub4 (struct CHIPSTATE*,int) ; 
 int /*<<< orphan*/  stub5 (struct CHIPSTATE*,int) ; 
 int /*<<< orphan*/  stub6 (struct CHIPSTATE*,int) ; 
 int /*<<< orphan*/  try_to_freeze () ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*) ; 

__attribute__((used)) static int chip_thread(void *data)
{
	struct CHIPSTATE *chip = data;
	struct CHIPDESC  *desc = chip->desc;
	struct v4l2_subdev *sd = &chip->sd;
	int mode;

	v4l2_dbg(1, debug, sd, "thread started\n");
	set_freezable();
	for (;;) {
		set_current_state(TASK_INTERRUPTIBLE);
		if (!kthread_should_stop())
			schedule();
		set_current_state(TASK_RUNNING);
		try_to_freeze();
		if (kthread_should_stop())
			break;
		v4l2_dbg(1, debug, sd, "thread wakeup\n");

		/* don't do anything for radio or if mode != auto */
		if (chip->radio || chip->mode != 0)
			continue;

		/* have a look what's going on */
		mode = desc->getmode(chip);
		if (mode == chip->prevmode)
			continue;

		/* chip detected a new audio mode - set it */
		v4l2_dbg(1, debug, sd, "thread checkmode\n");

		chip->prevmode = mode;

		if (mode & V4L2_TUNER_MODE_STEREO)
			desc->setmode(chip, V4L2_TUNER_MODE_STEREO);
		if (mode & V4L2_TUNER_MODE_LANG1_LANG2)
			desc->setmode(chip, V4L2_TUNER_MODE_STEREO);
		else if (mode & V4L2_TUNER_MODE_LANG1)
			desc->setmode(chip, V4L2_TUNER_MODE_LANG1);
		else if (mode & V4L2_TUNER_MODE_LANG2)
			desc->setmode(chip, V4L2_TUNER_MODE_LANG2);
		else
			desc->setmode(chip, V4L2_TUNER_MODE_MONO);

		/* schedule next check */
		mod_timer(&chip->wt, jiffies+msecs_to_jiffies(2000));
	}

	v4l2_dbg(1, debug, sd, "thread exiting\n");
	return 0;
}