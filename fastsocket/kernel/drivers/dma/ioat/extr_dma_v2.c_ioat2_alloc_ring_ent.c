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
struct ioatdma_device {int /*<<< orphan*/  dma_pool; } ;
struct TYPE_2__ {int /*<<< orphan*/  phys; int /*<<< orphan*/  tx_submit; } ;
struct ioat_ring_ent {TYPE_1__ txd; struct ioat_ring_ent* hw; } ;
struct ioat_dma_descriptor {TYPE_1__ txd; struct ioat_dma_descriptor* hw; } ;
struct dma_chan {int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dma_async_tx_descriptor_init (TYPE_1__*,struct dma_chan*) ; 
 int /*<<< orphan*/  ioat2_cache ; 
 int /*<<< orphan*/  ioat2_tx_submit_unlock ; 
 struct ioat_ring_ent* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ioat_ring_ent*,int /*<<< orphan*/ ,int) ; 
 struct ioat_ring_ent* pci_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_pool_free (int /*<<< orphan*/ ,struct ioat_ring_ent*,int /*<<< orphan*/ ) ; 
 struct ioatdma_device* to_ioatdma_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ioat_ring_ent *ioat2_alloc_ring_ent(struct dma_chan *chan, gfp_t flags)
{
	struct ioat_dma_descriptor *hw;
	struct ioat_ring_ent *desc;
	struct ioatdma_device *dma;
	dma_addr_t phys;

	dma = to_ioatdma_device(chan->device);
	hw = pci_pool_alloc(dma->dma_pool, flags, &phys);
	if (!hw)
		return NULL;
	memset(hw, 0, sizeof(*hw));

	desc = kmem_cache_alloc(ioat2_cache, flags);
	if (!desc) {
		pci_pool_free(dma->dma_pool, hw, phys);
		return NULL;
	}
	memset(desc, 0, sizeof(*desc));

	dma_async_tx_descriptor_init(&desc->txd, chan);
	desc->txd.tx_submit = ioat2_tx_submit_unlock;
	desc->hw = hw;
	desc->txd.phys = phys;
	return desc;
}