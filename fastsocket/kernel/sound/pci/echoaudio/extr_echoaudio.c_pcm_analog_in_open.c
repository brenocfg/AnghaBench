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
struct snd_pcm_substream {int /*<<< orphan*/  runtime; scalar_t__ number; } ;
struct echoaudio {int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  opencount; scalar_t__ can_set_rate; scalar_t__ rate_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_ACT (char*) ; 
 int /*<<< orphan*/  DE_HWP (char*) ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_FORMAT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw_rule_capture_channels_by_format ; 
 int /*<<< orphan*/  hw_rule_capture_format_by_channels ; 
 scalar_t__ num_analog_busses_in (struct echoaudio*) ; 
 int pcm_open (struct snd_pcm_substream*,scalar_t__) ; 
 int snd_pcm_hw_rule_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct echoaudio* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int pcm_analog_in_open(struct snd_pcm_substream *substream)
{
	struct echoaudio *chip = snd_pcm_substream_chip(substream);
	int err;

	DE_ACT(("pcm_analog_in_open\n"));
	if ((err = pcm_open(substream, num_analog_busses_in(chip) -
			    substream->number)) < 0)
		return err;
	if ((err = snd_pcm_hw_rule_add(substream->runtime, 0,
				       SNDRV_PCM_HW_PARAM_CHANNELS,
				       hw_rule_capture_channels_by_format, NULL,
				       SNDRV_PCM_HW_PARAM_FORMAT, -1)) < 0)
		return err;
	if ((err = snd_pcm_hw_rule_add(substream->runtime, 0,
				       SNDRV_PCM_HW_PARAM_FORMAT,
				       hw_rule_capture_format_by_channels, NULL,
				       SNDRV_PCM_HW_PARAM_CHANNELS, -1)) < 0)
		return err;
	atomic_inc(&chip->opencount);
	if (atomic_read(&chip->opencount) > 1 && chip->rate_set)
		chip->can_set_rate=0;
	DE_HWP(("pcm_analog_in_open  cs=%d  oc=%d  r=%d\n",
		chip->can_set_rate, atomic_read(&chip->opencount),
		chip->sample_rate));
	return 0;
}