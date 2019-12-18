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
typedef  int /*<<< orphan*/  SceSize ;

/* Variables and functions */
 int /*<<< orphan*/  PSP_AUDIO_VOLUME_MAX ; 
 int /*<<< orphan*/  lprintf (char*,...) ; 
 int samples_block ; 
 int samples_done ; 
 int samples_made ; 
 int sceAudio_E0727056 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sceKernelExitDeleteThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceKernelGetThreadCurrentPriority () ; 
 int sceKernelWaitSema (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sndBuffer ; 
 scalar_t__ sndBuffer_endptr ; 
 scalar_t__ snd_playptr ; 
 int /*<<< orphan*/  sound_sem ; 
 int /*<<< orphan*/  sound_thread_exit ; 

__attribute__((used)) static int sound_thread(SceSize args, void *argp)
{
	int ret = 0;

	lprintf("sthr: started, priority %i\n", sceKernelGetThreadCurrentPriority());

	while (!sound_thread_exit)
	{
		if (samples_made - samples_done < samples_block) {
			// wait for data (use at least 2 blocks)
			//lprintf("sthr: wait... (%i)\n", samples_made - samples_done);
			while (samples_made - samples_done <= samples_block*2 && !sound_thread_exit)
				ret = sceKernelWaitSema(sound_sem, 1, 0);
			if (ret < 0) lprintf("sthr: sceKernelWaitSema: %i\n", ret);
			continue;
		}

		// lprintf("sthr: got data: %i\n", samples_made - samples_done);

		ret = sceAudio_E0727056(PSP_AUDIO_VOLUME_MAX, snd_playptr);

		samples_done += samples_block;
		snd_playptr  += samples_block;
		if (snd_playptr >= sndBuffer_endptr)
			snd_playptr = sndBuffer;
		// 1.5 kernel returns 0, newer ones return # of samples queued
		if (ret < 0)
			lprintf("sthr: sceAudio_E0727056: %08x; pos %i/%i\n", ret, samples_done, samples_made);

		// shouln't happen, but just in case
		if (samples_made - samples_done >= samples_block*3) {
			//lprintf("sthr: block skip (%i)\n", samples_made - samples_done);
			samples_done += samples_block; // skip
			snd_playptr  += samples_block;
		}

	}

	lprintf("sthr: exit\n");
	sceKernelExitDeleteThread(0);
	return 0;
}