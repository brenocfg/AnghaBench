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
struct b43_dmaring {scalar_t__ type; int /*<<< orphan*/  dmabase; int /*<<< orphan*/  descbase; TYPE_2__* dev; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_DMA32_RINGMEMSIZE ; 
 int /*<<< orphan*/  B43_DMA64_RINGMEMSIZE ; 
 scalar_t__ B43_DMA_64BIT ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_ringmemory(struct b43_dmaring *ring)
{
	u16 ring_mem_size = (ring->type == B43_DMA_64BIT) ?
				B43_DMA64_RINGMEMSIZE : B43_DMA32_RINGMEMSIZE;
	dma_free_coherent(ring->dev->dev->dma_dev, ring_mem_size,
			  ring->descbase, ring->dmabase);
}