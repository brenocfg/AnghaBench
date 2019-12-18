#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {int dummy; } ;
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct platform_device {int dummy; } ;
struct au1xpsc_audio_data {int dummy; } ;
struct TYPE_8__ {int cfg; struct TYPE_8__* ioarea; int /*<<< orphan*/  mmio; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int PSC_AC97CFG_DE_ENABLE ; 
 int PSC_AC97CFG_RT_FIFO8 ; 
 int PSC_AC97CFG_TT_FIFO8 ; 
 int /*<<< orphan*/  PSC_CTRL (TYPE_1__*) ; 
 unsigned long PSC_CTRL_DISABLE ; 
 int /*<<< orphan*/  PSC_SEL (TYPE_1__*) ; 
 unsigned long PSC_SEL_CLK_MASK ; 
 unsigned long PSC_SEL_PS_AC97MODE ; 
 TYPE_1__* au1xpsc_ac97_workdata ; 
 unsigned long au_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioremap (scalar_t__,int) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_resource (TYPE_1__*) ; 
 TYPE_1__* request_mem_region (scalar_t__,scalar_t__,char*) ; 

__attribute__((used)) static int au1xpsc_ac97_probe(struct platform_device *pdev,
			      struct snd_soc_dai *dai)
{
	int ret;
	struct resource *r;
	unsigned long sel;

	if (au1xpsc_ac97_workdata)
		return -EBUSY;

	au1xpsc_ac97_workdata =
		kzalloc(sizeof(struct au1xpsc_audio_data), GFP_KERNEL);
	if (!au1xpsc_ac97_workdata)
		return -ENOMEM;

	mutex_init(&au1xpsc_ac97_workdata->lock);

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!r) {
		ret = -ENODEV;
		goto out0;
	}

	ret = -EBUSY;
	au1xpsc_ac97_workdata->ioarea =
		request_mem_region(r->start, r->end - r->start + 1,
					"au1xpsc_ac97");
	if (!au1xpsc_ac97_workdata->ioarea)
		goto out0;

	au1xpsc_ac97_workdata->mmio = ioremap(r->start, 0xffff);
	if (!au1xpsc_ac97_workdata->mmio)
		goto out1;

	/* configuration: max dma trigger threshold, enable ac97 */
	au1xpsc_ac97_workdata->cfg = PSC_AC97CFG_RT_FIFO8 |
				     PSC_AC97CFG_TT_FIFO8 |
				     PSC_AC97CFG_DE_ENABLE;

	/* preserve PSC clock source set up by platform (dev.platform_data
	 * is already occupied by soc layer)
	 */
	sel = au_readl(PSC_SEL(au1xpsc_ac97_workdata)) & PSC_SEL_CLK_MASK;
	au_writel(PSC_CTRL_DISABLE, PSC_CTRL(au1xpsc_ac97_workdata));
	au_sync();
	au_writel(0, PSC_SEL(au1xpsc_ac97_workdata));
	au_sync();
	au_writel(PSC_SEL_PS_AC97MODE | sel, PSC_SEL(au1xpsc_ac97_workdata));
	au_sync();
	/* next up: cold reset.  Dont check for PSC-ready now since
	 * there may not be any codec clock yet.
	 */

	return 0;

out1:
	release_resource(au1xpsc_ac97_workdata->ioarea);
	kfree(au1xpsc_ac97_workdata->ioarea);
out0:
	kfree(au1xpsc_ac97_workdata);
	au1xpsc_ac97_workdata = NULL;
	return ret;
}