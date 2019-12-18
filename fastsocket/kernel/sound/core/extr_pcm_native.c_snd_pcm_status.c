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
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_status {scalar_t__ state; scalar_t__ overrange; scalar_t__ avail_max; scalar_t__ delay; scalar_t__ avail; int /*<<< orphan*/  hw_ptr; int /*<<< orphan*/  appl_ptr; int /*<<< orphan*/  tstamp; int /*<<< orphan*/  trigger_tstamp; int /*<<< orphan*/  suspended_state; } ;
struct snd_pcm_runtime {scalar_t__ tstamp_mode; scalar_t__ overrange; scalar_t__ avail_max; scalar_t__ delay; TYPE_2__* status; scalar_t__ buffer_size; TYPE_1__* control; int /*<<< orphan*/  trigger_tstamp; } ;
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/  hw_ptr; int /*<<< orphan*/  tstamp; int /*<<< orphan*/  suspended_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  appl_ptr; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STATE_DRAINING ; 
 scalar_t__ SNDRV_PCM_STATE_OPEN ; 
 scalar_t__ SNDRV_PCM_STATE_RUNNING ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 scalar_t__ SNDRV_PCM_TSTAMP_ENABLE ; 
 scalar_t__ snd_pcm_capture_avail (struct snd_pcm_runtime*) ; 
 int /*<<< orphan*/  snd_pcm_gettime (struct snd_pcm_runtime*,int /*<<< orphan*/ *) ; 
 scalar_t__ snd_pcm_playback_avail (struct snd_pcm_runtime*) ; 
 scalar_t__ snd_pcm_running (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock_irq (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock_irq (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_update_hw_ptr (struct snd_pcm_substream*) ; 

int snd_pcm_status(struct snd_pcm_substream *substream,
		   struct snd_pcm_status *status)
{
	struct snd_pcm_runtime *runtime = substream->runtime;

	snd_pcm_stream_lock_irq(substream);
	status->state = runtime->status->state;
	status->suspended_state = runtime->status->suspended_state;
	if (status->state == SNDRV_PCM_STATE_OPEN)
		goto _end;
	status->trigger_tstamp = runtime->trigger_tstamp;
	if (snd_pcm_running(substream)) {
		snd_pcm_update_hw_ptr(substream);
		if (runtime->tstamp_mode == SNDRV_PCM_TSTAMP_ENABLE) {
			status->tstamp = runtime->status->tstamp;
			goto _tstamp_end;
		}
	}
	snd_pcm_gettime(runtime, &status->tstamp);
 _tstamp_end:
	status->appl_ptr = runtime->control->appl_ptr;
	status->hw_ptr = runtime->status->hw_ptr;
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		status->avail = snd_pcm_playback_avail(runtime);
		if (runtime->status->state == SNDRV_PCM_STATE_RUNNING ||
		    runtime->status->state == SNDRV_PCM_STATE_DRAINING) {
			status->delay = runtime->buffer_size - status->avail;
			status->delay += runtime->delay;
		} else
			status->delay = 0;
	} else {
		status->avail = snd_pcm_capture_avail(runtime);
		if (runtime->status->state == SNDRV_PCM_STATE_RUNNING)
			status->delay = status->avail + runtime->delay;
		else
			status->delay = 0;
	}
	status->avail_max = runtime->avail_max;
	status->overrange = runtime->overrange;
	runtime->avail_max = 0;
	runtime->overrange = 0;
 _end:
 	snd_pcm_stream_unlock_irq(substream);
	return 0;
}