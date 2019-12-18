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
struct snd_msnd {int /*<<< orphan*/  capture_sample_rate; int /*<<< orphan*/  capture_channels; int /*<<< orphan*/  capture_sample_size; void* mappedbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAQDS__size ; 
 int DAQDS_wChannels ; 
 int DAQDS_wSampleRate ; 
 int DAQDS_wSampleSize ; 
 int DARQ_DATA_BUFF ; 
 int /*<<< orphan*/  params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 struct snd_msnd* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int snd_msnd_capture_hw_params(struct snd_pcm_substream *substream,
					struct snd_pcm_hw_params *params)
{
	int		i;
	struct snd_msnd *chip = snd_pcm_substream_chip(substream);
	void		*pDAQ = chip->mappedbase + DARQ_DATA_BUFF;

	chip->capture_sample_size = snd_pcm_format_width(params_format(params));
	chip->capture_channels = params_channels(params);
	chip->capture_sample_rate = params_rate(params);

	for (i = 0; i < 3; ++i, pDAQ += DAQDS__size) {
		writew(chip->capture_sample_size, pDAQ + DAQDS_wSampleSize);
		writew(chip->capture_channels, pDAQ + DAQDS_wChannels);
		writew(chip->capture_sample_rate, pDAQ + DAQDS_wSampleRate);
	}
	return 0;
}