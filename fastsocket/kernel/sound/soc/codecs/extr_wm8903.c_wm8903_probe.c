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
struct snd_soc_device {TYPE_1__* card; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNDRV_DEFAULT_IDX1 ; 
 int /*<<< orphan*/  SNDRV_DEFAULT_STR1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct snd_soc_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  snd_soc_add_controls (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_free (struct snd_soc_device*) ; 
 int /*<<< orphan*/  snd_soc_free_pcms (struct snd_soc_device*) ; 
 int snd_soc_init_card (struct snd_soc_device*) ; 
 int snd_soc_new_pcms (struct snd_soc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8903_add_widgets (scalar_t__) ; 
 scalar_t__ wm8903_codec ; 
 int /*<<< orphan*/  wm8903_snd_controls ; 

__attribute__((used)) static int wm8903_probe(struct platform_device *pdev)
{
	struct snd_soc_device *socdev = platform_get_drvdata(pdev);
	int ret = 0;

	if (!wm8903_codec) {
		dev_err(&pdev->dev, "I2C device not yet probed\n");
		goto err;
	}

	socdev->card->codec = wm8903_codec;

	/* register pcms */
	ret = snd_soc_new_pcms(socdev, SNDRV_DEFAULT_IDX1, SNDRV_DEFAULT_STR1);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to create pcms\n");
		goto err;
	}

	snd_soc_add_controls(socdev->card->codec, wm8903_snd_controls,
				ARRAY_SIZE(wm8903_snd_controls));
	wm8903_add_widgets(socdev->card->codec);

	ret = snd_soc_init_card(socdev);
	if (ret < 0) {
		dev_err(&pdev->dev, "wm8903: failed to register card\n");
		goto card_err;
	}

	return ret;

card_err:
	snd_soc_free_pcms(socdev);
	snd_soc_dapm_free(socdev);
err:
	return ret;
}