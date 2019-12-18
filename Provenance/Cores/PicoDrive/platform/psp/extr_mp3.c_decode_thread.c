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
 int /*<<< orphan*/  lprintf (char*,...) ; 
 int* mp3_codec_struct ; 
 scalar_t__* mp3_mix_buffer ; 
 scalar_t__* mp3_src_buffer ; 
 int /*<<< orphan*/  psp_sem_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psp_sem_unlock (int /*<<< orphan*/ ) ; 
 int read_next_frame (size_t) ; 
 int sceAudiocodecDecode (int*,int) ; 
 int /*<<< orphan*/  sceKernelExitDeleteThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceKernelGetThreadCurrentPriority () ; 
 int /*<<< orphan*/  sceKernelGetThreadId () ; 
 int /*<<< orphan*/  thread_busy_sem ; 
 scalar_t__ thread_exit ; 
 int /*<<< orphan*/  thread_job_sem ; 
 size_t working_buf ; 

__attribute__((used)) static int decode_thread(SceSize args, void *argp)
{
	int ret, frame_size;

	lprintf("decode_thread started with id %08x, priority %i\n",
                sceKernelGetThreadId(), sceKernelGetThreadCurrentPriority());

	while (!thread_exit)
	{
		psp_sem_lock(thread_job_sem);
		if (thread_exit) break;

		psp_sem_lock(thread_busy_sem);
		//lprintf("{ job\n");

		frame_size = read_next_frame(working_buf);
		if (frame_size > 0)
		{
			mp3_codec_struct[6] = (unsigned long)mp3_src_buffer[working_buf];
			mp3_codec_struct[8] = (unsigned long)mp3_mix_buffer[working_buf];
			mp3_codec_struct[7] = mp3_codec_struct[10] = frame_size;
			mp3_codec_struct[9] = 1152 * 4;

			ret = sceAudiocodecDecode(mp3_codec_struct, 0x1002);
			if (ret < 0) lprintf("sceAudiocodecDecode failed with %08x\n", ret);
		}

		//lprintf("} job\n");
		psp_sem_unlock(thread_busy_sem);
	}

	lprintf("leaving decode thread\n");
	sceKernelExitDeleteThread(0);
	return 0;
}