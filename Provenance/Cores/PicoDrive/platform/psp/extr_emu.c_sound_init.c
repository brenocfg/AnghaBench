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
typedef  int SceUID ;

/* Variables and functions */
 int /*<<< orphan*/  SOUND_BLOCK_SIZE_NTSC ; 
 int /*<<< orphan*/  lprintf (char*,int) ; 
 int /*<<< orphan*/  samples_block ; 
 scalar_t__ samples_done ; 
 scalar_t__ samples_made ; 
 scalar_t__ sceKernelCreateSema (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int sceKernelCreateThread (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sceKernelStartThread (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sound_sem ; 
 int /*<<< orphan*/  sound_thread ; 
 scalar_t__ sound_thread_exit ; 

__attribute__((used)) static void sound_init(void)
{
	SceUID thid;
	int ret;

	sound_sem = sceKernelCreateSema("sndsem", 0, 0, 1, NULL);
	if (sound_sem < 0) lprintf("sceKernelCreateSema() failed: %i\n", sound_sem);

	samples_made = samples_done = 0;
	samples_block = SOUND_BLOCK_SIZE_NTSC; // make sure it goes to sema
	sound_thread_exit = 0;
	thid = sceKernelCreateThread("sndthread", sound_thread, 0x12, 0x10000, 0, NULL);
	if (thid >= 0)
	{
		ret = sceKernelStartThread(thid, 0, 0);
		if (ret < 0) lprintf("sound_init: sceKernelStartThread returned %08x\n", ret);
	}
	else
		lprintf("sceKernelCreateThread failed: %i\n", thid);
}