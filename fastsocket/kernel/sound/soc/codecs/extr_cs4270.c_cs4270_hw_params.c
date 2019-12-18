#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {struct snd_soc_device* socdev; } ;
struct snd_soc_device {TYPE_1__* card; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_soc_codec {int /*<<< orphan*/  dev; struct cs4270_private* private_data; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct cs4270_private {unsigned int mclk; int mode; scalar_t__ slave_mode; } ;
struct TYPE_4__ {unsigned int ratio; int mclk; int speed_mode; } ;
struct TYPE_3__ {struct snd_soc_codec* codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4270_FORMAT ; 
 int CS4270_FORMAT_ADC_I2S ; 
 int CS4270_FORMAT_ADC_LJ ; 
 int CS4270_FORMAT_ADC_MASK ; 
 int CS4270_FORMAT_DAC_I2S ; 
 int CS4270_FORMAT_DAC_LJ ; 
 int CS4270_FORMAT_DAC_MASK ; 
 int /*<<< orphan*/  CS4270_MODE ; 
 int CS4270_MODE_DIV_MASK ; 
 int CS4270_MODE_SLAVE ; 
 int CS4270_MODE_SPEED_MASK ; 
 int EINVAL ; 
 unsigned int NUM_MCLK_RATIOS ; 
#define  SND_SOC_DAIFMT_I2S 129 
#define  SND_SOC_DAIFMT_LEFT_J 128 
 TYPE_2__* cs4270_mode_ratios ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int snd_soc_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int snd_soc_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cs4270_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_device *socdev = rtd->socdev;
	struct snd_soc_codec *codec = socdev->card->codec;
	struct cs4270_private *cs4270 = codec->private_data;
	int ret;
	unsigned int i;
	unsigned int rate;
	unsigned int ratio;
	int reg;

	/* Figure out which MCLK/LRCK ratio to use */

	rate = params_rate(params);	/* Sampling rate, in Hz */
	ratio = cs4270->mclk / rate;	/* MCLK/LRCK ratio */

	for (i = 0; i < NUM_MCLK_RATIOS; i++) {
		if (cs4270_mode_ratios[i].ratio == ratio)
			break;
	}

	if (i == NUM_MCLK_RATIOS) {
		/* We did not find a matching ratio */
		dev_err(codec->dev, "could not find matching ratio\n");
		return -EINVAL;
	}

	/* Set the sample rate */

	reg = snd_soc_read(codec, CS4270_MODE);
	reg &= ~(CS4270_MODE_SPEED_MASK | CS4270_MODE_DIV_MASK);
	reg |= cs4270_mode_ratios[i].mclk;

	if (cs4270->slave_mode)
		reg |= CS4270_MODE_SLAVE;
	else
		reg |= cs4270_mode_ratios[i].speed_mode;

	ret = snd_soc_write(codec, CS4270_MODE, reg);
	if (ret < 0) {
		dev_err(codec->dev, "i2c write failed\n");
		return ret;
	}

	/* Set the DAI format */

	reg = snd_soc_read(codec, CS4270_FORMAT);
	reg &= ~(CS4270_FORMAT_DAC_MASK | CS4270_FORMAT_ADC_MASK);

	switch (cs4270->mode) {
	case SND_SOC_DAIFMT_I2S:
		reg |= CS4270_FORMAT_DAC_I2S | CS4270_FORMAT_ADC_I2S;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		reg |= CS4270_FORMAT_DAC_LJ | CS4270_FORMAT_ADC_LJ;
		break;
	default:
		dev_err(codec->dev, "unknown dai format\n");
		return -EINVAL;
	}

	ret = snd_soc_write(codec, CS4270_FORMAT, reg);
	if (ret < 0) {
		dev_err(codec->dev, "i2c write failed\n");
		return ret;
	}

	return ret;
}