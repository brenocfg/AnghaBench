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
 int /*<<< orphan*/  PSP_O_RDONLY ; 
 int /*<<< orphan*/  PSP_SEEK_END ; 
 int /*<<< orphan*/  PSP_SEEK_SET ; 
 int /*<<< orphan*/  initialized ; 
 int /*<<< orphan*/  lprintf (char*,...) ; 
 scalar_t__ mp3_buffer_offs ; 
 int /*<<< orphan*/  mp3_codec_struct ; 
 char* mp3_fname ; 
 scalar_t__ mp3_handle ; 
 int mp3_job_started ; 
 scalar_t__ mp3_play_bufsel ; 
 scalar_t__ mp3_samples_ready ; 
 int mp3_src_pos ; 
 scalar_t__ mp3_src_size ; 
 int /*<<< orphan*/  psp_sem_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psp_sem_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceAudiocodecInit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sceIoClose (scalar_t__) ; 
 scalar_t__ sceIoLseek32 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sceIoOpen (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sceKernelDelayThread (int) ; 
 int /*<<< orphan*/  thread_busy_sem ; 
 int /*<<< orphan*/  thread_job_sem ; 
 scalar_t__ working_buf ; 

void mp3_start_play(void *f, int pos)
{
	char *fname = f;

	if (!initialized) return;

	lprintf("mp3_start_play(%s) @ %i\n", fname, pos);
	psp_sem_lock(thread_busy_sem);

	if (mp3_fname != fname || mp3_handle < 0)
	{
		if (mp3_handle >= 0) sceIoClose(mp3_handle);
		mp3_handle = sceIoOpen(fname, PSP_O_RDONLY, 0777);
		if (mp3_handle < 0) {
			lprintf("sceIoOpen(%s) failed\n", fname);
			psp_sem_unlock(thread_busy_sem);
			return;
		}
		mp3_src_size = sceIoLseek32(mp3_handle, 0, PSP_SEEK_END);
		mp3_fname = fname;
	}

	// clear decoder state
	sceAudiocodecInit(mp3_codec_struct, 0x1002);

	// seek..
	mp3_src_pos = (int) (((float)pos / 1023.0f) * (float)mp3_src_size);
	sceIoLseek32(mp3_handle, mp3_src_pos, PSP_SEEK_SET);
	lprintf("seek %i: %i/%i\n", pos, mp3_src_pos, mp3_src_size);

	mp3_job_started = 1;
	mp3_samples_ready = mp3_buffer_offs = mp3_play_bufsel = 0;
	working_buf = 0;

	/* send a request to decode first frame */
	psp_sem_unlock(thread_busy_sem);
	psp_sem_unlock(thread_job_sem);
	sceKernelDelayThread(1); // reschedule
}