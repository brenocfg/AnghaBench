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
struct snd_msnd {int last_recbank; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  F_READING ; 
 int /*<<< orphan*/  HDEX_RECORD_START ; 
 int /*<<< orphan*/  HDEX_RECORD_STOP ; 
 int SNDRV_PCM_TRIGGER_START ; 
 int SNDRV_PCM_TRIGGER_STOP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ snd_msnd_send_dsp_cmd (struct snd_msnd*,int /*<<< orphan*/ ) ; 
 struct snd_msnd* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_msnd_capture_trigger(struct snd_pcm_substream *substream,
				    int cmd)
{
	struct snd_msnd *chip = snd_pcm_substream_chip(substream);

	if (cmd == SNDRV_PCM_TRIGGER_START) {
		chip->last_recbank = -1;
		set_bit(F_READING, &chip->flags);
		if (snd_msnd_send_dsp_cmd(chip, HDEX_RECORD_START) == 0)
			return 0;

		clear_bit(F_READING, &chip->flags);
	} else if (cmd == SNDRV_PCM_TRIGGER_STOP) {
		clear_bit(F_READING, &chip->flags);
		snd_msnd_send_dsp_cmd(chip, HDEX_RECORD_STOP);
		return 0;
	}
	return -EINVAL;
}