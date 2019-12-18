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
struct snd_soc_codec {scalar_t__ suspend_bias_level; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {struct snd_soc_codec* codec; } ;

/* Variables and functions */
 scalar_t__ SND_SOC_BIAS_ON ; 
 scalar_t__ SND_SOC_BIAS_STANDBY ; 
 struct snd_soc_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  wm8350_set_bias_level (struct snd_soc_codec*,scalar_t__) ; 

__attribute__((used)) static int wm8350_resume(struct platform_device *pdev)
{
	struct snd_soc_device *socdev = platform_get_drvdata(pdev);
	struct snd_soc_codec *codec = socdev->card->codec;

	wm8350_set_bias_level(codec, SND_SOC_BIAS_STANDBY);

	if (codec->suspend_bias_level == SND_SOC_BIAS_ON)
		wm8350_set_bias_level(codec, SND_SOC_BIAS_ON);

	return 0;
}