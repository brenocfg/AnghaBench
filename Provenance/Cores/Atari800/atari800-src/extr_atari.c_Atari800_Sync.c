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

/* Variables and functions */
 double Atari800_FPS_NTSC ; 
 double Atari800_FPS_PAL ; 
 scalar_t__ Atari800_TV_PAL ; 
 scalar_t__ Atari800_auto_frameskip ; 
 double Atari800_refresh_rate ; 
 scalar_t__ Atari800_tv_mode ; 
 double Sound_AdjustSpeed () ; 
 int /*<<< orphan*/  UI_is_active ; 
 int /*<<< orphan*/  Util_sleep (double) ; 
 double Util_time () ; 
 int /*<<< orphan*/  autoframeskip (double,double) ; 

void Atari800_Sync(void)
{
	static double lasttime = 0;
	double deltatime = 1.0 / ((Atari800_tv_mode == Atari800_TV_PAL) ? Atari800_FPS_PAL : Atari800_FPS_NTSC);
	double curtime;

#ifdef SYNCHRONIZED_SOUND
	deltatime *= Sound_AdjustSpeed();
#endif
#ifdef ALTERNATE_SYNC_WITH_HOST
	if (! UI_is_active)
		deltatime *= Atari800_refresh_rate;
#endif
	lasttime += deltatime;
	curtime = Util_time();
	if (Atari800_auto_frameskip)
		autoframeskip(curtime, lasttime);
	Util_sleep(lasttime - curtime);
	curtime = Util_time();

	if ((lasttime + deltatime) < curtime)
		lasttime = curtime;
}