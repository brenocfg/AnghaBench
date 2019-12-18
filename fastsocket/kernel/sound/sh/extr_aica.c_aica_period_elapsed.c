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
struct snd_pcm_substream {TYPE_1__* pcm; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int channels; } ;
struct snd_card_aica {int current_period; int dma_check; int /*<<< orphan*/  spu_dma_work; int /*<<< orphan*/  timer; } ;
struct TYPE_2__ {struct snd_card_aica* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AICA_CONTROL_CHANNEL_SAMPLE_NUMBER ; 
 int AICA_PERIOD_SIZE ; 
 int /*<<< orphan*/  aica_queue ; 
 int frames_to_bytes (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void aica_period_elapsed(unsigned long timer_var)
{
	/*timer function - so cannot sleep */
	int play_period;
	struct snd_pcm_runtime *runtime;
	struct snd_pcm_substream *substream;
	struct snd_card_aica *dreamcastcard;
	substream = (struct snd_pcm_substream *) timer_var;
	runtime = substream->runtime;
	dreamcastcard = substream->pcm->private_data;
	/* Have we played out an additional period? */
	play_period =
	    frames_to_bytes(runtime,
			    readl
			    (AICA_CONTROL_CHANNEL_SAMPLE_NUMBER)) /
	    AICA_PERIOD_SIZE;
	if (play_period == dreamcastcard->current_period) {
		/* reschedule the timer */
		mod_timer(&(dreamcastcard->timer), jiffies + 1);
		return;
	}
	if (runtime->channels > 1)
		dreamcastcard->current_period = play_period;
	if (unlikely(dreamcastcard->dma_check == 0))
		dreamcastcard->dma_check = 1;
	queue_work(aica_queue, &(dreamcastcard->spu_dma_work));
}