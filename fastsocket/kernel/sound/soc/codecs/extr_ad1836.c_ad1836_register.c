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
struct snd_soc_codec {char* name; int num_dai; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* write ) (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  dapm_paths; int /*<<< orphan*/  dapm_widgets; int /*<<< orphan*/  read; TYPE_1__* dai; int /*<<< orphan*/  owner; int /*<<< orphan*/  reg_cache_size; int /*<<< orphan*/  reg_cache; struct ad1836_priv* private_data; int /*<<< orphan*/  mutex; } ;
struct ad1836_priv {int /*<<< orphan*/  reg_cache; struct snd_soc_codec codec; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD1836_ADC_CTRL1 ; 
 int /*<<< orphan*/  AD1836_ADC_CTRL2 ; 
 int /*<<< orphan*/  AD1836_ADC_CTRL3 ; 
 int /*<<< orphan*/  AD1836_DAC_CTRL1 ; 
 int /*<<< orphan*/  AD1836_DAC_CTRL2 ; 
 int /*<<< orphan*/  AD1836_DAC_L1_VOL ; 
 int /*<<< orphan*/  AD1836_DAC_L2_VOL ; 
 int /*<<< orphan*/  AD1836_DAC_L3_VOL ; 
 int /*<<< orphan*/  AD1836_DAC_R1_VOL ; 
 int /*<<< orphan*/  AD1836_DAC_R2_VOL ; 
 int /*<<< orphan*/  AD1836_DAC_R3_VOL ; 
 int /*<<< orphan*/  AD1836_NUM_REGS ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct snd_soc_codec* ad1836_codec ; 
 TYPE_1__ ad1836_dai ; 
 int /*<<< orphan*/  ad1836_read_reg_cache ; 
 int /*<<< orphan*/  ad1836_write_reg (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kfree (struct ad1836_priv*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int snd_soc_register_codec (struct snd_soc_codec*) ; 
 int snd_soc_register_dai (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_soc_unregister_codec (struct snd_soc_codec*) ; 
 int /*<<< orphan*/  stub1 (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub10 (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub11 (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub8 (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub9 (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ad1836_register(struct ad1836_priv *ad1836)
{
	int ret;
	struct snd_soc_codec *codec = &ad1836->codec;

	if (ad1836_codec) {
		dev_err(codec->dev, "Another ad1836 is registered\n");
		return -EINVAL;
	}

	mutex_init(&codec->mutex);
	INIT_LIST_HEAD(&codec->dapm_widgets);
	INIT_LIST_HEAD(&codec->dapm_paths);
	codec->private_data = ad1836;
	codec->reg_cache = ad1836->reg_cache;
	codec->reg_cache_size = AD1836_NUM_REGS;
	codec->name = "AD1836";
	codec->owner = THIS_MODULE;
	codec->dai = &ad1836_dai;
	codec->num_dai = 1;
	codec->write = ad1836_write_reg;
	codec->read = ad1836_read_reg_cache;
	INIT_LIST_HEAD(&codec->dapm_widgets);
	INIT_LIST_HEAD(&codec->dapm_paths);

	ad1836_dai.dev = codec->dev;
	ad1836_codec = codec;

	/* default setting for ad1836 */
	/* de-emphasis: 48kHz, power-on dac */
	codec->write(codec, AD1836_DAC_CTRL1, 0x300);
	/* unmute dac channels */
	codec->write(codec, AD1836_DAC_CTRL2, 0x0);
	/* high-pass filter enable, power-on adc */
	codec->write(codec, AD1836_ADC_CTRL1, 0x100);
	/* unmute adc channles, adc aux mode */
	codec->write(codec, AD1836_ADC_CTRL2, 0x180);
	/* left/right diff:PGA/MUX */
	codec->write(codec, AD1836_ADC_CTRL3, 0x3A);
	/* volume */
	codec->write(codec, AD1836_DAC_L1_VOL, 0x3FF);
	codec->write(codec, AD1836_DAC_R1_VOL, 0x3FF);
	codec->write(codec, AD1836_DAC_L2_VOL, 0x3FF);
	codec->write(codec, AD1836_DAC_R2_VOL, 0x3FF);
	codec->write(codec, AD1836_DAC_L3_VOL, 0x3FF);
	codec->write(codec, AD1836_DAC_R3_VOL, 0x3FF);

	ret = snd_soc_register_codec(codec);
	if (ret != 0) {
		dev_err(codec->dev, "Failed to register codec: %d\n", ret);
		kfree(ad1836);
		return ret;
	}

	ret = snd_soc_register_dai(&ad1836_dai);
	if (ret != 0) {
		dev_err(codec->dev, "Failed to register DAI: %d\n", ret);
		snd_soc_unregister_codec(codec);
		kfree(ad1836);
		return ret;
	}

	return 0;
}