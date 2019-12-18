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
typedef  int u16 ;
struct snd_soc_device {TYPE_1__* card; } ;
struct snd_soc_codec {int dummy; } ;
struct platform_device {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
struct TYPE_2__ {struct snd_soc_codec* codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_EXTENDED_MID ; 
 int /*<<< orphan*/  AC97_EXTENDED_MSTATUS ; 
 int /*<<< orphan*/  AC97_POWERDOWN ; 
 int ac97_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ac97_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int wm9713_soc_suspend(struct platform_device *pdev,
	pm_message_t state)
{
	struct snd_soc_device *socdev = platform_get_drvdata(pdev);
	struct snd_soc_codec *codec = socdev->card->codec;
	u16 reg;

	/* Disable everything except touchpanel - that will be handled
	 * by the touch driver and left disabled if touch is not in
	 * use. */
	reg = ac97_read(codec, AC97_EXTENDED_MID);
	ac97_write(codec, AC97_EXTENDED_MID, reg | 0x7fff);
	ac97_write(codec, AC97_EXTENDED_MSTATUS, 0xffff);
	ac97_write(codec, AC97_POWERDOWN, 0x6f00);
	ac97_write(codec, AC97_POWERDOWN, 0xffff);

	return 0;
}