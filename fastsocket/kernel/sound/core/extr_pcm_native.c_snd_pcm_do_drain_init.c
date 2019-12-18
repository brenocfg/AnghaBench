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
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {TYPE_1__* status; } ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 void* SNDRV_PCM_STATE_DRAINING ; 
#define  SNDRV_PCM_STATE_PREPARED 129 
#define  SNDRV_PCM_STATE_RUNNING 128 
 void* SNDRV_PCM_STATE_SETUP ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 scalar_t__ snd_pcm_capture_avail (struct snd_pcm_runtime*) ; 
 int /*<<< orphan*/  snd_pcm_do_start (struct snd_pcm_substream*,void*) ; 
 int /*<<< orphan*/  snd_pcm_do_stop (struct snd_pcm_substream*,int) ; 
 int /*<<< orphan*/  snd_pcm_playback_empty (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_post_start (struct snd_pcm_substream*,void*) ; 
 int /*<<< orphan*/  snd_pcm_post_stop (struct snd_pcm_substream*,int) ; 

__attribute__((used)) static int snd_pcm_do_drain_init(struct snd_pcm_substream *substream, int state)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		switch (runtime->status->state) {
		case SNDRV_PCM_STATE_PREPARED:
			/* start playback stream if possible */
			if (! snd_pcm_playback_empty(substream)) {
				snd_pcm_do_start(substream, SNDRV_PCM_STATE_DRAINING);
				snd_pcm_post_start(substream, SNDRV_PCM_STATE_DRAINING);
			}
			break;
		case SNDRV_PCM_STATE_RUNNING:
			runtime->status->state = SNDRV_PCM_STATE_DRAINING;
			break;
		default:
			break;
		}
	} else {
		/* stop running stream */
		if (runtime->status->state == SNDRV_PCM_STATE_RUNNING) {
			int new_state = snd_pcm_capture_avail(runtime) > 0 ?
				SNDRV_PCM_STATE_DRAINING : SNDRV_PCM_STATE_SETUP;
			snd_pcm_do_stop(substream, new_state);
			snd_pcm_post_stop(substream, new_state);
		}
	}
	return 0;
}