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
struct TYPE_4__ {scalar_t__ num_retune_configs; int /*<<< orphan*/  lineout2_diff; int /*<<< orphan*/  lineout1_diff; } ;
struct wm8993_priv {TYPE_2__ pdata; } ;
struct snd_soc_device {TYPE_1__* card; } ;
struct snd_soc_codec {int /*<<< orphan*/ * dev; struct wm8993_priv* private_data; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {void* codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNDRV_DEFAULT_IDX1 ; 
 int /*<<< orphan*/  SNDRV_DEFAULT_STR1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct snd_soc_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  routes ; 
 int /*<<< orphan*/  snd_soc_add_controls (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_free (struct snd_soc_device*) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_widgets (struct snd_soc_codec*) ; 
 int /*<<< orphan*/  snd_soc_free_pcms (struct snd_soc_device*) ; 
 int snd_soc_init_card (struct snd_soc_device*) ; 
 int snd_soc_new_pcms (struct snd_soc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* wm8993_codec ; 
 int /*<<< orphan*/  wm8993_dapm_widgets ; 
 int /*<<< orphan*/  wm8993_eq_controls ; 
 int /*<<< orphan*/  wm8993_snd_controls ; 
 int /*<<< orphan*/  wm_hubs_add_analogue_controls (struct snd_soc_codec*) ; 
 int /*<<< orphan*/  wm_hubs_add_analogue_routes (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8993_probe(struct platform_device *pdev)
{
	struct snd_soc_device *socdev = platform_get_drvdata(pdev);
	struct snd_soc_codec *codec;
	struct wm8993_priv *wm8993;
	int ret = 0;

	if (!wm8993_codec) {
		dev_err(&pdev->dev, "I2C device not yet probed\n");
		goto err;
	}

	socdev->card->codec = wm8993_codec;
	codec = wm8993_codec;
	wm8993 = codec->private_data;

	ret = snd_soc_new_pcms(socdev, SNDRV_DEFAULT_IDX1, SNDRV_DEFAULT_STR1);
	if (ret < 0) {
		dev_err(codec->dev, "failed to create pcms\n");
		goto err;
	}

	snd_soc_add_controls(codec, wm8993_snd_controls,
			     ARRAY_SIZE(wm8993_snd_controls));
	if (wm8993->pdata.num_retune_configs != 0) {
		dev_dbg(codec->dev, "Using ReTune Mobile\n");
	} else {
		dev_dbg(codec->dev, "No ReTune Mobile, using normal EQ\n");
		snd_soc_add_controls(codec, wm8993_eq_controls,
				     ARRAY_SIZE(wm8993_eq_controls));
	}

	snd_soc_dapm_new_controls(codec, wm8993_dapm_widgets,
				  ARRAY_SIZE(wm8993_dapm_widgets));
	wm_hubs_add_analogue_controls(codec);

	snd_soc_dapm_add_routes(codec, routes, ARRAY_SIZE(routes));
	wm_hubs_add_analogue_routes(codec, wm8993->pdata.lineout1_diff,
				    wm8993->pdata.lineout2_diff);

	snd_soc_dapm_new_widgets(codec);

	ret = snd_soc_init_card(socdev);
	if (ret < 0) {
		dev_err(codec->dev, "failed to register card\n");
		goto card_err;
	}

	return ret;

card_err:
	snd_soc_free_pcms(socdev);
	snd_soc_dapm_free(socdev);
err:
	return ret;
}