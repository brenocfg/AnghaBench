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
struct snd_pcm_substream {int /*<<< orphan*/  stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {TYPE_1__* status; } ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 int EBADFD ; 
 int EPIPE ; 
#define  SNDRV_PCM_STATE_DRAINING 132 
#define  SNDRV_PCM_STATE_PREPARED 131 
#define  SNDRV_PCM_STATE_RUNNING 130 
#define  SNDRV_PCM_STATE_SUSPENDED 129 
#define  SNDRV_PCM_STATE_XRUN 128 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  snd_pcm_stream_lock_irq (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock_irq (struct snd_pcm_substream*) ; 
 int snd_pcm_update_hw_ptr (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_pcm_hwsync(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	int err;

	snd_pcm_stream_lock_irq(substream);
	switch (runtime->status->state) {
	case SNDRV_PCM_STATE_DRAINING:
		if (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			goto __badfd;
	case SNDRV_PCM_STATE_RUNNING:
		if ((err = snd_pcm_update_hw_ptr(substream)) < 0)
			break;
		/* Fall through */
	case SNDRV_PCM_STATE_PREPARED:
	case SNDRV_PCM_STATE_SUSPENDED:
		err = 0;
		break;
	case SNDRV_PCM_STATE_XRUN:
		err = -EPIPE;
		break;
	default:
	      __badfd:
		err = -EBADFD;
		break;
	}
	snd_pcm_stream_unlock_irq(substream);
	return err;
}