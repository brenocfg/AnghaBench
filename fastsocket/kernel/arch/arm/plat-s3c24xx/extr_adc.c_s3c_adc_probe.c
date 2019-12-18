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
struct resource {int /*<<< orphan*/  start; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct adc_device {int prescale; scalar_t__ irq; int /*<<< orphan*/  clk; int /*<<< orphan*/  regs; struct platform_device* pdev; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int S3C2410_ADCCON ; 
 int S3C2410_ADCCON_PRSCEN ; 
 int S3C2410_ADCCON_PRSCVL (int) ; 
 struct adc_device* adc_dev ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct adc_device*) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct adc_device*) ; 
 struct adc_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct adc_device*) ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct adc_device*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  s3c_adc_irq ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3c_adc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct adc_device *adc;
	struct resource *regs;
	int ret;

	adc = kzalloc(sizeof(struct adc_device), GFP_KERNEL);
	if (adc == NULL) {
		dev_err(dev, "failed to allocate adc_device\n");
		return -ENOMEM;
	}

	adc->pdev = pdev;
	adc->prescale = S3C2410_ADCCON_PRSCVL(49);

	adc->irq = platform_get_irq(pdev, 1);
	if (adc->irq <= 0) {
		dev_err(dev, "failed to get adc irq\n");
		ret = -ENOENT;
		goto err_alloc;
	}

	ret = request_irq(adc->irq, s3c_adc_irq, 0, dev_name(dev), adc);
	if (ret < 0) {
		dev_err(dev, "failed to attach adc irq\n");
		goto err_alloc;
	}

	adc->clk = clk_get(dev, "adc");
	if (IS_ERR(adc->clk)) {
		dev_err(dev, "failed to get adc clock\n");
		ret = PTR_ERR(adc->clk);
		goto err_irq;
	}

	regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!regs) {
		dev_err(dev, "failed to find registers\n");
		ret = -ENXIO;
		goto err_clk;
	}

	adc->regs = ioremap(regs->start, resource_size(regs));
	if (!adc->regs) {
		dev_err(dev, "failed to map registers\n");
		ret = -ENXIO;
		goto err_clk;
	}

	clk_enable(adc->clk);

	writel(adc->prescale | S3C2410_ADCCON_PRSCEN,
	       adc->regs + S3C2410_ADCCON);

	dev_info(dev, "attached adc driver\n");

	platform_set_drvdata(pdev, adc);
	adc_dev = adc;

	return 0;

 err_clk:
	clk_put(adc->clk);

 err_irq:
	free_irq(adc->irq, adc);

 err_alloc:
	kfree(adc);
	return ret;
}