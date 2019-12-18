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
struct nm256_stream {int running; } ;
struct nm256 {int /*<<< orphan*/  reg_lock; } ;
struct TYPE_2__ {struct nm256_stream* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_nm256_capture_start (struct nm256*,struct nm256_stream*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_nm256_capture_stop (struct nm256*) ; 
 struct nm256* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
snd_nm256_capture_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct nm256 *chip = snd_pcm_substream_chip(substream);
	struct nm256_stream *s = substream->runtime->private_data;
	int err = 0;

	if (snd_BUG_ON(!s))
		return -ENXIO;

	spin_lock(&chip->reg_lock);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		if (! s->running) {
			snd_nm256_capture_start(chip, s, substream);
			s->running = 1;
		}
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		if (s->running) {
			snd_nm256_capture_stop(chip);
			s->running = 0;
		}
		break;
	default:
		err = -EINVAL;
		break;
	}
	spin_unlock(&chip->reg_lock);
	return err;
}