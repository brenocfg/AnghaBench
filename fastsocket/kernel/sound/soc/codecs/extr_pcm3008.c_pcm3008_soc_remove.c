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
struct snd_soc_device {TYPE_1__* card; struct pcm3008_setup_data* codec_data; } ;
struct snd_soc_codec {int dummy; } ;
struct platform_device {int dummy; } ;
struct pcm3008_setup_data {int dummy; } ;
struct TYPE_2__ {struct snd_soc_codec* codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_soc_codec*) ; 
 int /*<<< orphan*/  pcm3008_gpio_free (struct pcm3008_setup_data*) ; 
 struct snd_soc_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  snd_soc_free_pcms (struct snd_soc_device*) ; 

__attribute__((used)) static int pcm3008_soc_remove(struct platform_device *pdev)
{
	struct snd_soc_device *socdev = platform_get_drvdata(pdev);
	struct snd_soc_codec *codec = socdev->card->codec;
	struct pcm3008_setup_data *setup = socdev->codec_data;

	if (!codec)
		return 0;

	pcm3008_gpio_free(setup);
	snd_soc_free_pcms(socdev);
	kfree(socdev->card->codec);

	return 0;
}