#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct pxamci_host {int max_blk_size; int max_blk_count; int dma; int clkrate; int f_min; int f_max; int caps; int irq; int imask; int /*<<< orphan*/ * clk; int /*<<< orphan*/  sg_dma; scalar_t__ sg_cpu; scalar_t__ base; TYPE_1__* pdata; int /*<<< orphan*/  dma_drcmrtx; int /*<<< orphan*/  dma_drcmrrx; struct resource* res; int /*<<< orphan*/  lock; int /*<<< orphan*/  cmdat; int /*<<< orphan*/  clkrt; struct pxamci_host* mmc; int /*<<< orphan*/  max_seg_size; int /*<<< orphan*/  max_phys_segs; int /*<<< orphan*/ * ops; } ;
struct TYPE_10__ {TYPE_1__* platform_data; } ;
struct platform_device {TYPE_2__ dev; } ;
struct mmc_host {int max_blk_size; int max_blk_count; int dma; int clkrate; int f_min; int f_max; int caps; int irq; int imask; int /*<<< orphan*/ * clk; int /*<<< orphan*/  sg_dma; scalar_t__ sg_cpu; scalar_t__ base; TYPE_1__* pdata; int /*<<< orphan*/  dma_drcmrtx; int /*<<< orphan*/  dma_drcmrrx; struct resource* res; int /*<<< orphan*/  lock; int /*<<< orphan*/  cmdat; int /*<<< orphan*/  clkrt; struct mmc_host* mmc; int /*<<< orphan*/  max_seg_size; int /*<<< orphan*/  max_phys_segs; int /*<<< orphan*/ * ops; } ;
struct TYPE_9__ {int gpio_card_detect; int gpio_card_ro; int gpio_power; scalar_t__ get_ro; scalar_t__ setpower; int /*<<< orphan*/  (* init ) (TYPE_2__*,int /*<<< orphan*/ ,struct pxamci_host*) ;int /*<<< orphan*/  gpio_power_invert; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKRT_OFF ; 
 int /*<<< orphan*/  CMDAT_SDIO_INT_EN ; 
 int /*<<< orphan*/  DMA_PRIO_LOW ; 
 char* DRIVER_NAME ; 
 int EBUSY ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_DMA ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int MMC_CAP_4_BIT_DATA ; 
 int MMC_CAP_MMC_HIGHSPEED ; 
 int MMC_CAP_SDIO_IRQ ; 
 int MMC_CAP_SD_HIGHSPEED ; 
 scalar_t__ MMC_I_MASK ; 
 int MMC_I_MASK_ALL ; 
 scalar_t__ MMC_RESTO ; 
 scalar_t__ MMC_SPI ; 
 int /*<<< orphan*/  NR_SG ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SZ_4K ; 
 int /*<<< orphan*/ * clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int clk_get_rate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 
 scalar_t__ cpu_is_pxa25x () ; 
 scalar_t__ cpu_is_pxa300 () ; 
 scalar_t__ cpu_is_pxa310 () ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 scalar_t__ dma_alloc_coherent (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_direction_input (int) ; 
 int /*<<< orphan*/  gpio_direction_output (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 scalar_t__ gpio_is_valid (int) ; 
 int gpio_request (int,char*) ; 
 int gpio_to_irq (int) ; 
 scalar_t__ ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  mmc_add_host (struct pxamci_host*) ; 
 struct pxamci_host* mmc_alloc_host (int,TYPE_2__*) ; 
 int /*<<< orphan*/  mmc_free_host (struct pxamci_host*) ; 
 struct pxamci_host* mmc_priv (struct pxamci_host*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pxamci_host*) ; 
 int /*<<< orphan*/  pxa_free_dma (int) ; 
 int pxa_request_dma (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pxamci_host*) ; 
 int /*<<< orphan*/  pxamci_detect_irq ; 
 int /*<<< orphan*/  pxamci_dma_irq ; 
 int /*<<< orphan*/  pxamci_init_ocr (struct pxamci_host*) ; 
 int /*<<< orphan*/  pxamci_irq ; 
 int /*<<< orphan*/  pxamci_ops ; 
 int /*<<< orphan*/  pxamci_stop_clock (struct pxamci_host*) ; 
 int /*<<< orphan*/  release_resource (struct resource*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int,char*,struct pxamci_host*) ; 
 struct resource* request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,struct pxamci_host*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int pxamci_probe(struct platform_device *pdev)
{
	struct mmc_host *mmc;
	struct pxamci_host *host = NULL;
	struct resource *r, *dmarx, *dmatx;
	int ret, irq, gpio_cd = -1, gpio_ro = -1, gpio_power = -1;

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	irq = platform_get_irq(pdev, 0);
	if (!r || irq < 0)
		return -ENXIO;

	r = request_mem_region(r->start, SZ_4K, DRIVER_NAME);
	if (!r)
		return -EBUSY;

	mmc = mmc_alloc_host(sizeof(struct pxamci_host), &pdev->dev);
	if (!mmc) {
		ret = -ENOMEM;
		goto out;
	}

	mmc->ops = &pxamci_ops;

	/*
	 * We can do SG-DMA, but we don't because we never know how much
	 * data we successfully wrote to the card.
	 */
	mmc->max_phys_segs = NR_SG;

	/*
	 * Our hardware DMA can handle a maximum of one page per SG entry.
	 */
	mmc->max_seg_size = PAGE_SIZE;

	/*
	 * Block length register is only 10 bits before PXA27x.
	 */
	mmc->max_blk_size = cpu_is_pxa25x() ? 1023 : 2048;

	/*
	 * Block count register is 16 bits.
	 */
	mmc->max_blk_count = 65535;

	host = mmc_priv(mmc);
	host->mmc = mmc;
	host->dma = -1;
	host->pdata = pdev->dev.platform_data;
	host->clkrt = CLKRT_OFF;

	host->clk = clk_get(&pdev->dev, NULL);
	if (IS_ERR(host->clk)) {
		ret = PTR_ERR(host->clk);
		host->clk = NULL;
		goto out;
	}

	host->clkrate = clk_get_rate(host->clk);

	/*
	 * Calculate minimum clock rate, rounding up.
	 */
	mmc->f_min = (host->clkrate + 63) / 64;
	mmc->f_max = (cpu_is_pxa300() || cpu_is_pxa310()) ? 26000000
							  : host->clkrate;

	pxamci_init_ocr(host);

	mmc->caps = 0;
	host->cmdat = 0;
	if (!cpu_is_pxa25x()) {
		mmc->caps |= MMC_CAP_4_BIT_DATA | MMC_CAP_SDIO_IRQ;
		host->cmdat |= CMDAT_SDIO_INT_EN;
		if (cpu_is_pxa300() || cpu_is_pxa310())
			mmc->caps |= MMC_CAP_MMC_HIGHSPEED |
				     MMC_CAP_SD_HIGHSPEED;
	}

	host->sg_cpu = dma_alloc_coherent(&pdev->dev, PAGE_SIZE, &host->sg_dma, GFP_KERNEL);
	if (!host->sg_cpu) {
		ret = -ENOMEM;
		goto out;
	}

	spin_lock_init(&host->lock);
	host->res = r;
	host->irq = irq;
	host->imask = MMC_I_MASK_ALL;

	host->base = ioremap(r->start, SZ_4K);
	if (!host->base) {
		ret = -ENOMEM;
		goto out;
	}

	/*
	 * Ensure that the host controller is shut down, and setup
	 * with our defaults.
	 */
	pxamci_stop_clock(host);
	writel(0, host->base + MMC_SPI);
	writel(64, host->base + MMC_RESTO);
	writel(host->imask, host->base + MMC_I_MASK);

	host->dma = pxa_request_dma(DRIVER_NAME, DMA_PRIO_LOW,
				    pxamci_dma_irq, host);
	if (host->dma < 0) {
		ret = -EBUSY;
		goto out;
	}

	ret = request_irq(host->irq, pxamci_irq, 0, DRIVER_NAME, host);
	if (ret)
		goto out;

	platform_set_drvdata(pdev, mmc);

	dmarx = platform_get_resource(pdev, IORESOURCE_DMA, 0);
	if (!dmarx) {
		ret = -ENXIO;
		goto out;
	}
	host->dma_drcmrrx = dmarx->start;

	dmatx = platform_get_resource(pdev, IORESOURCE_DMA, 1);
	if (!dmatx) {
		ret = -ENXIO;
		goto out;
	}
	host->dma_drcmrtx = dmatx->start;

	if (host->pdata) {
		gpio_cd = host->pdata->gpio_card_detect;
		gpio_ro = host->pdata->gpio_card_ro;
		gpio_power = host->pdata->gpio_power;
	}
	if (gpio_is_valid(gpio_power)) {
		ret = gpio_request(gpio_power, "mmc card power");
		if (ret) {
			dev_err(&pdev->dev, "Failed requesting gpio_power %d\n", gpio_power);
			goto out;
		}
		gpio_direction_output(gpio_power,
				      host->pdata->gpio_power_invert);
	}
	if (gpio_is_valid(gpio_ro)) {
		ret = gpio_request(gpio_ro, "mmc card read only");
		if (ret) {
			dev_err(&pdev->dev, "Failed requesting gpio_ro %d\n", gpio_ro);
			goto err_gpio_ro;
		}
		gpio_direction_input(gpio_ro);
	}
	if (gpio_is_valid(gpio_cd)) {
		ret = gpio_request(gpio_cd, "mmc card detect");
		if (ret) {
			dev_err(&pdev->dev, "Failed requesting gpio_cd %d\n", gpio_cd);
			goto err_gpio_cd;
		}
		gpio_direction_input(gpio_cd);

		ret = request_irq(gpio_to_irq(gpio_cd), pxamci_detect_irq,
				  IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				  "mmc card detect", mmc);
		if (ret) {
			dev_err(&pdev->dev, "failed to request card detect IRQ\n");
			goto err_request_irq;
		}
	}

	if (host->pdata && host->pdata->init)
		host->pdata->init(&pdev->dev, pxamci_detect_irq, mmc);

	if (gpio_is_valid(gpio_power) && host->pdata->setpower)
		dev_warn(&pdev->dev, "gpio_power and setpower() both defined\n");
	if (gpio_is_valid(gpio_ro) && host->pdata->get_ro)
		dev_warn(&pdev->dev, "gpio_ro and get_ro() both defined\n");

	mmc_add_host(mmc);

	return 0;

err_request_irq:
	gpio_free(gpio_cd);
err_gpio_cd:
	gpio_free(gpio_ro);
err_gpio_ro:
	gpio_free(gpio_power);
 out:
	if (host) {
		if (host->dma >= 0)
			pxa_free_dma(host->dma);
		if (host->base)
			iounmap(host->base);
		if (host->sg_cpu)
			dma_free_coherent(&pdev->dev, PAGE_SIZE, host->sg_cpu, host->sg_dma);
		if (host->clk)
			clk_put(host->clk);
	}
	if (mmc)
		mmc_free_host(mmc);
	release_resource(r);
	return ret;
}