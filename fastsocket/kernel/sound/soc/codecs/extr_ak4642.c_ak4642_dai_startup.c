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
struct snd_soc_dai {struct snd_soc_codec* codec; } ;
struct snd_soc_codec {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  ak4642_write (struct snd_soc_codec*,int,int) ; 

__attribute__((used)) static int ak4642_dai_startup(struct snd_pcm_substream *substream,
			      struct snd_soc_dai *dai)
{
	int is_play = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	struct snd_soc_codec *codec = dai->codec;

	if (is_play) {
		/*
		 * start headphone output
		 *
		 * PLL, Master Mode
		 * Audio I/F Format :MSB justified (ADC & DAC)
		 * Sampling Frequency: 44.1kHz
		 * Digital Volume: −8dB
		 * Bass Boost Level : Middle
		 *
		 * This operation came from example code of
		 * "ASAHI KASEI AK4642" (japanese) manual p97.
		 *
		 * Example code use 0x39, 0x79 value for 0x01 address,
		 * But we need MCKO (0x02) bit now
		 */
		ak4642_write(codec, 0x05, 0x27);
		ak4642_write(codec, 0x0f, 0x09);
		ak4642_write(codec, 0x0e, 0x19);
		ak4642_write(codec, 0x09, 0x91);
		ak4642_write(codec, 0x0c, 0x91);
		ak4642_write(codec, 0x0a, 0x28);
		ak4642_write(codec, 0x0d, 0x28);
		ak4642_write(codec, 0x00, 0x64);
		ak4642_write(codec, 0x01, 0x3b); /* + MCKO bit */
		ak4642_write(codec, 0x01, 0x7b); /* + MCKO bit */
	} else {
		/*
		 * start stereo input
		 *
		 * PLL Master Mode
		 * Audio I/F Format:MSB justified (ADC & DAC)
		 * Sampling Frequency:44.1kHz
		 * Pre MIC AMP:+20dB
		 * MIC Power On
		 * ALC setting:Refer to Table 35
		 * ALC bit=“1”
		 *
		 * This operation came from example code of
		 * "ASAHI KASEI AK4642" (japanese) manual p94.
		 */
		ak4642_write(codec, 0x05, 0x27);
		ak4642_write(codec, 0x02, 0x05);
		ak4642_write(codec, 0x06, 0x3c);
		ak4642_write(codec, 0x08, 0xe1);
		ak4642_write(codec, 0x0b, 0x00);
		ak4642_write(codec, 0x07, 0x21);
		ak4642_write(codec, 0x00, 0x41);
		ak4642_write(codec, 0x10, 0x01);
	}

	return 0;
}