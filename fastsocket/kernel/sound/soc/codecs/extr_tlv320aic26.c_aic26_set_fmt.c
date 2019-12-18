#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {struct snd_soc_codec* codec; } ;
struct snd_soc_codec {struct aic26* private_data; } ;
struct aic26 {int master; TYPE_1__* spi; int /*<<< orphan*/  datfm; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC26_DATFM_DSP ; 
 int /*<<< orphan*/  AIC26_DATFM_I2S ; 
 int /*<<< orphan*/  AIC26_DATFM_LEFTJ ; 
 int /*<<< orphan*/  AIC26_DATFM_RIGHTJ ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 133 
#define  SND_SOC_DAIFMT_CBS_CFS 132 
#define  SND_SOC_DAIFMT_DSP_A 131 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_LEFT_J 129 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int aic26_set_fmt(struct snd_soc_dai *codec_dai, unsigned int fmt)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	struct aic26 *aic26 = codec->private_data;

	dev_dbg(&aic26->spi->dev, "aic26_set_fmt(dai=%p, fmt==%i)\n",
		codec_dai, fmt);

	/* set master/slave audio interface */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM: aic26->master = 1; break;
	case SND_SOC_DAIFMT_CBS_CFS: aic26->master = 0; break;
	default:
		dev_dbg(&aic26->spi->dev, "bad master\n"); return -EINVAL;
	}

	/* interface format */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:     aic26->datfm = AIC26_DATFM_I2S; break;
	case SND_SOC_DAIFMT_DSP_A:   aic26->datfm = AIC26_DATFM_DSP; break;
	case SND_SOC_DAIFMT_RIGHT_J: aic26->datfm = AIC26_DATFM_RIGHTJ; break;
	case SND_SOC_DAIFMT_LEFT_J:  aic26->datfm = AIC26_DATFM_LEFTJ; break;
	default:
		dev_dbg(&aic26->spi->dev, "bad format\n"); return -EINVAL;
	}

	return 0;
}