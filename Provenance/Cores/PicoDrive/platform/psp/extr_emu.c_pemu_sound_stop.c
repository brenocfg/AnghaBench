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
 int /*<<< orphan*/  memset32 (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  psp_msleep (int) ; 
 int samples_block ; 
 scalar_t__ samples_done ; 
 int samples_made ; 
 scalar_t__ sceAudioOutput2GetRestSample () ; 
 int /*<<< orphan*/  sceAudio_5C37C0AE () ; 
 int /*<<< orphan*/  sceKernelDelayThread (int) ; 
 int /*<<< orphan*/  sceKernelSignalSema (int /*<<< orphan*/ ,int) ; 
 scalar_t__ sndBuffer ; 
 int /*<<< orphan*/  sound_sem ; 

void pemu_sound_stop(void)
{
	int i;
	if (samples_done == 0)
	{
		// if no data is written between sceAudio_38553111 and sceAudio_5C37C0AE calls,
		// we get a deadlock on next sceAudio_38553111 call
		// so this is yet another workaround:
		memset32((int *)(void *)sndBuffer, 0, samples_block*4/4);
		samples_made = samples_block * 3;
		sceKernelSignalSema(sound_sem, 1);
	}
	sceKernelDelayThread(100*1000);
	samples_made = samples_done = 0;
	for (i = 0; sceAudioOutput2GetRestSample() > 0 && i < 16; i++)
		psp_msleep(100);
	sceAudio_5C37C0AE();
}