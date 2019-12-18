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
struct TYPE_2__ {int /*<<< orphan*/  phys; } ;
struct ioat_ring_ent {TYPE_1__ txd; int /*<<< orphan*/  hw; } ;
struct dma_chan {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioat2_cache ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct ioat_ring_ent*) ; 
 int /*<<< orphan*/  pci_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ioatdma_device* to_ioatdma_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ioat2_free_ring_ent(struct ioat_ring_ent *desc, struct dma_chan *chan)
{
	struct ioatdma_device *dma;

	dma = to_ioatdma_device(chan->device);
	pci_pool_free(dma->dma_pool, desc->hw, desc->txd.phys);
	kmem_cache_free(ioat2_cache, desc);
}