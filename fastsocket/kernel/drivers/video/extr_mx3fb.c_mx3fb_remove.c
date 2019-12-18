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
struct platform_device {int dummy; } ;
struct mx3fb_info {TYPE_1__* idmac_channel; } ;
struct mx3fb_data {int /*<<< orphan*/  reg_base; struct fb_info* fbi; } ;
struct fb_info {struct mx3fb_info* par; } ;
struct dma_chan {int dummy; } ;
struct TYPE_2__ {struct dma_chan dma_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (struct dma_chan*) ; 
 int /*<<< orphan*/  dmaengine_put () ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mx3fb_data*) ; 
 struct mx3fb_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_fbi (struct fb_info*) ; 

__attribute__((used)) static int mx3fb_remove(struct platform_device *dev)
{
	struct mx3fb_data *mx3fb = platform_get_drvdata(dev);
	struct fb_info *fbi = mx3fb->fbi;
	struct mx3fb_info *mx3_fbi = fbi->par;
	struct dma_chan *chan;

	chan = &mx3_fbi->idmac_channel->dma_chan;
	release_fbi(fbi);

	dma_release_channel(chan);
	dmaengine_put();

	iounmap(mx3fb->reg_base);
	kfree(mx3fb);
	return 0;
}