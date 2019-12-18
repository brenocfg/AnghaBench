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
struct snd_soc_device {int /*<<< orphan*/  dev; TYPE_1__* card; } ;
struct snd_soc_dai {scalar_t__ ac97_control; } ;
struct snd_soc_codec {int num_dai; int /*<<< orphan*/  mutex; scalar_t__ card; int /*<<< orphan*/  name; scalar_t__ ac97; struct snd_soc_dai* dai; } ;
struct TYPE_2__ {struct snd_soc_codec* codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_codec_reg ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_card_free (scalar_t__) ; 
 int /*<<< orphan*/  soc_ac97_dev_unregister (struct snd_soc_codec*) ; 
 int /*<<< orphan*/  soc_cleanup_codec_debugfs (struct snd_soc_codec*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

void snd_soc_free_pcms(struct snd_soc_device *socdev)
{
	struct snd_soc_codec *codec = socdev->card->codec;
#ifdef CONFIG_SND_SOC_AC97_BUS
	struct snd_soc_dai *codec_dai;
	int i;
#endif

	mutex_lock(&codec->mutex);
	soc_cleanup_codec_debugfs(codec);
#ifdef CONFIG_SND_SOC_AC97_BUS
	for (i = 0; i < codec->num_dai; i++) {
		codec_dai = &codec->dai[i];
		if (codec_dai->ac97_control && codec->ac97 &&
		    strcmp(codec->name, "AC97") != 0) {
			soc_ac97_dev_unregister(codec);
			goto free_card;
		}
	}
free_card:
#endif

	if (codec->card)
		snd_card_free(codec->card);
	device_remove_file(socdev->dev, &dev_attr_codec_reg);
	mutex_unlock(&codec->mutex);
}