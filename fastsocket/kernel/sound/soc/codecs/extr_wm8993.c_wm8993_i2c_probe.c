#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int jd_scthr; int jd_thr; int micbias1_lvl; scalar_t__ lineout2fb; scalar_t__ lineout1fb; int /*<<< orphan*/  lineout2_diff; int /*<<< orphan*/  lineout1_diff; } ;
struct snd_soc_codec {char* name; int (* write ) (struct snd_soc_codec*,size_t,int) ;int (* set_bias_level ) (struct snd_soc_codec*,int /*<<< orphan*/ ) ;int num_dai; TYPE_4__* dev; struct i2c_client* control_data; struct wm8993_priv* private_data; TYPE_1__* dai; int /*<<< orphan*/  bias_level; int /*<<< orphan*/  reg_cache_size; TYPE_3__* reg_cache; scalar_t__ hw_write; int /*<<< orphan*/  read; int /*<<< orphan*/  dapm_paths; int /*<<< orphan*/  dapm_widgets; int /*<<< orphan*/  mutex; } ;
struct wm8993_priv {int class_w_users; TYPE_3__ pdata; TYPE_3__* reg_cache; struct snd_soc_codec codec; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_8__ {unsigned int* platform_data; } ;
struct i2c_client {TYPE_4__ dev; } ;
typedef  scalar_t__ hw_write_t ;
struct TYPE_6__ {TYPE_4__* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_3__*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SND_SOC_BIAS_OFF ; 
 int /*<<< orphan*/  SND_SOC_BIAS_STANDBY ; 
 int WM8993_ADC_VU ; 
 int /*<<< orphan*/  WM8993_ADDITIONAL_CONTROL ; 
 int /*<<< orphan*/  WM8993_ANALOGUE_HP_0 ; 
 int /*<<< orphan*/  WM8993_CLOCKING_4 ; 
 int WM8993_DAC_VU ; 
 int WM8993_HPOUT1_AUTO_PU ; 
 int WM8993_JD_SCTHR_MASK ; 
 int WM8993_JD_SCTHR_SHIFT ; 
 int WM8993_JD_THR_MASK ; 
 int WM8993_JD_THR_SHIFT ; 
 int WM8993_LINEOUT1_FB ; 
 int WM8993_LINEOUT1_MODE ; 
 int WM8993_LINEOUT2_FB ; 
 int WM8993_LINEOUT2_MODE ; 
 int /*<<< orphan*/  WM8993_LINE_MIXER1 ; 
 int /*<<< orphan*/  WM8993_LINE_MIXER2 ; 
 int WM8993_MICB1_LVL ; 
 int WM8993_MICB2_LVL ; 
 int /*<<< orphan*/  WM8993_MICBIAS ; 
 int /*<<< orphan*/  WM8993_RIGHT_ADC_DIGITAL_VOLUME ; 
 int /*<<< orphan*/  WM8993_RIGHT_DAC_DIGITAL_VOLUME ; 
 size_t WM8993_SOFTWARE_RESET ; 
 int WM8993_SR_MODE ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 scalar_t__ i2c_master_send ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct wm8993_priv*) ; 
 int /*<<< orphan*/  kfree (struct wm8993_priv*) ; 
 struct wm8993_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,unsigned int*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int snd_soc_register_codec (struct snd_soc_codec*) ; 
 int snd_soc_register_dai (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_soc_update_bits (struct snd_soc_codec*,int /*<<< orphan*/ ,int,int) ; 
 struct snd_soc_codec* wm8993_codec ; 
 TYPE_1__ wm8993_dai ; 
 int /*<<< orphan*/  wm8993_read ; 
 unsigned int wm8993_read_hw (struct snd_soc_codec*,size_t) ; 
 unsigned int* wm8993_reg_defaults ; 
 int wm8993_set_bias_level (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int wm8993_write (struct snd_soc_codec*,size_t,int) ; 

__attribute__((used)) static int wm8993_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct wm8993_priv *wm8993;
	struct snd_soc_codec *codec;
	unsigned int val;
	int ret;

	if (wm8993_codec) {
		dev_err(&i2c->dev, "A WM8993 is already registered\n");
		return -EINVAL;
	}

	wm8993 = kzalloc(sizeof(struct wm8993_priv), GFP_KERNEL);
	if (wm8993 == NULL)
		return -ENOMEM;

	codec = &wm8993->codec;
	if (i2c->dev.platform_data)
		memcpy(&wm8993->pdata, i2c->dev.platform_data,
		       sizeof(wm8993->pdata));

	mutex_init(&codec->mutex);
	INIT_LIST_HEAD(&codec->dapm_widgets);
	INIT_LIST_HEAD(&codec->dapm_paths);

	codec->name = "WM8993";
	codec->read = wm8993_read;
	codec->write = wm8993_write;
	codec->hw_write = (hw_write_t)i2c_master_send;
	codec->reg_cache = wm8993->reg_cache;
	codec->reg_cache_size = ARRAY_SIZE(wm8993->reg_cache);
	codec->bias_level = SND_SOC_BIAS_OFF;
	codec->set_bias_level = wm8993_set_bias_level;
	codec->dai = &wm8993_dai;
	codec->num_dai = 1;
	codec->private_data = wm8993;

	memcpy(wm8993->reg_cache, wm8993_reg_defaults,
	       sizeof(wm8993->reg_cache));

	i2c_set_clientdata(i2c, wm8993);
	codec->control_data = i2c;
	wm8993_codec = codec;

	codec->dev = &i2c->dev;

	val = wm8993_read_hw(codec, WM8993_SOFTWARE_RESET);
	if (val != wm8993_reg_defaults[WM8993_SOFTWARE_RESET]) {
		dev_err(codec->dev, "Invalid ID register value %x\n", val);
		ret = -EINVAL;
		goto err;
	}

	ret = wm8993_write(codec, WM8993_SOFTWARE_RESET, 0xffff);
	if (ret != 0)
		goto err;

	/* By default we're using the output mixers */
	wm8993->class_w_users = 2;

	/* Latch volume update bits and default ZC on */
	snd_soc_update_bits(codec, WM8993_RIGHT_DAC_DIGITAL_VOLUME,
			    WM8993_DAC_VU, WM8993_DAC_VU);
	snd_soc_update_bits(codec, WM8993_RIGHT_ADC_DIGITAL_VOLUME,
			    WM8993_ADC_VU, WM8993_ADC_VU);

	/* Manualy manage the HPOUT sequencing for independent stereo
	 * control. */
	snd_soc_update_bits(codec, WM8993_ANALOGUE_HP_0,
			    WM8993_HPOUT1_AUTO_PU, 0);

	/* Use automatic clock configuration */
	snd_soc_update_bits(codec, WM8993_CLOCKING_4, WM8993_SR_MODE, 0);

	if (!wm8993->pdata.lineout1_diff)
		snd_soc_update_bits(codec, WM8993_LINE_MIXER1,
				    WM8993_LINEOUT1_MODE,
				    WM8993_LINEOUT1_MODE);
	if (!wm8993->pdata.lineout2_diff)
		snd_soc_update_bits(codec, WM8993_LINE_MIXER2,
				    WM8993_LINEOUT2_MODE,
				    WM8993_LINEOUT2_MODE);

	if (wm8993->pdata.lineout1fb)
		snd_soc_update_bits(codec, WM8993_ADDITIONAL_CONTROL,
				    WM8993_LINEOUT1_FB, WM8993_LINEOUT1_FB);

	if (wm8993->pdata.lineout2fb)
		snd_soc_update_bits(codec, WM8993_ADDITIONAL_CONTROL,
				    WM8993_LINEOUT2_FB, WM8993_LINEOUT2_FB);

	/* Apply the microphone bias/detection configuration - the
	 * platform data is directly applicable to the register. */
	snd_soc_update_bits(codec, WM8993_MICBIAS,
			    WM8993_JD_SCTHR_MASK | WM8993_JD_THR_MASK |
			    WM8993_MICB1_LVL | WM8993_MICB2_LVL,
			    wm8993->pdata.jd_scthr << WM8993_JD_SCTHR_SHIFT |
			    wm8993->pdata.jd_thr << WM8993_JD_THR_SHIFT |
			    wm8993->pdata.micbias1_lvl |
			    wm8993->pdata.micbias1_lvl << 1);

	ret = wm8993_set_bias_level(codec, SND_SOC_BIAS_STANDBY);
	if (ret != 0)
		goto err;

	wm8993_dai.dev = codec->dev;

	ret = snd_soc_register_dai(&wm8993_dai);
	if (ret != 0)
		goto err_bias;

	ret = snd_soc_register_codec(codec);

	return 0;

err_bias:
	wm8993_set_bias_level(codec, SND_SOC_BIAS_OFF);
err:
	wm8993_codec = NULL;
	kfree(wm8993);
	return ret;
}