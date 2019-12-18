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
struct snd_pcm_runtime {struct snd_ca0106_pcm* private_data; } ;
struct snd_ca0106_pcm {size_t channel_id; } ;
struct snd_ca0106 {TYPE_1__* capture_channels; } ;
struct TYPE_2__ {scalar_t__ use; } ;

/* Variables and functions */
 struct snd_ca0106* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_ca0106_pcm_close_capture(struct snd_pcm_substream *substream)
{
	struct snd_ca0106 *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
        struct snd_ca0106_pcm *epcm = runtime->private_data;
	chip->capture_channels[epcm->channel_id].use = 0;
	/* FIXME: maybe zero others */
	return 0;
}