#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_2__* pcm; } ;
struct snd_emu10k1 {size_t p16v_device_offset; TYPE_1__* p16v_voices; } ;
struct TYPE_4__ {size_t device; } ;
struct TYPE_3__ {scalar_t__ use; } ;

/* Variables and functions */
 struct snd_emu10k1* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_p16v_pcm_close_playback(struct snd_pcm_substream *substream)
{
	struct snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	//struct snd_pcm_runtime *runtime = substream->runtime;
	//struct snd_emu10k1_pcm *epcm = runtime->private_data;
	emu->p16v_voices[substream->pcm->device - emu->p16v_device_offset].use = 0;
	/* FIXME: maybe zero others */
	return 0;
}