#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_soc_device {struct snd_soc_card* card; } ;
struct snd_soc_card {int /*<<< orphan*/ * dev; struct snd_soc_device* socdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct snd_soc_device* platform_get_drvdata (struct platform_device*) ; 
 int snd_soc_register_card (struct snd_soc_card*) ; 

__attribute__((used)) static int soc_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct snd_soc_device *socdev = platform_get_drvdata(pdev);
	struct snd_soc_card *card = socdev->card;

	/* Bodge while we push things out of socdev */
	card->socdev = socdev;

	/* Bodge while we unpick instantiation */
	card->dev = &pdev->dev;
	ret = snd_soc_register_card(card);
	if (ret != 0) {
		dev_err(&pdev->dev, "Failed to register card\n");
		return ret;
	}

	return 0;
}