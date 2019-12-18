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
struct snd_pcm_substream {int number; int /*<<< orphan*/  runtime; } ;
struct echoaudio {scalar_t__ digital_mode; int /*<<< orphan*/  mode_mutex; scalar_t__ can_set_rate; scalar_t__ rate_set; int /*<<< orphan*/  opencount; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_ACT (char*) ; 
 scalar_t__ DIGITAL_MODE_ADAT ; 
 int ECHOCARD_HAS_ADAT ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_FORMAT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw_rule_playback_channels_by_format ; 
 int /*<<< orphan*/  hw_rule_playback_format_by_channels ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int num_digital_busses_out (struct echoaudio*) ; 
 int pcm_open (struct snd_pcm_substream*,int) ; 
 int snd_pcm_hw_rule_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct echoaudio* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int pcm_digital_out_open(struct snd_pcm_substream *substream)
{
	struct echoaudio *chip = snd_pcm_substream_chip(substream);
	int err, max_channels;

	DE_ACT(("pcm_digital_out_open\n"));
	max_channels = num_digital_busses_out(chip) - substream->number;
	mutex_lock(&chip->mode_mutex);
	if (chip->digital_mode == DIGITAL_MODE_ADAT)
		err = pcm_open(substream, max_channels);
	else	/* If the card has ADAT, subtract the 6 channels
		 * that S/PDIF doesn't have
		 */
		err = pcm_open(substream, max_channels - ECHOCARD_HAS_ADAT);

	if (err < 0)
		goto dout_exit;

	if ((err = snd_pcm_hw_rule_add(substream->runtime, 0,
				       SNDRV_PCM_HW_PARAM_CHANNELS,
				       hw_rule_playback_channels_by_format,
				       NULL, SNDRV_PCM_HW_PARAM_FORMAT,
				       -1)) < 0)
		goto dout_exit;
	if ((err = snd_pcm_hw_rule_add(substream->runtime, 0,
				       SNDRV_PCM_HW_PARAM_FORMAT,
				       hw_rule_playback_format_by_channels,
				       NULL, SNDRV_PCM_HW_PARAM_CHANNELS,
				       -1)) < 0)
		goto dout_exit;
	atomic_inc(&chip->opencount);
	if (atomic_read(&chip->opencount) > 1 && chip->rate_set)
		chip->can_set_rate=0;
dout_exit:
	mutex_unlock(&chip->mode_mutex);
	return err;
}