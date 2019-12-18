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
struct radeon_device {int /*<<< orphan*/ * ring; } ;

/* Variables and functions */
 size_t CAYMAN_RING_TYPE_DMA1_INDEX ; 
 size_t R600_RING_TYPE_DMA_INDEX ; 
 int /*<<< orphan*/  cayman_dma_stop (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_ring_fini (struct radeon_device*,int /*<<< orphan*/ *) ; 

void cayman_dma_fini(struct radeon_device *rdev)
{
	cayman_dma_stop(rdev);
	radeon_ring_fini(rdev, &rdev->ring[R600_RING_TYPE_DMA_INDEX]);
	radeon_ring_fini(rdev, &rdev->ring[CAYMAN_RING_TYPE_DMA1_INDEX]);
}