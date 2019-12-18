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
struct snd_soc_codec {int dummy; } ;
struct TYPE_2__ {struct snd_soc_codec* codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  dapm_free_widgets (struct snd_soc_codec*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sys_remove (int /*<<< orphan*/ ) ; 

void snd_soc_dapm_free(struct snd_soc_device *socdev)
{
	struct snd_soc_codec *codec = socdev->card->codec;

	snd_soc_dapm_sys_remove(socdev->dev);
	dapm_free_widgets(codec);
}