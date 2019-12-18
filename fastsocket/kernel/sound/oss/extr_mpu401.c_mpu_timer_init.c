#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mpu_config {int timer_flag; int version; int revision; } ;
struct TYPE_3__ {int devlink; } ;

/* Variables and functions */
 int TMR_EXTERNAL ; 
 int TMR_INTERNAL ; 
 int TMR_MODE_CLS ; 
 int TMR_MODE_FSK ; 
 int TMR_MODE_MIDI ; 
 struct mpu_config* dev_conf ; 
 int max_timebase ; 
 TYPE_1__ mpu_timer ; 
 int sound_alloc_timerdev () ; 
 TYPE_1__** sound_timer_devs ; 
 int timer_caps ; 
 int timer_initialized ; 
 int timer_mode ; 

__attribute__((used)) static int mpu_timer_init(int midi_dev)
{
	struct mpu_config *devc;
	int n;

	devc = &dev_conf[midi_dev];

	if (timer_initialized)
		return -1;	/* There is already a similar timer */

	timer_initialized = 1;

	mpu_timer.devlink = midi_dev;
	dev_conf[midi_dev].timer_flag = 1;

	n = sound_alloc_timerdev();
	if (n == -1)
		n = 0;
	sound_timer_devs[n] = &mpu_timer;

	if (devc->version < 0x20)	/* Original MPU-401 */
		timer_caps = TMR_INTERNAL | TMR_EXTERNAL | TMR_MODE_FSK | TMR_MODE_MIDI;
	else
	{
		/*
		 * The version number 2.0 is used (at least) by the
		 * MusicQuest cards and the Roland Super-MPU.
		 *
		 * MusicQuest has given a special meaning to the bits of the
		 * revision number. The Super-MPU returns 0.
		 */

		if (devc->revision)
			timer_caps |= TMR_EXTERNAL | TMR_MODE_MIDI;

		if (devc->revision & 0x02)
			timer_caps |= TMR_MODE_CLS;


		if (devc->revision & 0x40)
			max_timebase = 10;	/* Has the 216 and 240 ppqn modes */
	}

	timer_mode = (TMR_INTERNAL | TMR_MODE_MIDI) & timer_caps;
	return n;

}