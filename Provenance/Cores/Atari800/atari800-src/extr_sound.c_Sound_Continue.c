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
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  PLATFORM_SoundContinue () ; 
 scalar_t__ Sound_enabled ; 
 int /*<<< orphan*/  Util_time () ; 
 int /*<<< orphan*/  last_audio_write_time ; 
 scalar_t__ paused ; 

void Sound_Continue(void)
{
	if (Sound_enabled && paused) {
		/* start audio output */
#ifdef SYNCHRONIZED_SOUND
/*		sync_write_pos = sync_read_pos + sync_min_fill;
		avg_fill = sync_min_fill;*/
		last_audio_write_time = Util_time();
#endif /* SYNCHRONIZED_SOUND */
		PLATFORM_SoundContinue();
		paused = FALSE;
	}
}