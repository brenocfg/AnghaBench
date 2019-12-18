#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct platform_device {int dummy; } ;
struct davinci_mcbsp_dev {int /*<<< orphan*/ * clk; } ;
struct TYPE_3__ {struct davinci_mcbsp_dev* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 
 TYPE_1__ davinci_i2s_dai ; 
 int /*<<< orphan*/  kfree (struct davinci_mcbsp_dev*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  snd_soc_unregister_dai (TYPE_1__*) ; 

__attribute__((used)) static int davinci_i2s_remove(struct platform_device *pdev)
{
	struct davinci_mcbsp_dev *dev = davinci_i2s_dai.private_data;
	struct resource *mem;

	snd_soc_unregister_dai(&davinci_i2s_dai);
	clk_disable(dev->clk);
	clk_put(dev->clk);
	dev->clk = NULL;
	kfree(dev);
	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(mem->start, (mem->end - mem->start) + 1);

	return 0;
}