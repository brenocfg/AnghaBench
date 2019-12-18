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
struct esschan {int running; int /*<<< orphan*/  hwptr; int /*<<< orphan*/  count; int /*<<< orphan*/  bob_freq; } ;
struct es1968 {int /*<<< orphan*/  substream_lock; } ;
struct TYPE_2__ {struct esschan* private_data; } ;

/* Variables and functions */
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  snd_es1968_bob_dec (struct es1968*) ; 
 int /*<<< orphan*/  snd_es1968_bob_inc (struct es1968*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_es1968_pcm_start (struct es1968*,struct esschan*) ; 
 int /*<<< orphan*/  snd_es1968_pcm_stop (struct es1968*,struct esschan*) ; 
 struct es1968* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_es1968_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct es1968 *chip = snd_pcm_substream_chip(substream);
	struct esschan *es = substream->runtime->private_data;

	spin_lock(&chip->substream_lock);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		if (es->running)
			break;
		snd_es1968_bob_inc(chip, es->bob_freq);
		es->count = 0;
		es->hwptr = 0;
		snd_es1968_pcm_start(chip, es);
		es->running = 1;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		if (! es->running)
			break;
		snd_es1968_pcm_stop(chip, es);
		es->running = 0;
		snd_es1968_bob_dec(chip);
		break;
	}
	spin_unlock(&chip->substream_lock);
	return 0;
}