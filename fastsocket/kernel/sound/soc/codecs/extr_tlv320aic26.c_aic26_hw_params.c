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
typedef  int u16 ;
struct snd_soc_pcm_runtime {struct snd_soc_device* socdev; } ;
struct snd_soc_device {TYPE_1__* card; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_soc_codec {struct aic26* private_data; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct aic26 {int datfm; scalar_t__ master; TYPE_2__* spi; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct snd_soc_codec* codec; } ;

/* Variables and functions */
 int AIC26_DIV_1 ; 
 int AIC26_DIV_1_5 ; 
 int AIC26_DIV_2 ; 
 int AIC26_DIV_3 ; 
 int AIC26_DIV_4 ; 
 int AIC26_DIV_6 ; 
 int /*<<< orphan*/  AIC26_REG_AUDIO_CTRL1 ; 
 int /*<<< orphan*/  AIC26_REG_AUDIO_CTRL3 ; 
 int /*<<< orphan*/  AIC26_REG_PLL_PROG1 ; 
 int /*<<< orphan*/  AIC26_REG_PLL_PROG2 ; 
 int AIC26_WLEN_16 ; 
 int AIC26_WLEN_24 ; 
 int AIC26_WLEN_32 ; 
 int EINVAL ; 
#define  SNDRV_PCM_FORMAT_S16_BE 131 
#define  SNDRV_PCM_FORMAT_S24_BE 130 
#define  SNDRV_PCM_FORMAT_S32_BE 129 
#define  SNDRV_PCM_FORMAT_S8 128 
 int aic26_reg_read_cache (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aic26_reg_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int aic26_hw_params(struct snd_pcm_substream *substream,
			   struct snd_pcm_hw_params *params,
			   struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_device *socdev = rtd->socdev;
	struct snd_soc_codec *codec = socdev->card->codec;
	struct aic26 *aic26 = codec->private_data;
	int fsref, divisor, wlen, pval, jval, dval, qval;
	u16 reg;

	dev_dbg(&aic26->spi->dev, "aic26_hw_params(substream=%p, params=%p)\n",
		substream, params);
	dev_dbg(&aic26->spi->dev, "rate=%i format=%i\n", params_rate(params),
		params_format(params));

	switch (params_rate(params)) {
	case 8000:  fsref = 48000; divisor = AIC26_DIV_6; break;
	case 11025: fsref = 44100; divisor = AIC26_DIV_4; break;
	case 12000: fsref = 48000; divisor = AIC26_DIV_4; break;
	case 16000: fsref = 48000; divisor = AIC26_DIV_3; break;
	case 22050: fsref = 44100; divisor = AIC26_DIV_2; break;
	case 24000: fsref = 48000; divisor = AIC26_DIV_2; break;
	case 32000: fsref = 48000; divisor = AIC26_DIV_1_5; break;
	case 44100: fsref = 44100; divisor = AIC26_DIV_1; break;
	case 48000: fsref = 48000; divisor = AIC26_DIV_1; break;
	default:
		dev_dbg(&aic26->spi->dev, "bad rate\n"); return -EINVAL;
	}

	/* select data word length */
	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S8:     wlen = AIC26_WLEN_16; break;
	case SNDRV_PCM_FORMAT_S16_BE: wlen = AIC26_WLEN_16; break;
	case SNDRV_PCM_FORMAT_S24_BE: wlen = AIC26_WLEN_24; break;
	case SNDRV_PCM_FORMAT_S32_BE: wlen = AIC26_WLEN_32; break;
	default:
		dev_dbg(&aic26->spi->dev, "bad format\n"); return -EINVAL;
	}

	/* Configure PLL */
	pval = 1;
	jval = (fsref == 44100) ? 7 : 8;
	dval = (fsref == 44100) ? 5264 : 1920;
	qval = 0;
	reg = 0x8000 | qval << 11 | pval << 8 | jval << 2;
	aic26_reg_write(codec, AIC26_REG_PLL_PROG1, reg);
	reg = dval << 2;
	aic26_reg_write(codec, AIC26_REG_PLL_PROG2, reg);

	/* Audio Control 3 (master mode, fsref rate) */
	reg = aic26_reg_read_cache(codec, AIC26_REG_AUDIO_CTRL3);
	reg &= ~0xf800;
	if (aic26->master)
		reg |= 0x0800;
	if (fsref == 48000)
		reg |= 0x2000;
	aic26_reg_write(codec, AIC26_REG_AUDIO_CTRL3, reg);

	/* Audio Control 1 (FSref divisor) */
	reg = aic26_reg_read_cache(codec, AIC26_REG_AUDIO_CTRL1);
	reg &= ~0x0fff;
	reg |= wlen | aic26->datfm | (divisor << 3) | divisor;
	aic26_reg_write(codec, AIC26_REG_AUDIO_CTRL1, reg);

	return 0;
}