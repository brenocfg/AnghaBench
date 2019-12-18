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
struct snd_pcm_substream {scalar_t__ timer; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  tsleep; int /*<<< orphan*/  sleep; TYPE_1__* status; int /*<<< orphan*/  trigger_tstamp; } ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_TIMER_EVENT_MSTOP ; 
 int /*<<< orphan*/  snd_pcm_trigger_tstamp (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_timer_notify (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_pcm_post_stop(struct snd_pcm_substream *substream, int state)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	if (runtime->status->state != state) {
		snd_pcm_trigger_tstamp(substream);
		if (substream->timer)
			snd_timer_notify(substream->timer, SNDRV_TIMER_EVENT_MSTOP,
					 &runtime->trigger_tstamp);
		runtime->status->state = state;
	}
	wake_up(&runtime->sleep);
	wake_up(&runtime->tsleep);
}