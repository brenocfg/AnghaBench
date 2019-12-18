#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct snd_soc_codec {char* name; int (* read ) (struct snd_soc_codec*,int /*<<< orphan*/ ) ;int num_dai; int reg_cache_size; int /*<<< orphan*/  delayed_work; int /*<<< orphan*/  dev; TYPE_1__** reg_cache; struct wm8753_priv* private_data; TYPE_1__* dai; int /*<<< orphan*/  (* set_bias_level ) (struct snd_soc_codec*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  bias_level; int /*<<< orphan*/  (* write ) (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  owner; int /*<<< orphan*/  dapm_paths; int /*<<< orphan*/  dapm_widgets; int /*<<< orphan*/  mutex; } ;
struct wm8753_priv {TYPE_1__* reg_cache; struct snd_soc_codec codec; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SND_SOC_BIAS_PREPARE ; 
 int /*<<< orphan*/  SND_SOC_BIAS_STANDBY ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  WM8753_LADC ; 
 int /*<<< orphan*/  WM8753_LDAC ; 
 int /*<<< orphan*/  WM8753_LINVOL ; 
 int /*<<< orphan*/  WM8753_LOUT1V ; 
 int /*<<< orphan*/  WM8753_LOUT2V ; 
 int /*<<< orphan*/  WM8753_RADC ; 
 int /*<<< orphan*/  WM8753_RDAC ; 
 int /*<<< orphan*/  WM8753_RINVOL ; 
 int /*<<< orphan*/  WM8753_ROUT1V ; 
 int /*<<< orphan*/  WM8753_ROUT2V ; 
 int /*<<< orphan*/  caps_charge ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kfree (struct wm8753_priv*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snd_soc_register_codec (struct snd_soc_codec*) ; 
 int snd_soc_register_dais (TYPE_1__*,int) ; 
 int /*<<< orphan*/  snd_soc_unregister_codec (struct snd_soc_codec*) ; 
 struct snd_soc_codec* wm8753_codec ; 
 TYPE_1__* wm8753_dai ; 
 int wm8753_read_reg_cache (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8753_reg ; 
 int wm8753_reset (struct snd_soc_codec*) ; 
 int /*<<< orphan*/  wm8753_set_bias_level (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8753_work ; 
 int /*<<< orphan*/  wm8753_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8753_register(struct wm8753_priv *wm8753)
{
	int ret, i;
	struct snd_soc_codec *codec = &wm8753->codec;
	u16 reg;

	if (wm8753_codec) {
		dev_err(codec->dev, "Multiple WM8753 devices not supported\n");
		ret = -EINVAL;
		goto err;
	}

	mutex_init(&codec->mutex);
	INIT_LIST_HEAD(&codec->dapm_widgets);
	INIT_LIST_HEAD(&codec->dapm_paths);

	codec->name = "WM8753";
	codec->owner = THIS_MODULE;
	codec->read = wm8753_read_reg_cache;
	codec->write = wm8753_write;
	codec->bias_level = SND_SOC_BIAS_STANDBY;
	codec->set_bias_level = wm8753_set_bias_level;
	codec->dai = wm8753_dai;
	codec->num_dai = 2;
	codec->reg_cache_size = ARRAY_SIZE(wm8753->reg_cache) + 1;
	codec->reg_cache = &wm8753->reg_cache;
	codec->private_data = wm8753;

	memcpy(codec->reg_cache, wm8753_reg, sizeof(wm8753->reg_cache));
	INIT_DELAYED_WORK(&codec->delayed_work, wm8753_work);

	ret = wm8753_reset(codec);
	if (ret < 0) {
		dev_err(codec->dev, "Failed to issue reset\n");
		goto err;
	}

	/* charge output caps */
	wm8753_set_bias_level(codec, SND_SOC_BIAS_PREPARE);
	schedule_delayed_work(&codec->delayed_work,
			      msecs_to_jiffies(caps_charge));

	/* set the update bits */
	reg = wm8753_read_reg_cache(codec, WM8753_LDAC);
	wm8753_write(codec, WM8753_LDAC, reg | 0x0100);
	reg = wm8753_read_reg_cache(codec, WM8753_RDAC);
	wm8753_write(codec, WM8753_RDAC, reg | 0x0100);
	reg = wm8753_read_reg_cache(codec, WM8753_LADC);
	wm8753_write(codec, WM8753_LADC, reg | 0x0100);
	reg = wm8753_read_reg_cache(codec, WM8753_RADC);
	wm8753_write(codec, WM8753_RADC, reg | 0x0100);
	reg = wm8753_read_reg_cache(codec, WM8753_LOUT1V);
	wm8753_write(codec, WM8753_LOUT1V, reg | 0x0100);
	reg = wm8753_read_reg_cache(codec, WM8753_ROUT1V);
	wm8753_write(codec, WM8753_ROUT1V, reg | 0x0100);
	reg = wm8753_read_reg_cache(codec, WM8753_LOUT2V);
	wm8753_write(codec, WM8753_LOUT2V, reg | 0x0100);
	reg = wm8753_read_reg_cache(codec, WM8753_ROUT2V);
	wm8753_write(codec, WM8753_ROUT2V, reg | 0x0100);
	reg = wm8753_read_reg_cache(codec, WM8753_LINVOL);
	wm8753_write(codec, WM8753_LINVOL, reg | 0x0100);
	reg = wm8753_read_reg_cache(codec, WM8753_RINVOL);
	wm8753_write(codec, WM8753_RINVOL, reg | 0x0100);

	wm8753_codec = codec;

	for (i = 0; i < ARRAY_SIZE(wm8753_dai); i++)
		wm8753_dai[i].dev = codec->dev;

	ret = snd_soc_register_codec(codec);
	if (ret != 0) {
		dev_err(codec->dev, "Failed to register codec: %d\n", ret);
		goto err;
	}

	ret = snd_soc_register_dais(&wm8753_dai[0], ARRAY_SIZE(wm8753_dai));
	if (ret != 0) {
		dev_err(codec->dev, "Failed to register DAIs: %d\n", ret);
		goto err_codec;
	}

	return 0;

err_codec:
	run_delayed_work(&codec->delayed_work);
	snd_soc_unregister_codec(codec);
err:
	kfree(wm8753);
	return ret;
}