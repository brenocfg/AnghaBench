#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {int dummy; } ;
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct platform_device {int dummy; } ;
struct au1xpsc_audio_data {int dummy; } ;
struct TYPE_9__ {int cfg; struct TYPE_9__* ioarea; int /*<<< orphan*/  mmio; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2S_CFG (TYPE_1__*) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  PSC_CTRL (TYPE_1__*) ; 
 unsigned long PSC_CTRL_DISABLE ; 
 int PSC_I2SCFG_RT_FIFO8 ; 
 int PSC_I2SCFG_TT_FIFO8 ; 
 int /*<<< orphan*/  PSC_SEL (TYPE_1__*) ; 
 unsigned long PSC_SEL_CLK_MASK ; 
 unsigned long PSC_SEL_PS_I2SMODE ; 
 TYPE_1__* au1xpsc_i2s_workdata ; 
 unsigned long au_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioremap (scalar_t__,int) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_resource (TYPE_1__*) ; 
 TYPE_1__* request_mem_region (scalar_t__,scalar_t__,char*) ; 

__attribute__((used)) static int au1xpsc_i2s_probe(struct platform_device *pdev,
			     struct snd_soc_dai *dai)
{
	struct resource *r;
	unsigned long sel;
	int ret;

	if (au1xpsc_i2s_workdata)
		return -EBUSY;

	au1xpsc_i2s_workdata =
		kzalloc(sizeof(struct au1xpsc_audio_data), GFP_KERNEL);
	if (!au1xpsc_i2s_workdata)
		return -ENOMEM;

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!r) {
		ret = -ENODEV;
		goto out0;
	}

	ret = -EBUSY;
	au1xpsc_i2s_workdata->ioarea =
		request_mem_region(r->start, r->end - r->start + 1,
					"au1xpsc_i2s");
	if (!au1xpsc_i2s_workdata->ioarea)
		goto out0;

	au1xpsc_i2s_workdata->mmio = ioremap(r->start, 0xffff);
	if (!au1xpsc_i2s_workdata->mmio)
		goto out1;

	/* preserve PSC clock source set up by platform (dev.platform_data
	 * is already occupied by soc layer)
	 */
	sel = au_readl(PSC_SEL(au1xpsc_i2s_workdata)) & PSC_SEL_CLK_MASK;
	au_writel(PSC_CTRL_DISABLE, PSC_CTRL(au1xpsc_i2s_workdata));
	au_sync();
	au_writel(PSC_SEL_PS_I2SMODE | sel, PSC_SEL(au1xpsc_i2s_workdata));
	au_writel(0, I2S_CFG(au1xpsc_i2s_workdata));
	au_sync();

	/* preconfigure: set max rx/tx fifo depths */
	au1xpsc_i2s_workdata->cfg |=
			PSC_I2SCFG_RT_FIFO8 | PSC_I2SCFG_TT_FIFO8;

	/* don't wait for I2S core to become ready now; clocks may not
	 * be running yet; depending on clock input for PSC a wait might
	 * time out.
	 */

	return 0;

out1:
	release_resource(au1xpsc_i2s_workdata->ioarea);
	kfree(au1xpsc_i2s_workdata->ioarea);
out0:
	kfree(au1xpsc_i2s_workdata);
	au1xpsc_i2s_workdata = NULL;
	return ret;
}