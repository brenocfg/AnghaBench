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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; TYPE_1__* pcm; } ;
struct snd_pcm_runtime {TYPE_2__* status; } ;
struct snd_card {int dummy; } ;
struct TYPE_4__ {int state; } ;
struct TYPE_3__ {struct snd_card* card; } ;

/* Variables and functions */
 int EBADFD ; 
 int /*<<< orphan*/  SNDRV_CTL_POWER_D0 ; 
#define  SNDRV_PCM_STATE_RUNNING 129 
 int SNDRV_PCM_STATE_SUSPENDED ; 
#define  SNDRV_PCM_STATE_XRUN 128 
 int snd_pcm_stop (struct snd_pcm_substream*,int const) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock_irq (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock_irq (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_power_lock (struct snd_card*) ; 
 int /*<<< orphan*/  snd_power_unlock (struct snd_card*) ; 
 int snd_power_wait (struct snd_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_pcm_xrun(struct snd_pcm_substream *substream)
{
	struct snd_card *card = substream->pcm->card;
	struct snd_pcm_runtime *runtime = substream->runtime;
	int result;

	snd_power_lock(card);
	if (runtime->status->state == SNDRV_PCM_STATE_SUSPENDED) {
		result = snd_power_wait(card, SNDRV_CTL_POWER_D0);
		if (result < 0)
			goto _unlock;
	}

	snd_pcm_stream_lock_irq(substream);
	switch (runtime->status->state) {
	case SNDRV_PCM_STATE_XRUN:
		result = 0;	/* already there */
		break;
	case SNDRV_PCM_STATE_RUNNING:
		result = snd_pcm_stop(substream, SNDRV_PCM_STATE_XRUN);
		break;
	default:
		result = -EBADFD;
	}
	snd_pcm_stream_unlock_irq(substream);
 _unlock:
	snd_power_unlock(card);
	return result;
}