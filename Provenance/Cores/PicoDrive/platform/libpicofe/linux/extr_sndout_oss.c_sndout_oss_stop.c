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
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  sndout_oss_can_restart ; 
 int sounddev ; 

void sndout_oss_stop(void)
{
	/* restarting audio on GP2X causes trouble,
	 * not restarting on Caanoo causes trouble */
	if (!sndout_oss_can_restart)
		return;

	if (sounddev < 0)
		return;

	// sync causes trouble on Caanoo..
	//ioctl(sounddev, SOUND_PCM_SYNC, 0);

	close(sounddev);
	sounddev = -1;
}