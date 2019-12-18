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
struct snd_soc_pcm_runtime {struct snd_soc_device* socdev; } ;
struct snd_soc_device {TYPE_1__* card; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_soc_codec {int (* read ) (struct snd_soc_codec*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write ) (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ;} ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {struct snd_soc_codec* codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD1938_ADC_CTRL1 ; 
 int AD1938_ADC_WORD_LEN_MASK ; 
 int /*<<< orphan*/  AD1938_DAC_CTRL2 ; 
 int AD1938_DAC_WORD_LEN_MASK ; 
#define  SNDRV_PCM_FORMAT_S16_LE 131 
#define  SNDRV_PCM_FORMAT_S20_3LE 130 
#define  SNDRV_PCM_FORMAT_S24_LE 129 
#define  SNDRV_PCM_FORMAT_S32_LE 128 
 int params_format (struct snd_pcm_hw_params*) ; 
 int stub1 (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int stub3 (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ad1938_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params,
		struct snd_soc_dai *dai)
{
	int word_len = 0, reg = 0;

	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_device *socdev = rtd->socdev;
	struct snd_soc_codec *codec = socdev->card->codec;

	/* bit size */
	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		word_len = 3;
		break;
	case SNDRV_PCM_FORMAT_S20_3LE:
		word_len = 1;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
	case SNDRV_PCM_FORMAT_S32_LE:
		word_len = 0;
		break;
	}

	reg = codec->read(codec, AD1938_DAC_CTRL2);
	reg = (reg & (~AD1938_DAC_WORD_LEN_MASK)) | word_len;
	codec->write(codec, AD1938_DAC_CTRL2, reg);

	reg = codec->read(codec, AD1938_ADC_CTRL1);
	reg = (reg & (~AD1938_ADC_WORD_LEN_MASK)) | word_len;
	codec->write(codec, AD1938_ADC_CTRL1, reg);

	return 0;
}