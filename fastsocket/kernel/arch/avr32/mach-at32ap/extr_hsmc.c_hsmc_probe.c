#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct hsmc {int dummy; } ;
struct clk {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  regs; struct clk* mck; struct clk* pclk; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  clk_disable (struct clk*) ; 
 int /*<<< orphan*/  clk_enable (struct clk*) ; 
 struct clk* clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned long) ; 
 TYPE_1__* hsmc ; 
 int /*<<< orphan*/  ioremap (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_1__*) ; 

__attribute__((used)) static int hsmc_probe(struct platform_device *pdev)
{
	struct resource *regs;
	struct clk *pclk, *mck;
	int ret;

	if (hsmc)
		return -EBUSY;

	regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!regs)
		return -ENXIO;
	pclk = clk_get(&pdev->dev, "pclk");
	if (IS_ERR(pclk))
		return PTR_ERR(pclk);
	mck = clk_get(&pdev->dev, "mck");
	if (IS_ERR(mck)) {
		ret = PTR_ERR(mck);
		goto out_put_pclk;
	}

	ret = -ENOMEM;
	hsmc = kzalloc(sizeof(struct hsmc), GFP_KERNEL);
	if (!hsmc)
		goto out_put_clocks;

	clk_enable(pclk);
	clk_enable(mck);

	hsmc->pclk = pclk;
	hsmc->mck = mck;
	hsmc->regs = ioremap(regs->start, regs->end - regs->start + 1);
	if (!hsmc->regs)
		goto out_disable_clocks;

	dev_info(&pdev->dev, "Atmel Static Memory Controller at 0x%08lx\n",
		 (unsigned long)regs->start);

	platform_set_drvdata(pdev, hsmc);

	return 0;

out_disable_clocks:
	clk_disable(mck);
	clk_disable(pclk);
	kfree(hsmc);
out_put_clocks:
	clk_put(mck);
out_put_pclk:
	clk_put(pclk);
	hsmc = NULL;
	return ret;
}