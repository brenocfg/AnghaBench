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
 int /*<<< orphan*/  Sound_enabled ; 
 int /*<<< orphan*/  UpdateSyncBuffer () ; 
 int /*<<< orphan*/  WriteOut () ; 
 scalar_t__ paused ; 

void Sound_Update(void)
{
	if (!Sound_enabled || paused)
		return;
#ifdef SYNCHRONIZED_SOUND
	UpdateSyncBuffer();
#endif /* SYNCHRONIZED_SOUND */
#ifndef SOUND_CALLBACK
	WriteOut();
#endif /* !SOUND_CALLBACK */
}