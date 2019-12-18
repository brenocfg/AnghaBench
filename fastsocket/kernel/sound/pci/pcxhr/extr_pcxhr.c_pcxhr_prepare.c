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
struct snd_pcxhr {struct pcxhr_mgr* mgr; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct pcxhr_mgr {scalar_t__ sample_rate; int /*<<< orphan*/  setup_mutex; } ;
struct TYPE_2__ {scalar_t__ rate; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  periods; int /*<<< orphan*/  period_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pcxhr_hardware_timer (struct pcxhr_mgr*,int) ; 
 int pcxhr_set_clock (struct pcxhr_mgr*,scalar_t__) ; 
 struct snd_pcxhr* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_printdd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcxhr_prepare(struct snd_pcm_substream *subs)
{
	struct snd_pcxhr *chip = snd_pcm_substream_chip(subs);
	struct pcxhr_mgr *mgr = chip->mgr;
	int err = 0;

	snd_printdd("pcxhr_prepare : period_size(%lx) periods(%x) buffer_size(%lx)\n",
		    subs->runtime->period_size, subs->runtime->periods,
		    subs->runtime->buffer_size);

	mutex_lock(&mgr->setup_mutex);

	do {
		/* only the first stream can choose the sample rate */
		/* set the clock only once (first stream) */
		if (mgr->sample_rate != subs->runtime->rate) {
			err = pcxhr_set_clock(mgr, subs->runtime->rate);
			if (err)
				break;
			if (mgr->sample_rate == 0)
				/* start the DSP-timer */
				err = pcxhr_hardware_timer(mgr, 1);
			mgr->sample_rate = subs->runtime->rate;
		}
	} while(0);	/* do only once (so we can use break instead of goto) */

	mutex_unlock(&mgr->setup_mutex);

	return err;
}