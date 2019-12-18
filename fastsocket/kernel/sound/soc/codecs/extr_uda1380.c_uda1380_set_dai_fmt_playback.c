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

/* Variables and functions */
 int EINVAL ; 
 int R01_SFORI_I2S ; 
 int R01_SFORI_LSB16 ; 
 int R01_SFORI_MASK ; 
 int R01_SFORI_MSB ; 
 unsigned int SND_SOC_DAIFMT_CBS_CFS ; 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_LSB 129 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_MSB 128 
 int /*<<< orphan*/  UDA1380_IFACE ; 
 int uda1380_read_reg_cache (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uda1380_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int uda1380_set_dai_fmt_playback(struct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	int iface;

	/* set up DAI based upon fmt */
	iface = uda1380_read_reg_cache(codec, UDA1380_IFACE);
	iface &= ~R01_SFORI_MASK;

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		iface |= R01_SFORI_I2S;
		break;
	case SND_SOC_DAIFMT_LSB:
		iface |= R01_SFORI_LSB16;
		break;
	case SND_SOC_DAIFMT_MSB:
		iface |= R01_SFORI_MSB;
	}

	/* DATAI is slave only, so this has to be slave */
	if ((fmt & SND_SOC_DAIFMT_MASTER_MASK) != SND_SOC_DAIFMT_CBS_CFS)
		return -EINVAL;

	uda1380_write(codec, UDA1380_IFACE, iface);

	return 0;
}