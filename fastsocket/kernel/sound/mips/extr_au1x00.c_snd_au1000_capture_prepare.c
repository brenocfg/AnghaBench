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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; TYPE_1__* pcm; } ;
struct snd_pcm_runtime {int channels; int /*<<< orphan*/  rate; } ;
struct snd_au1000 {int /*<<< orphan*/  ac97; } ;
struct TYPE_2__ {struct snd_au1000* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_PCM_LR_ADC_RATE ; 
 int AC97_SLOT_3 ; 
 int AC97_SLOT_4 ; 
 int /*<<< orphan*/  au1000_set_ac97_recv_slots (struct snd_au1000*,int) ; 
 int /*<<< orphan*/  snd_ac97_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
snd_au1000_capture_prepare(struct snd_pcm_substream *substream)
{
	struct snd_au1000 *au1000 = substream->pcm->private_data;
	struct snd_pcm_runtime *runtime = substream->runtime;

	if (runtime->channels == 1)
		au1000_set_ac97_recv_slots(au1000, AC97_SLOT_4);
	else
		au1000_set_ac97_recv_slots(au1000, AC97_SLOT_3 | AC97_SLOT_4);
	snd_ac97_set_rate(au1000->ac97, AC97_PCM_LR_ADC_RATE, runtime->rate);
	return 0;
}