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
typedef  int u32 ;
struct radeon_ring {int wptr; int next_rptr_gpu_addr; } ;
struct radeon_ib {size_t ring; int gpu_addr; int length_dw; TYPE_2__* vm; } ;
struct TYPE_3__ {scalar_t__ enabled; } ;
struct radeon_device {TYPE_1__ wb; struct radeon_ring* ring; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int DMA_IB_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DMA_PACKET_INDIRECT_BUFFER ; 
 int /*<<< orphan*/  DMA_PACKET_NOP ; 
 int /*<<< orphan*/  DMA_PACKET_WRITE ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 
 int upper_32_bits (int) ; 

void cayman_dma_ring_ib_execute(struct radeon_device *rdev,
				struct radeon_ib *ib)
{
	struct radeon_ring *ring = &rdev->ring[ib->ring];

	if (rdev->wb.enabled) {
		u32 next_rptr = ring->wptr + 4;
		while ((next_rptr & 7) != 5)
			next_rptr++;
		next_rptr += 3;
		radeon_ring_write(ring, DMA_PACKET(DMA_PACKET_WRITE, 0, 0, 1));
		radeon_ring_write(ring, ring->next_rptr_gpu_addr & 0xfffffffc);
		radeon_ring_write(ring, upper_32_bits(ring->next_rptr_gpu_addr) & 0xff);
		radeon_ring_write(ring, next_rptr);
	}

	/* The indirect buffer packet must end on an 8 DW boundary in the DMA ring.
	 * Pad as necessary with NOPs.
	 */
	while ((ring->wptr & 7) != 5)
		radeon_ring_write(ring, DMA_PACKET(DMA_PACKET_NOP, 0, 0, 0));
	radeon_ring_write(ring, DMA_IB_PACKET(DMA_PACKET_INDIRECT_BUFFER, ib->vm ? ib->vm->id : 0, 0));
	radeon_ring_write(ring, (ib->gpu_addr & 0xFFFFFFE0));
	radeon_ring_write(ring, (ib->length_dw << 12) | (upper_32_bits(ib->gpu_addr) & 0xFF));

}