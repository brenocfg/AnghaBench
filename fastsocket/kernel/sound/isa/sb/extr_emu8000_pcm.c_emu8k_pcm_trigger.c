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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_emu8k_pcm {int voices; int running; } ;
struct TYPE_2__ {struct snd_emu8k_pcm* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  start_voice (struct snd_emu8k_pcm*,int) ; 
 int /*<<< orphan*/  stop_voice (struct snd_emu8k_pcm*,int) ; 

__attribute__((used)) static int emu8k_pcm_trigger(struct snd_pcm_substream *subs, int cmd)
{
	struct snd_emu8k_pcm *rec = subs->runtime->private_data;
	int ch;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		for (ch = 0; ch < rec->voices; ch++)
			start_voice(rec, ch);
		rec->running = 1;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		rec->running = 0;
		for (ch = 0; ch < rec->voices; ch++)
			stop_voice(rec, ch);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}