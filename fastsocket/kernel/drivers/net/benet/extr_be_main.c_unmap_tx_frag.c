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
typedef  int u64 ;
struct device {int dummy; } ;
struct be_eth_wrb {int /*<<< orphan*/  frag_len; scalar_t__ frag_pa_lo; scalar_t__ frag_pa_hi; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  be_dws_le_to_cpu (struct be_eth_wrb*,int) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unmap_tx_frag(struct device *dev, struct be_eth_wrb *wrb,
		bool unmap_single)
{
	dma_addr_t dma;

	be_dws_le_to_cpu(wrb, sizeof(*wrb));

	dma = (u64)wrb->frag_pa_hi << 32 | (u64)wrb->frag_pa_lo;
	if (wrb->frag_len) {
		if (unmap_single)
			dma_unmap_single(dev, dma, wrb->frag_len,
					 DMA_TO_DEVICE);
		else
			dma_unmap_page(dev, dma, wrb->frag_len, DMA_TO_DEVICE);
	}
}