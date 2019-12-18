#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_pcm_substream {int dummy; } ;
struct snd_line6_pcm {int /*<<< orphan*/  flags; scalar_t__ count_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_PAUSE_PLAYBACK ; 
 int /*<<< orphan*/  BIT_RUNNING_PLAYBACK ; 
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 131 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 130 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct snd_line6_pcm* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int submit_audio_out_all_urbs (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink_audio_out_urbs (struct snd_line6_pcm*) ; 

int snd_line6_playback_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_line6_pcm *line6pcm = snd_pcm_substream_chip(substream);
	int err;
	line6pcm->count_out = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		if (!test_and_set_bit(BIT_RUNNING_PLAYBACK, &line6pcm->flags)) {
			err = submit_audio_out_all_urbs(substream);

			if (err < 0) {
				clear_bit(BIT_RUNNING_PLAYBACK, &line6pcm->flags);
				return err;
			}
		}

		break;

	case SNDRV_PCM_TRIGGER_STOP:
		if (test_and_clear_bit(BIT_RUNNING_PLAYBACK, &line6pcm->flags))
			unlink_audio_out_urbs(line6pcm);

		break;

	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		set_bit(BIT_PAUSE_PLAYBACK, &line6pcm->flags);
		break;

	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		clear_bit(BIT_PAUSE_PLAYBACK, &line6pcm->flags);
		break;

	default:
		return -EINVAL;
	}

	return 0;
}