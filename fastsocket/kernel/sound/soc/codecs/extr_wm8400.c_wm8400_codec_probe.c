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
struct snd_soc_codec {char* name; int (* read ) (struct snd_soc_codec*,int /*<<< orphan*/ ) ;int num_dai; int /*<<< orphan*/  dapm_paths; int /*<<< orphan*/  dapm_widgets; int /*<<< orphan*/  mutex; int /*<<< orphan*/  reg_cache_size; TYPE_2__* dai; int /*<<< orphan*/  set_bias_level; int /*<<< orphan*/  bias_level; int /*<<< orphan*/  (* write ) (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  owner; int /*<<< orphan*/ * dev; void* control_data; struct wm8400_priv* private_data; } ;
struct wm8400_priv {int /*<<< orphan*/  work; TYPE_1__* wm8400; struct snd_soc_codec codec; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SND_SOC_BIAS_OFF ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int WM8400_CODEC_ENA ; 
 int WM8400_IPVU ; 
 int /*<<< orphan*/  WM8400_LEFT_LINE_INPUT_1_2_VOLUME ; 
 int /*<<< orphan*/  WM8400_LEFT_OUTPUT_VOLUME ; 
 int /*<<< orphan*/  WM8400_POWER_MANAGEMENT_1 ; 
 int /*<<< orphan*/  WM8400_REGISTER_COUNT ; 
 int /*<<< orphan*/  WM8400_RIGHT_LINE_INPUT_1_2_VOLUME ; 
 int /*<<< orphan*/  WM8400_RIGHT_OUTPUT_VOLUME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 void* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct wm8400_priv*) ; 
 struct wm8400_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * power ; 
 int /*<<< orphan*/  regulator_bulk_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int regulator_bulk_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct snd_soc_codec* wm8400_codec ; 
 int /*<<< orphan*/  wm8400_codec_reset (struct snd_soc_codec*) ; 
 TYPE_2__ wm8400_dai ; 
 int /*<<< orphan*/  wm8400_probe_deferred ; 
 int wm8400_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8400_set_bias_level ; 
 int /*<<< orphan*/  wm8400_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8400_codec_probe(struct platform_device *dev)
{
	struct wm8400_priv *priv;
	int ret;
	u16 reg;
	struct snd_soc_codec *codec;

	priv = kzalloc(sizeof(struct wm8400_priv), GFP_KERNEL);
	if (priv == NULL)
		return -ENOMEM;

	codec = &priv->codec;
	codec->private_data = priv;
	codec->control_data = dev_get_drvdata(&dev->dev);
	priv->wm8400 = dev_get_drvdata(&dev->dev);

	ret = regulator_bulk_get(priv->wm8400->dev,
				 ARRAY_SIZE(power), &power[0]);
	if (ret != 0) {
		dev_err(&dev->dev, "Failed to get regulators: %d\n", ret);
	        goto err;
	}

	codec->dev = &dev->dev;
	wm8400_dai.dev = &dev->dev;

	codec->name = "WM8400";
	codec->owner = THIS_MODULE;
	codec->read = wm8400_read;
	codec->write = wm8400_write;
	codec->bias_level = SND_SOC_BIAS_OFF;
	codec->set_bias_level = wm8400_set_bias_level;
	codec->dai = &wm8400_dai;
	codec->num_dai = 1;
	codec->reg_cache_size = WM8400_REGISTER_COUNT;
	mutex_init(&codec->mutex);
	INIT_LIST_HEAD(&codec->dapm_widgets);
	INIT_LIST_HEAD(&codec->dapm_paths);
	INIT_WORK(&priv->work, wm8400_probe_deferred);

	wm8400_codec_reset(codec);

	reg = wm8400_read(codec, WM8400_POWER_MANAGEMENT_1);
	wm8400_write(codec, WM8400_POWER_MANAGEMENT_1, reg | WM8400_CODEC_ENA);

	/* Latch volume update bits */
	reg = wm8400_read(codec, WM8400_LEFT_LINE_INPUT_1_2_VOLUME);
	wm8400_write(codec, WM8400_LEFT_LINE_INPUT_1_2_VOLUME,
		     reg & WM8400_IPVU);
	reg = wm8400_read(codec, WM8400_RIGHT_LINE_INPUT_1_2_VOLUME);
	wm8400_write(codec, WM8400_RIGHT_LINE_INPUT_1_2_VOLUME,
		     reg & WM8400_IPVU);

	wm8400_write(codec, WM8400_LEFT_OUTPUT_VOLUME, 0x50 | (1<<8));
	wm8400_write(codec, WM8400_RIGHT_OUTPUT_VOLUME, 0x50 | (1<<8));

	wm8400_codec = codec;

	if (!schedule_work(&priv->work)) {
		ret = -EINVAL;
		goto err_regulator;
	}

	return 0;

err_regulator:
	wm8400_codec = NULL;
	regulator_bulk_free(ARRAY_SIZE(power), power);
err:
	kfree(priv);
	return ret;
}