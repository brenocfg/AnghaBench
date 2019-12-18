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
struct pl030_rtc {scalar_t__ base; int /*<<< orphan*/  rtc; } ;
struct amba_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;
struct amba_device {int /*<<< orphan*/ * irq; int /*<<< orphan*/  dev; TYPE_1__ res; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_DISABLED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ RTC_CR ; 
 scalar_t__ RTC_EOI ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  amba_release_regions (struct amba_device*) ; 
 int amba_request_regions (struct amba_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amba_set_drvdata (struct amba_device*,struct pl030_rtc*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct pl030_rtc*) ; 
 scalar_t__ ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct pl030_rtc*) ; 
 struct pl030_rtc* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl030_interrupt ; 
 int /*<<< orphan*/  pl030_ops ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct pl030_rtc*) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 
 int /*<<< orphan*/  rtc_device_register (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pl030_probe(struct amba_device *dev, struct amba_id *id)
{
	struct pl030_rtc *rtc;
	int ret;

	ret = amba_request_regions(dev, NULL);
	if (ret)
		goto err_req;

	rtc = kmalloc(sizeof(*rtc), GFP_KERNEL);
	if (!rtc) {
		ret = -ENOMEM;
		goto err_rtc;
	}

	rtc->base = ioremap(dev->res.start, resource_size(&dev->res));
	if (!rtc->base) {
		ret = -ENOMEM;
		goto err_map;
	}

	__raw_writel(0, rtc->base + RTC_CR);
	__raw_writel(0, rtc->base + RTC_EOI);

	amba_set_drvdata(dev, rtc);

	ret = request_irq(dev->irq[0], pl030_interrupt, IRQF_DISABLED,
			  "rtc-pl030", rtc);
	if (ret)
		goto err_irq;

	rtc->rtc = rtc_device_register("pl030", &dev->dev, &pl030_ops,
				       THIS_MODULE);
	if (IS_ERR(rtc->rtc)) {
		ret = PTR_ERR(rtc->rtc);
		goto err_reg;
	}

	return 0;

 err_reg:
	free_irq(dev->irq[0], rtc);
 err_irq:
	iounmap(rtc->base);
 err_map:
	kfree(rtc);
 err_rtc:
	amba_release_regions(dev);
 err_req:
	return ret;
}