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
struct snd_soc_codec {int /*<<< orphan*/  dev; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {struct snd_soc_codec* codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNDRV_DEFAULT_IDX1 ; 
 int /*<<< orphan*/  SNDRV_DEFAULT_STR1 ; 
 struct snd_soc_codec* cs4270_codec ; 
 int /*<<< orphan*/  cs4270_snd_controls ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct snd_soc_device* platform_get_drvdata (struct platform_device*) ; 
 int snd_soc_add_controls (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_free_pcms (struct snd_soc_device*) ; 
 int snd_soc_init_card (struct snd_soc_device*) ; 
 int snd_soc_new_pcms (struct snd_soc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs4270_probe(struct platform_device *pdev)
{
	struct snd_soc_device *socdev = platform_get_drvdata(pdev);
	struct snd_soc_codec *codec = cs4270_codec;
	int ret;

	/* Connect the codec to the socdev.  snd_soc_new_pcms() needs this. */
	socdev->card->codec = codec;

	/* Register PCMs */
	ret = snd_soc_new_pcms(socdev, SNDRV_DEFAULT_IDX1, SNDRV_DEFAULT_STR1);
	if (ret < 0) {
		dev_err(codec->dev, "failed to create pcms\n");
		return ret;
	}

	/* Add the non-DAPM controls */
	ret = snd_soc_add_controls(codec, cs4270_snd_controls,
				ARRAY_SIZE(cs4270_snd_controls));
	if (ret < 0) {
		dev_err(codec->dev, "failed to add controls\n");
		goto error_free_pcms;
	}

	/* And finally, register the socdev */
	ret = snd_soc_init_card(socdev);
	if (ret < 0) {
		dev_err(codec->dev, "failed to register card\n");
		goto error_free_pcms;
	}

	return 0;

error_free_pcms:
	snd_soc_free_pcms(socdev);

	return ret;
}