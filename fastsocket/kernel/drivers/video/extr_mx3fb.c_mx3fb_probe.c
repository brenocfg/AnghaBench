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
struct resource {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct mx3fb_data {int backlight_level; int /*<<< orphan*/  reg_base; struct device* dev; int /*<<< orphan*/  lock; } ;
struct dma_chan_request {int /*<<< orphan*/  id; struct mx3fb_data* mx3fb; } ;
struct dma_chan {int dummy; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_PRIVATE ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IDMAC_SDC_0 ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  chan_filter ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (struct dma_chan*) ; 
 struct dma_chan* dma_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dma_chan_request*) ; 
 int /*<<< orphan*/  dmaengine_get () ; 
 int /*<<< orphan*/  dmaengine_put () ; 
 int init_fb_chan (struct mx3fb_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mx3fb_data*) ; 
 struct mx3fb_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mx3fb_data*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_idmac_chan (struct dma_chan*) ; 

__attribute__((used)) static int mx3fb_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int ret;
	struct resource *sdc_reg;
	struct mx3fb_data *mx3fb;
	dma_cap_mask_t mask;
	struct dma_chan *chan;
	struct dma_chan_request rq;

	/*
	 * Display Interface (DI) and Synchronous Display Controller (SDC)
	 * registers
	 */
	sdc_reg = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!sdc_reg)
		return -EINVAL;

	mx3fb = kzalloc(sizeof(*mx3fb), GFP_KERNEL);
	if (!mx3fb)
		return -ENOMEM;

	spin_lock_init(&mx3fb->lock);

	mx3fb->reg_base = ioremap(sdc_reg->start, resource_size(sdc_reg));
	if (!mx3fb->reg_base) {
		ret = -ENOMEM;
		goto eremap;
	}

	pr_debug("Remapped %x to %x at %p\n", sdc_reg->start, sdc_reg->end,
		 mx3fb->reg_base);

	/* IDMAC interface */
	dmaengine_get();

	mx3fb->dev = dev;
	platform_set_drvdata(pdev, mx3fb);

	rq.mx3fb = mx3fb;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);
	dma_cap_set(DMA_PRIVATE, mask);
	rq.id = IDMAC_SDC_0;
	chan = dma_request_channel(mask, chan_filter, &rq);
	if (!chan) {
		ret = -EBUSY;
		goto ersdc0;
	}

	ret = init_fb_chan(mx3fb, to_idmac_chan(chan));
	if (ret < 0)
		goto eisdc0;

	mx3fb->backlight_level = 255;

	return 0;

eisdc0:
	dma_release_channel(chan);
ersdc0:
	dmaengine_put();
	iounmap(mx3fb->reg_base);
eremap:
	kfree(mx3fb);
	dev_err(dev, "mx3fb: failed to register fb\n");
	return ret;
}