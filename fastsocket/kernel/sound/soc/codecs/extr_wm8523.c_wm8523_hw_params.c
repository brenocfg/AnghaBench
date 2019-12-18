#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct wm8523_priv {int sysclk; } ;
struct snd_soc_pcm_runtime {struct snd_soc_device* socdev; } ;
struct snd_soc_device {TYPE_1__* card; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_soc_codec {int /*<<< orphan*/  dev; struct wm8523_priv* private_data; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_5__ {int ratio; int value; } ;
struct TYPE_4__ {struct snd_soc_codec* codec; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int EINVAL ; 
#define  SNDRV_PCM_FORMAT_S16_LE 131 
#define  SNDRV_PCM_FORMAT_S20_3LE 130 
#define  SNDRV_PCM_FORMAT_S24_LE 129 
#define  SNDRV_PCM_FORMAT_S32_LE 128 
 int /*<<< orphan*/  WM8523_AIF_CTRL1 ; 
 int /*<<< orphan*/  WM8523_AIF_CTRL2 ; 
 int WM8523_SR_MASK ; 
 int WM8523_WL_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__* lrclk_ratios ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int snd_soc_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8523_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_device *socdev = rtd->socdev;
	struct snd_soc_codec *codec = socdev->card->codec;
	struct wm8523_priv *wm8523 = codec->private_data;
	int i;
	u16 aifctrl1 = snd_soc_read(codec, WM8523_AIF_CTRL1);
	u16 aifctrl2 = snd_soc_read(codec, WM8523_AIF_CTRL2);

	/* Find a supported LRCLK ratio */
	for (i = 0; i < ARRAY_SIZE(lrclk_ratios); i++) {
		if (wm8523->sysclk / params_rate(params) ==
		    lrclk_ratios[i].ratio)
			break;
	}

	/* Should never happen, should be handled by constraints */
	if (i == ARRAY_SIZE(lrclk_ratios)) {
		dev_err(codec->dev, "MCLK/fs ratio %d unsupported\n",
			wm8523->sysclk / params_rate(params));
		return -EINVAL;
	}

	aifctrl2 &= ~WM8523_SR_MASK;
	aifctrl2 |= lrclk_ratios[i].value;

	aifctrl1 &= ~WM8523_WL_MASK;
	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		break;
	case SNDRV_PCM_FORMAT_S20_3LE:
		aifctrl1 |= 0x8;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		aifctrl1 |= 0x10;
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		aifctrl1 |= 0x18;
		break;
	}

	snd_soc_write(codec, WM8523_AIF_CTRL1, aifctrl1);
	snd_soc_write(codec, WM8523_AIF_CTRL2, aifctrl2);

	return 0;
}