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
struct t7l66xb_platform_data {int (* disable ) (struct platform_device*) ;} ;
struct t7l66xb {int /*<<< orphan*/  rscr; int /*<<< orphan*/  scr; int /*<<< orphan*/  clk48m; } ;
struct TYPE_2__ {struct t7l66xb_platform_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct t7l66xb*) ; 
 int /*<<< orphan*/  mfd_remove_devices (TYPE_1__*) ; 
 struct t7l66xb* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ *) ; 
 int stub1 (struct platform_device*) ; 
 int /*<<< orphan*/  t7l66xb_detach_irq (struct platform_device*) ; 

__attribute__((used)) static int t7l66xb_remove(struct platform_device *dev)
{
	struct t7l66xb_platform_data *pdata = dev->dev.platform_data;
	struct t7l66xb *t7l66xb = platform_get_drvdata(dev);
	int ret;

	ret = pdata->disable(dev);
	clk_disable(t7l66xb->clk48m);
	clk_put(t7l66xb->clk48m);
	t7l66xb_detach_irq(dev);
	iounmap(t7l66xb->scr);
	release_resource(&t7l66xb->rscr);
	mfd_remove_devices(&dev->dev);
	platform_set_drvdata(dev, NULL);
	kfree(t7l66xb);

	return ret;

}