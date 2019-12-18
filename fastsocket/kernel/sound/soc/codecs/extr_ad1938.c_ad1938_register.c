#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_codec {char* name; int num_dai; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* write ) (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  dapm_paths; int /*<<< orphan*/  dapm_widgets; int /*<<< orphan*/  set_bias_level; int /*<<< orphan*/  read; TYPE_1__* dai; int /*<<< orphan*/  owner; int /*<<< orphan*/  reg_cache_size; int /*<<< orphan*/  reg_cache; struct ad1938_priv* private_data; int /*<<< orphan*/  mutex; } ;
struct ad1938_priv {int /*<<< orphan*/  reg_cache; struct snd_soc_codec codec; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD1938_ADC_CTRL0 ; 
 int /*<<< orphan*/  AD1938_ADC_CTRL1 ; 
 int /*<<< orphan*/  AD1938_DAC_CHNL_MUTE ; 
 int /*<<< orphan*/  AD1938_DAC_CTRL0 ; 
 int /*<<< orphan*/  AD1938_DAC_CTRL2 ; 
 int /*<<< orphan*/  AD1938_NUM_REGS ; 
 int /*<<< orphan*/  AD1938_PLL_CLK_CTRL0 ; 
 int /*<<< orphan*/  AD1938_PLL_CLK_CTRL1 ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct snd_soc_codec* ad1938_codec ; 
 TYPE_1__ ad1938_dai ; 
 int /*<<< orphan*/  ad1938_fill_cache (struct snd_soc_codec*) ; 
 int /*<<< orphan*/  ad1938_read_reg_cache ; 
 int /*<<< orphan*/  ad1938_set_bias_level ; 
 int /*<<< orphan*/  ad1938_write_reg (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kfree (struct ad1938_priv*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int snd_soc_register_codec (struct snd_soc_codec*) ; 
 int snd_soc_register_dai (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_soc_unregister_codec (struct snd_soc_codec*) ; 
 int /*<<< orphan*/  stub1 (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ad1938_register(struct ad1938_priv *ad1938)
{
	int ret;
	struct snd_soc_codec *codec = &ad1938->codec;

	if (ad1938_codec) {
		dev_err(codec->dev, "Another ad1938 is registered\n");
		return -EINVAL;
	}

	mutex_init(&codec->mutex);
	INIT_LIST_HEAD(&codec->dapm_widgets);
	INIT_LIST_HEAD(&codec->dapm_paths);
	codec->private_data = ad1938;
	codec->reg_cache = ad1938->reg_cache;
	codec->reg_cache_size = AD1938_NUM_REGS;
	codec->name = "AD1938";
	codec->owner = THIS_MODULE;
	codec->dai = &ad1938_dai;
	codec->num_dai = 1;
	codec->write = ad1938_write_reg;
	codec->read = ad1938_read_reg_cache;
	codec->set_bias_level = ad1938_set_bias_level;
	INIT_LIST_HEAD(&codec->dapm_widgets);
	INIT_LIST_HEAD(&codec->dapm_paths);

	ad1938_dai.dev = codec->dev;
	ad1938_codec = codec;

	/* default setting for ad1938 */

	/* unmute dac channels */
	codec->write(codec, AD1938_DAC_CHNL_MUTE, 0x0);
	/* de-emphasis: 48kHz, powedown dac */
	codec->write(codec, AD1938_DAC_CTRL2, 0x1A);
	/* powerdown dac, dac in tdm mode */
	codec->write(codec, AD1938_DAC_CTRL0, 0x41);
	/* high-pass filter enable */
	codec->write(codec, AD1938_ADC_CTRL0, 0x3);
	/* sata delay=1, adc aux mode */
	codec->write(codec, AD1938_ADC_CTRL1, 0x43);
	/* pll input: mclki/xi */
	codec->write(codec, AD1938_PLL_CLK_CTRL0, 0x9D);
	codec->write(codec, AD1938_PLL_CLK_CTRL1, 0x04);

	ad1938_fill_cache(codec);

	ret = snd_soc_register_codec(codec);
	if (ret != 0) {
		dev_err(codec->dev, "Failed to register codec: %d\n", ret);
		kfree(ad1938);
		return ret;
	}

	ret = snd_soc_register_dai(&ad1938_dai);
	if (ret != 0) {
		dev_err(codec->dev, "Failed to register DAI: %d\n", ret);
		snd_soc_unregister_codec(codec);
		kfree(ad1938);
		return ret;
	}

	return 0;
}