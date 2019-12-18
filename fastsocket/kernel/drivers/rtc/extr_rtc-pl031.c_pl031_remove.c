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
struct pl031_local {int /*<<< orphan*/  base; int /*<<< orphan*/  rtc; } ;
struct amba_device {int /*<<< orphan*/ * irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  amba_release_regions (struct amba_device*) ; 
 int /*<<< orphan*/  amba_set_drvdata (struct amba_device*,int /*<<< orphan*/ *) ; 
 struct pl031_local* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pl031_local*) ; 
 int /*<<< orphan*/  rtc_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pl031_remove(struct amba_device *adev)
{
	struct pl031_local *ldata = dev_get_drvdata(&adev->dev);

	amba_set_drvdata(adev, NULL);
	free_irq(adev->irq[0], ldata->rtc);
	rtc_device_unregister(ldata->rtc);
	iounmap(ldata->base);
	kfree(ldata);
	amba_release_regions(adev);

	return 0;
}