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
 int /*<<< orphan*/  MFP_IRQ_off ; 
 int /*<<< orphan*/  Supexec (int /*<<< orphan*/ ) ; 
 scalar_t__ sound_enabled ; 

void Sound_Pause(void)
{
#ifdef SOUND
	if (sound_enabled)
		Supexec(MFP_IRQ_off);
#endif
}