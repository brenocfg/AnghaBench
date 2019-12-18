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
struct snd_pcm_hw_params {int dummy; } ;
struct snd_msnd {int /*<<< orphan*/  play_sample_rate; int /*<<< orphan*/  play_channels; int /*<<< orphan*/  play_sample_size; void* mappedbase; } ;

/* Variables and functions */
 int DAPQ_DATA_BUFF ; 
 int /*<<< orphan*/  DAQDS__size ; 
 int DAQDS_wChannels ; 
 int DAQDS_wSampleRate ; 
 int DAQDS_wSampleSize ; 
 int /*<<< orphan*/  params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 struct snd_msnd* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int snd_msnd_playback_hw_params(struct snd_pcm_substream *substream,
					struct snd_pcm_hw_params *params)
{
	int	i;
	struct snd_msnd *chip = snd_pcm_substream_chip(substream);
	void	*pDAQ =	chip->mappedbase + DAPQ_DATA_BUFF;

	chip->play_sample_size = snd_pcm_format_width(params_format(params));
	chip->play_channels = params_channels(params);
	chip->play_sample_rate = params_rate(params);

	for (i = 0; i < 3; ++i, pDAQ += DAQDS__size) {
		writew(chip->play_sample_size, pDAQ + DAQDS_wSampleSize);
		writew(chip->play_channels, pDAQ + DAQDS_wChannels);
		writew(chip->play_sample_rate, pDAQ + DAQDS_wSampleRate);
	}
	/* dont do this here:
	 * snd_msnd_calibrate_adc(chip->play_sample_rate);
	 */

	return 0;
}