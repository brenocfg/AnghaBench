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
 scalar_t__ Atari800_FPS_NTSC ; 
 scalar_t__ Atari800_FPS_PAL ; 
 scalar_t__ Atari800_TV_PAL ; 
 int Atari800_nframes ; 
 int Atari800_refresh_rate ; 
 scalar_t__ Atari800_tv_mode ; 
 double Util_time () ; 

__attribute__((used)) static void autoframeskip(double curtime, double lasttime)
{
	static int afs_lastframe = 0, afs_discard = 0;
	static double afs_lasttime = 0.0, afs_sleeptime = 0.0;
	double afs_speedpct, afs_sleeppct, afs_ataritime, afs_realtime;

	if (lasttime - curtime > 0)
		afs_sleeptime += lasttime - curtime;
	if (curtime - afs_lasttime > 0.5) {
		afs_ataritime = ((double) (Atari800_nframes - afs_lastframe)) /
						((double) (Atari800_tv_mode == Atari800_TV_PAL ? Atari800_FPS_PAL : Atari800_FPS_NTSC));
		afs_realtime = curtime - afs_lasttime;
		afs_speedpct = 100.0 * afs_ataritime / afs_realtime;
		afs_sleeppct = 100.0 * afs_sleeptime / afs_realtime;

		if (afs_discard < 3 && (afs_realtime > 2.0 * afs_ataritime)) {
			afs_discard++;
		} else {
			afs_discard = 0;
			if (afs_speedpct < 90.0) {
				if (Atari800_refresh_rate < 4)
					Atari800_refresh_rate++;
			} else {
				if (afs_sleeppct > 20.0 && Atari800_refresh_rate > 1)
					Atari800_refresh_rate--;
			}
		}

		afs_sleeptime = 0.0;
		afs_lastframe = Atari800_nframes;
		afs_lasttime = Util_time();
	}
}