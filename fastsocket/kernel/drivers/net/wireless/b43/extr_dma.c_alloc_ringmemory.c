#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct b43_dmaring {scalar_t__ type; int /*<<< orphan*/  descbase; int /*<<< orphan*/  dmabase; TYPE_2__* dev; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_DMA32_RINGMEMSIZE ; 
 int /*<<< orphan*/  B43_DMA64_RINGMEMSIZE ; 
 scalar_t__ B43_DMA_64BIT ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int alloc_ringmemory(struct b43_dmaring *ring)
{
	/* The specs call for 4K buffers for 30- and 32-bit DMA with 4K
	 * alignment and 8K buffers for 64-bit DMA with 8K alignment.
	 * In practice we could use smaller buffers for the latter, but the
	 * alignment is really important because of the hardware bug. If bit
	 * 0x00001000 is used in DMA address, some hardware (like BCM4331)
	 * copies that bit into B43_DMA64_RXSTATUS and we get false values from
	 * B43_DMA64_RXSTATDPTR. Let's just use 8K buffers even if we don't use
	 * more than 256 slots for ring.
	 */
	u16 ring_mem_size = (ring->type == B43_DMA_64BIT) ?
				B43_DMA64_RINGMEMSIZE : B43_DMA32_RINGMEMSIZE;

	ring->descbase = dma_alloc_coherent(ring->dev->dev->dma_dev,
					    ring_mem_size, &(ring->dmabase),
					    GFP_KERNEL | __GFP_ZERO);
	if (!ring->descbase)
		return -ENOMEM;

	return 0;
}