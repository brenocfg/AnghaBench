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
struct vpfe_device {int /*<<< orphan*/  ccdc_addr; int /*<<< orphan*/  video_dev; int /*<<< orphan*/  v4l2_dev; struct vpfe_device* sd; int /*<<< orphan*/  ccdc_irq0; } ;
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 struct vpfe_device* ccdc_cfg ; 
 int /*<<< orphan*/  ccdc_lock ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct vpfe_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vpfe_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vpfe_device* platform_get_drvdata (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpfe_disable_clock (struct vpfe_device*) ; 

__attribute__((used)) static int vpfe_remove(struct platform_device *pdev)
{
	struct vpfe_device *vpfe_dev = platform_get_drvdata(pdev);
	struct resource *res;

	v4l2_info(pdev->dev.driver, "vpfe_remove\n");

	free_irq(vpfe_dev->ccdc_irq0, vpfe_dev);
	kfree(vpfe_dev->sd);
	v4l2_device_unregister(&vpfe_dev->v4l2_dev);
	video_unregister_device(vpfe_dev->video_dev);
	mutex_lock(&ccdc_lock);
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(res->start, res->end - res->start + 1);
	iounmap(ccdc_cfg->ccdc_addr);
	mutex_unlock(&ccdc_lock);
	vpfe_disable_clock(vpfe_dev);
	kfree(vpfe_dev);
	kfree(ccdc_cfg);
	return 0;
}