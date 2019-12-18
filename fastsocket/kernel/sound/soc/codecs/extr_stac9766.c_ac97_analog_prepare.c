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
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {unsigned short rate; } ;

/* Variables and functions */
 unsigned short AC97_EXTENDED_STATUS ; 
 unsigned short AC97_PCM_FRONT_DAC_RATE ; 
 unsigned short AC97_PCM_LR_ADC_RATE ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 unsigned short stac9766_ac97_read (struct snd_soc_codec*,unsigned short) ; 
 int stac9766_ac97_write (struct snd_soc_codec*,unsigned short,unsigned short) ; 

__attribute__((used)) static int ac97_analog_prepare(struct snd_pcm_substream *substream,
			       struct snd_soc_dai *dai)
{
	struct snd_soc_codec *codec = dai->codec;
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned short reg, vra;

	vra = stac9766_ac97_read(codec, AC97_EXTENDED_STATUS);

	vra |= 0x1; /* enable variable rate audio */

	stac9766_ac97_write(codec, AC97_EXTENDED_STATUS, vra);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		reg = AC97_PCM_FRONT_DAC_RATE;
	else
		reg = AC97_PCM_LR_ADC_RATE;

	return stac9766_ac97_write(codec, reg, runtime->rate);
}