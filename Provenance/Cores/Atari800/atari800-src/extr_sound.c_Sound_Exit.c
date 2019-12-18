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
 int /*<<< orphan*/  PLATFORM_SoundExit () ; 
 scalar_t__ Sound_enabled ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * process_buffer ; 
 int /*<<< orphan*/ * sync_buffer ; 

void Sound_Exit(void)
{
	if (Sound_enabled) {
		PLATFORM_SoundExit();
		Sound_enabled = FALSE;
#ifndef SOUND_CALLBACK
		free(process_buffer);
		process_buffer = NULL;
#endif /* !SOUND_CALLBACK */
#ifdef SYNCHRONIZED_SOUND
		free(sync_buffer);
		sync_buffer = NULL;
#endif /* SYNCHRONIZED_SOUND */
	}
}