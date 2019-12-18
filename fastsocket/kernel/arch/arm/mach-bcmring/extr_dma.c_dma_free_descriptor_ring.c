#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ physAddr; int /*<<< orphan*/ * virtAddr; scalar_t__ descriptorsAllocated; scalar_t__ bytesAllocated; } ;
typedef  TYPE_1__ DMA_DescriptorRing_t ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_writecombine (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 

void dma_free_descriptor_ring(DMA_DescriptorRing_t *ring	/* Descriptor to release */
    ) {
	if (ring->virtAddr != NULL) {
		dma_free_writecombine(NULL,
				      ring->bytesAllocated,
				      ring->virtAddr, ring->physAddr);
	}

	ring->bytesAllocated = 0;
	ring->descriptorsAllocated = 0;
	ring->virtAddr = NULL;
	ring->physAddr = 0;
}