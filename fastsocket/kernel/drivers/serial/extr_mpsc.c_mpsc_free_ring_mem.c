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
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  line; } ;
struct mpsc_port_info {scalar_t__ dma_region_p; int /*<<< orphan*/ * dma_region; TYPE_1__ port; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPSC_DMA_ALLOC_SIZE ; 
 int /*<<< orphan*/  dma_free_noncoherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpsc_free_ring_mem(struct mpsc_port_info *pi)
{
	pr_debug("mpsc_free_ring_mem[%d]: Freeing ring mem\n", pi->port.line);

	if (pi->dma_region) {
		dma_free_noncoherent(pi->port.dev, MPSC_DMA_ALLOC_SIZE,
				pi->dma_region, pi->dma_region_p);
		pi->dma_region = NULL;
		pi->dma_region_p = (dma_addr_t)NULL;
	}
}