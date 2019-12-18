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
 scalar_t__ PsndOut ; 
 int /*<<< orphan*/  lprintf (char*,scalar_t__) ; 
 int samples_block ; 
 int samples_done ; 
 int samples_made ; 
 int sceKernelSignalSema (int /*<<< orphan*/ ,int) ; 
 scalar_t__ sndBuffer ; 
 scalar_t__ sndBuffer_endptr ; 
 int /*<<< orphan*/  sound_sem ; 

__attribute__((used)) static void writeSound(int len)
{
	int ret;

	PsndOut += len / 2;
	/*if (PsndOut > sndBuffer_endptr) {
		memcpy32((int *)(void *)sndBuffer, (int *)endptr, (PsndOut - endptr + 1) / 2);
		PsndOut = &sndBuffer[PsndOut - endptr];
		lprintf("mov\n");
	}
	else*/
	if (PsndOut > sndBuffer_endptr) lprintf("snd oflow %i!\n", PsndOut - sndBuffer_endptr);
	if (PsndOut >= sndBuffer_endptr)
		PsndOut = sndBuffer;

	// signal the snd thread
	samples_made += len / 2;
	if (samples_made - samples_done > samples_block*2) {
		// lprintf("signal, %i/%i\n", samples_done, samples_made);
		ret = sceKernelSignalSema(sound_sem, 1);
		//if (ret < 0) lprintf("snd signal ret %08x\n", ret);
	}
}