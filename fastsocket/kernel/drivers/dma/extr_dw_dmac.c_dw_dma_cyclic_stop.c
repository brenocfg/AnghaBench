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
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct dw_dma_chan {int mask; int /*<<< orphan*/  lock; TYPE_1__ chan; } ;
struct dw_dma {int dummy; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_EN ; 
 int /*<<< orphan*/  channel_clear_bit (struct dw_dma*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int dma_readl (struct dw_dma*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct dw_dma* to_dw_dma (int /*<<< orphan*/ ) ; 
 struct dw_dma_chan* to_dw_dma_chan (struct dma_chan*) ; 

void dw_dma_cyclic_stop(struct dma_chan *chan)
{
	struct dw_dma_chan	*dwc = to_dw_dma_chan(chan);
	struct dw_dma		*dw = to_dw_dma(dwc->chan.device);

	spin_lock(&dwc->lock);

	channel_clear_bit(dw, CH_EN, dwc->mask);
	while (dma_readl(dw, CH_EN) & dwc->mask)
		cpu_relax();

	spin_unlock(&dwc->lock);
}