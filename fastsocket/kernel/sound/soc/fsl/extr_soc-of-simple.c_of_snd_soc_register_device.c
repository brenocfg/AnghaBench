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
struct TYPE_3__ {struct of_snd_soc_device* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_4__ {TYPE_1__* dev; int /*<<< orphan*/  codec_data; } ;
struct of_snd_soc_device {TYPE_2__ device; int /*<<< orphan*/  id; int /*<<< orphan*/  platform_node; } ;

/* Variables and functions */
 int platform_device_add (struct platform_device*) ; 
 struct platform_device* platform_device_alloc (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void of_snd_soc_register_device(struct of_snd_soc_device *of_soc)
{
	struct platform_device *pdev;
	int rc;

	/* Only register the device if both the codec and platform have
	 * been registered */
	if ((!of_soc->device.codec_data) || (!of_soc->platform_node))
		return;

	pr_info("platform<-->codec match achieved; registering machine\n");

	pdev = platform_device_alloc("soc-audio", of_soc->id);
	if (!pdev) {
		pr_err("of_soc: platform_device_alloc() failed\n");
		return;
	}

	pdev->dev.platform_data = of_soc;
	platform_set_drvdata(pdev, &of_soc->device);
	of_soc->device.dev = &pdev->dev;

	/* The ASoC device is complete; register it */
	rc = platform_device_add(pdev);
	if (rc) {
		pr_err("of_soc: platform_device_add() failed\n");
		return;
	}

}