#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ buffer_size; scalar_t__ period_size; struct emu10k1x_pcm* private_data; } ;
struct emu10k1x_pcm {int /*<<< orphan*/  running; TYPE_1__* voice; } ;
struct emu10k1x {int dummy; } ;
typedef  scalar_t__ snd_pcm_uframes_t ;
struct TYPE_2__ {int number; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLAYBACK_LIST_PTR ; 
 int /*<<< orphan*/  PLAYBACK_POINTER ; 
 scalar_t__ bytes_to_frames (struct snd_pcm_runtime*,scalar_t__) ; 
 scalar_t__ frames_to_bytes (struct snd_pcm_runtime*,scalar_t__) ; 
 scalar_t__ snd_emu10k1x_ptr_read (struct emu10k1x*,int /*<<< orphan*/ ,int) ; 
 struct emu10k1x* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t
snd_emu10k1x_pcm_pointer(struct snd_pcm_substream *substream)
{
	struct emu10k1x *emu = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct emu10k1x_pcm *epcm = runtime->private_data;
	int channel = epcm->voice->number;
	snd_pcm_uframes_t ptr = 0, ptr1 = 0, ptr2= 0,ptr3 = 0,ptr4 = 0;

	if (!epcm->running)
		return 0;

	ptr3 = snd_emu10k1x_ptr_read(emu, PLAYBACK_LIST_PTR, channel);
	ptr1 = snd_emu10k1x_ptr_read(emu, PLAYBACK_POINTER, channel);
	ptr4 = snd_emu10k1x_ptr_read(emu, PLAYBACK_LIST_PTR, channel);

	if(ptr4 == 0 && ptr1 == frames_to_bytes(runtime, runtime->buffer_size))
		return 0;
	
	if (ptr3 != ptr4) 
		ptr1 = snd_emu10k1x_ptr_read(emu, PLAYBACK_POINTER, channel);
	ptr2 = bytes_to_frames(runtime, ptr1);
	ptr2 += (ptr4 >> 3) * runtime->period_size;
	ptr = ptr2;

	if (ptr >= runtime->buffer_size)
		ptr -= runtime->buffer_size;

	return ptr;
}