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
 int PsndRate ; 
 void mix_16h_to_32 (int*,short*,int) ; 
 void mix_16h_to_32_s1 (int*,short*,int) ; 
 void mix_16h_to_32_s2 (int*,short*,int) ; 
 int mp3_buffer_offs ; 
 scalar_t__ mp3_handle ; 
 int mp3_job_started ; 
 short** mp3_mix_buffer ; 
 size_t mp3_play_bufsel ; 
 int mp3_samples_ready ; 
 scalar_t__ mp3_src_pos ; 
 scalar_t__ mp3_src_size ; 
 int /*<<< orphan*/  psp_sem_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psp_sem_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceKernelDelayThread (int) ; 
 int /*<<< orphan*/  thread_busy_sem ; 
 int /*<<< orphan*/  thread_job_sem ; 
 int working_buf ; 

void mp3_update(int *buffer, int length, int stereo)
{
	int length_mp3;

	// playback was started, track not ended
	if (mp3_handle < 0 || mp3_src_pos >= mp3_src_size) return;

	length_mp3 = length;
	if (PsndRate == 22050) length_mp3 <<= 1;	// mp3s are locked to 44100Hz stereo
	else if (PsndRate == 11025) length_mp3 <<= 2;	// so make length 44100ish

	/* do we have to wait? */
	if (mp3_job_started && mp3_samples_ready < length_mp3)
	{
		psp_sem_lock(thread_busy_sem);
		psp_sem_unlock(thread_busy_sem);
		mp3_job_started = 0;
		mp3_samples_ready += 1152;
	}

	/* mix mp3 data, only stereo */
	if (mp3_samples_ready >= length_mp3)
	{
		int shr = 0;
		void (*mix_samples)(int *dest_buf, short *mp3_buf, int count) = mix_16h_to_32;
		if (PsndRate == 22050) { mix_samples = mix_16h_to_32_s1; shr = 1; }
		else if (PsndRate == 11025) { mix_samples = mix_16h_to_32_s2; shr = 2; }

		if (1152 - mp3_buffer_offs >= length_mp3) {
			mix_samples(buffer, mp3_mix_buffer[mp3_play_bufsel] + mp3_buffer_offs*2, length<<1);

			mp3_buffer_offs += length_mp3;
		} else {
			// collect samples from both buffers..
			int left = 1152 - mp3_buffer_offs;
			if (mp3_play_bufsel == 0)
			{
				mix_samples(buffer, mp3_mix_buffer[0] + mp3_buffer_offs*2, length<<1);
				mp3_buffer_offs = length_mp3 - left;
				mp3_play_bufsel = 1;
			} else {
				mix_samples(buffer, mp3_mix_buffer[1] + mp3_buffer_offs*2, (left>>shr)<<1);
				mp3_buffer_offs = length_mp3 - left;
				mix_samples(buffer + ((left>>shr)<<1),
					mp3_mix_buffer[0], (mp3_buffer_offs>>shr)<<1);
				mp3_play_bufsel = 0;
			}
		}
		mp3_samples_ready -= length_mp3;
	}

	// ask to decode more if we already can
	if (!mp3_job_started)
	{
		mp3_job_started = 1;
		working_buf ^= 1;

		/* next job.. */
		psp_sem_lock(thread_busy_sem);   // just in case
		psp_sem_unlock(thread_busy_sem);
		psp_sem_unlock(thread_job_sem);
		sceKernelDelayThread(1);
	}
}