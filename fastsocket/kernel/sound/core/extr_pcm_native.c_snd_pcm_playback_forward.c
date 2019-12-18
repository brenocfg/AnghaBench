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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ boundary; TYPE_2__* control; TYPE_1__* status; } ;
typedef  scalar_t__ snd_pcm_uframes_t ;
typedef  scalar_t__ snd_pcm_sframes_t ;
struct TYPE_4__ {scalar_t__ appl_ptr; } ;
struct TYPE_3__ {int state; } ;

/* Variables and functions */
 scalar_t__ EBADFD ; 
 scalar_t__ EPIPE ; 
 scalar_t__ ESTRPIPE ; 
#define  SNDRV_PCM_STATE_DRAINING 133 
#define  SNDRV_PCM_STATE_PAUSED 132 
#define  SNDRV_PCM_STATE_PREPARED 131 
#define  SNDRV_PCM_STATE_RUNNING 130 
#define  SNDRV_PCM_STATE_SUSPENDED 129 
#define  SNDRV_PCM_STATE_XRUN 128 
 scalar_t__ snd_pcm_playback_avail (struct snd_pcm_runtime*) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock_irq (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock_irq (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_update_hw_ptr (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_sframes_t snd_pcm_playback_forward(struct snd_pcm_substream *substream,
						  snd_pcm_uframes_t frames)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	snd_pcm_sframes_t appl_ptr;
	snd_pcm_sframes_t ret;
	snd_pcm_sframes_t avail;

	if (frames == 0)
		return 0;

	snd_pcm_stream_lock_irq(substream);
	switch (runtime->status->state) {
	case SNDRV_PCM_STATE_PREPARED:
	case SNDRV_PCM_STATE_PAUSED:
		break;
	case SNDRV_PCM_STATE_DRAINING:
	case SNDRV_PCM_STATE_RUNNING:
		if (snd_pcm_update_hw_ptr(substream) >= 0)
			break;
		/* Fall through */
	case SNDRV_PCM_STATE_XRUN:
		ret = -EPIPE;
		goto __end;
	case SNDRV_PCM_STATE_SUSPENDED:
		ret = -ESTRPIPE;
		goto __end;
	default:
		ret = -EBADFD;
		goto __end;
	}

	avail = snd_pcm_playback_avail(runtime);
	if (avail <= 0) {
		ret = 0;
		goto __end;
	}
	if (frames > (snd_pcm_uframes_t)avail)
		frames = avail;
	appl_ptr = runtime->control->appl_ptr + frames;
	if (appl_ptr >= (snd_pcm_sframes_t)runtime->boundary)
		appl_ptr -= runtime->boundary;
	runtime->control->appl_ptr = appl_ptr;
	ret = frames;
 __end:
	snd_pcm_stream_unlock_irq(substream);
	return ret;
}