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
struct b43legacy_dmaring {int /*<<< orphan*/  descbase; int /*<<< orphan*/  dmabase; TYPE_2__* dev; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_DMA_RINGMEMSIZE ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int alloc_ringmemory(struct b43legacy_dmaring *ring)
{
	/* GFP flags must match the flags in free_ringmemory()! */
	ring->descbase = dma_alloc_coherent(ring->dev->dev->dma_dev,
					    B43legacy_DMA_RINGMEMSIZE,
					    &(ring->dmabase),
					    GFP_KERNEL | __GFP_ZERO);
	if (!ring->descbase)
		return -ENOMEM;

	return 0;
}