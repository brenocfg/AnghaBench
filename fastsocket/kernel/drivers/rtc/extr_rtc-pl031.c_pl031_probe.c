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
struct pl031_local {int /*<<< orphan*/  base; int /*<<< orphan*/  rtc; } ;
struct amba_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;
struct amba_device {int /*<<< orphan*/ * irq; int /*<<< orphan*/  dev; TYPE_1__ res; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_DISABLED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  amba_release_regions (struct amba_device*) ; 
 int amba_request_regions (struct amba_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amba_set_drvdata (struct amba_device*,struct pl031_local*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pl031_local*) ; 
 struct pl031_local* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl031_interrupt ; 
 int /*<<< orphan*/  pl031_ops ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 
 int /*<<< orphan*/  rtc_device_register (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pl031_probe(struct amba_device *adev, struct amba_id *id)
{
	int ret;
	struct pl031_local *ldata;

	ret = amba_request_regions(adev, NULL);
	if (ret)
		goto err_req;

	ldata = kmalloc(sizeof(struct pl031_local), GFP_KERNEL);
	if (!ldata) {
		ret = -ENOMEM;
		goto out;
	}

	ldata->base = ioremap(adev->res.start, resource_size(&adev->res));
	if (!ldata->base) {
		ret = -ENOMEM;
		goto out_no_remap;
	}

	amba_set_drvdata(adev, ldata);

	if (request_irq(adev->irq[0], pl031_interrupt, IRQF_DISABLED,
			"rtc-pl031", ldata->rtc)) {
		ret = -EIO;
		goto out_no_irq;
	}

	ldata->rtc = rtc_device_register("pl031", &adev->dev, &pl031_ops,
					 THIS_MODULE);
	if (IS_ERR(ldata->rtc)) {
		ret = PTR_ERR(ldata->rtc);
		goto out_no_rtc;
	}

	return 0;

out_no_rtc:
	free_irq(adev->irq[0], ldata->rtc);
out_no_irq:
	iounmap(ldata->base);
	amba_set_drvdata(adev, NULL);
out_no_remap:
	kfree(ldata);
out:
	amba_release_regions(adev);
err_req:
	return ret;
}