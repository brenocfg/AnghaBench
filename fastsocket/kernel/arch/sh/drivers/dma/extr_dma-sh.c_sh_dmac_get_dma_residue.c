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
struct dma_channel {size_t chan; } ;

/* Variables and functions */
 scalar_t__ CHCR ; 
 int CHCR_DE ; 
 scalar_t__ TCR ; 
 int calc_xmit_shift (struct dma_channel*) ; 
 int ctrl_inl (scalar_t__) ; 
 scalar_t__* dma_base_addr ; 

__attribute__((used)) static int sh_dmac_get_dma_residue(struct dma_channel *chan)
{
	if (!(ctrl_inl(dma_base_addr[chan->chan] + CHCR) & CHCR_DE))
		return 0;

	return ctrl_inl(dma_base_addr[chan->chan] + TCR)
		 << calc_xmit_shift(chan);
}