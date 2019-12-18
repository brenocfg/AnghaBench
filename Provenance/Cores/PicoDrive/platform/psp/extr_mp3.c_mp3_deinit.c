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
 scalar_t__ initialized ; 
 int /*<<< orphan*/  lprintf (char*,scalar_t__) ; 
 int /*<<< orphan*/  mp3_codec_struct ; 
 int /*<<< orphan*/ * mp3_fname ; 
 int mp3_handle ; 
 int /*<<< orphan*/  psp_sem_lock (int) ; 
 int /*<<< orphan*/  psp_sem_unlock (int) ; 
 int /*<<< orphan*/  sceAudiocodecReleaseEDRAM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceIoClose (int) ; 
 int /*<<< orphan*/  sceKernelDelayThread (int) ; 
 int /*<<< orphan*/  sceKernelDeleteSema (int) ; 
 int /*<<< orphan*/  sceKernelSignalSema (int,int) ; 
 int thread_busy_sem ; 
 int thread_exit ; 
 int thread_job_sem ; 

void mp3_deinit(void)
{
	lprintf("mp3_deinit, initialized=%i\n", initialized);

	if (!initialized) return;
	thread_exit = 1;
	psp_sem_lock(thread_busy_sem);
	psp_sem_unlock(thread_busy_sem);

	sceKernelSignalSema(thread_job_sem, 1);
	sceKernelDelayThread(100*1000);

	if (mp3_handle >= 0) sceIoClose(mp3_handle);
	mp3_handle = -1;
	mp3_fname = NULL;

	sceKernelDeleteSema(thread_busy_sem);
	thread_busy_sem = -1;
	sceKernelDeleteSema(thread_job_sem);
	thread_job_sem = -1;
	sceAudiocodecReleaseEDRAM(mp3_codec_struct);
	initialized = 0;
}