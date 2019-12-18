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
struct snd_soc_codec {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct snd_soc_codec* codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  SNDRV_DEFAULT_IDX1 ; 
 int /*<<< orphan*/  SNDRV_DEFAULT_STR1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct snd_soc_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  snd_soc_add_controls (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_free (struct snd_soc_device*) ; 
 int /*<<< orphan*/  snd_soc_free_pcms (struct snd_soc_device*) ; 
 int snd_soc_init_card (struct snd_soc_device*) ; 
 int snd_soc_new_pcms (struct snd_soc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8900_add_widgets (struct snd_soc_codec*) ; 
 struct snd_soc_codec* wm8900_codec ; 
 int /*<<< orphan*/  wm8900_snd_controls ; 

__attribute__((used)) static int wm8900_probe(struct platform_device *pdev)
{
	struct snd_soc_device *socdev = platform_get_drvdata(pdev);
	struct snd_soc_codec *codec;
	int ret = 0;

	if (!wm8900_codec) {
		dev_err(&pdev->dev, "I2C client not yet instantiated\n");
		return -ENODEV;
	}

	codec = wm8900_codec;
	socdev->card->codec = codec;

	/* Register pcms */
	ret = snd_soc_new_pcms(socdev, SNDRV_DEFAULT_IDX1, SNDRV_DEFAULT_STR1);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to register new PCMs\n");
		goto pcm_err;
	}

	snd_soc_add_controls(codec, wm8900_snd_controls,
				ARRAY_SIZE(wm8900_snd_controls));
	wm8900_add_widgets(codec);

	ret = snd_soc_init_card(socdev);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to register card\n");
		goto card_err;
	}

	return ret;

card_err:
	snd_soc_free_pcms(socdev);
	snd_soc_dapm_free(socdev);
pcm_err:
	return ret;
}