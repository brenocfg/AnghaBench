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
struct dma_channel {size_t chan; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ CHCR ; 
 unsigned long CHCR_IE ; 
 int /*<<< orphan*/  DMA_CONFIGURED ; 
 int /*<<< orphan*/  DMA_TEI_CAPABLE ; 
 unsigned long RS_DUAL ; 
 int /*<<< orphan*/  ctrl_outl (unsigned long,scalar_t__) ; 
 scalar_t__* dma_base_addr ; 

__attribute__((used)) static int
sh_dmac_configure_channel(struct dma_channel *chan, unsigned long chcr)
{
	if (!chcr)
		chcr = RS_DUAL | CHCR_IE;

	if (chcr & CHCR_IE) {
		chcr &= ~CHCR_IE;
		chan->flags |= DMA_TEI_CAPABLE;
	} else {
		chan->flags &= ~DMA_TEI_CAPABLE;
	}

	ctrl_outl(chcr, (dma_base_addr[chan->chan] + CHCR));

	chan->flags |= DMA_CONFIGURED;
	return 0;
}