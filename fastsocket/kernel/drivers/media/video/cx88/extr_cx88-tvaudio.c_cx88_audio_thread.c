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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  t ;
struct v4l2_tuner {int rxsubchans; } ;
struct cx88_core {int tvaudio; int /*<<< orphan*/  audiomode_current; int /*<<< orphan*/  audiomode_manual; int /*<<< orphan*/  use_nicam; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNSET ; 
 int /*<<< orphan*/  V4L2_TUNER_MODE_MONO ; 
 int /*<<< orphan*/  V4L2_TUNER_MODE_STEREO ; 
 int V4L2_TUNER_SUB_STEREO ; 
#define  WW_BG 138 
#define  WW_BTSC 137 
#define  WW_DK 136 
#define  WW_EIAJ 135 
#define  WW_FM 134 
#define  WW_I 133 
#define  WW_I2SADC 132 
#define  WW_I2SPT 131 
#define  WW_L 130 
#define  WW_M 129 
#define  WW_NONE 128 
 int /*<<< orphan*/  cx88_get_stereo (struct cx88_core*,struct v4l2_tuner*) ; 
 int /*<<< orphan*/  cx88_set_stereo (struct cx88_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  memset (struct v4l2_tuner*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int /*<<< orphan*/  try_to_freeze () ; 

int cx88_audio_thread(void *data)
{
	struct cx88_core *core = data;
	struct v4l2_tuner t;
	u32 mode = 0;

	dprintk("cx88: tvaudio thread started\n");
	set_freezable();
	for (;;) {
		msleep_interruptible(1000);
		if (kthread_should_stop())
			break;
		try_to_freeze();

		switch (core->tvaudio) {
		case WW_BG:
		case WW_DK:
		case WW_M:
		case WW_I:
		case WW_L:
			if (core->use_nicam)
				goto hw_autodetect;

			/* just monitor the audio status for now ... */
			memset(&t, 0, sizeof(t));
			cx88_get_stereo(core, &t);

			if (UNSET != core->audiomode_manual)
				/* manually set, don't do anything. */
				continue;

			/* monitor signal and set stereo if available */
			if (t.rxsubchans & V4L2_TUNER_SUB_STEREO)
				mode = V4L2_TUNER_MODE_STEREO;
			else
				mode = V4L2_TUNER_MODE_MONO;
			if (mode == core->audiomode_current)
				continue;
			/* automatically switch to best available mode */
			cx88_set_stereo(core, mode, 0);
			break;
		case WW_NONE:
		case WW_BTSC:
		case WW_EIAJ:
		case WW_I2SPT:
		case WW_FM:
		case WW_I2SADC:
hw_autodetect:
			/* stereo autodetection is supported by hardware so
			   we don't need to do it manually. Do nothing. */
			break;
		}
	}

	dprintk("cx88: tvaudio thread exiting\n");
	return 0;
}