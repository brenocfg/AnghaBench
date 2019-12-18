#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct TYPE_4__ {struct mv_xor_platform_shared_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mv_xor_shared_private {void* xor_high_base; void* xor_base; } ;
struct mv_xor_platform_shared_data {int /*<<< orphan*/ * dram; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,TYPE_1__*,char*) ; 
 void* devm_ioremap (TYPE_1__*,scalar_t__,scalar_t__) ; 
 struct mv_xor_shared_private* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_xor_conf_mbus_windows (struct mv_xor_shared_private*,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mv_xor_shared_private*) ; 

__attribute__((used)) static int mv_xor_shared_probe(struct platform_device *pdev)
{
	struct mv_xor_platform_shared_data *msd = pdev->dev.platform_data;
	struct mv_xor_shared_private *msp;
	struct resource *res;

	dev_printk(KERN_NOTICE, &pdev->dev, "Marvell shared XOR driver\n");

	msp = devm_kzalloc(&pdev->dev, sizeof(*msp), GFP_KERNEL);
	if (!msp)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENODEV;

	msp->xor_base = devm_ioremap(&pdev->dev, res->start,
				     res->end - res->start + 1);
	if (!msp->xor_base)
		return -EBUSY;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!res)
		return -ENODEV;

	msp->xor_high_base = devm_ioremap(&pdev->dev, res->start,
					  res->end - res->start + 1);
	if (!msp->xor_high_base)
		return -EBUSY;

	platform_set_drvdata(pdev, msp);

	/*
	 * (Re-)program MBUS remapping windows if we are asked to.
	 */
	if (msd != NULL && msd->dram != NULL)
		mv_xor_conf_mbus_windows(msp, msd->dram);

	return 0;
}