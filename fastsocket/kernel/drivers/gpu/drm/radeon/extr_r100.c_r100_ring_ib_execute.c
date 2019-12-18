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
typedef  scalar_t__ u32 ;
struct radeon_ring {scalar_t__ rptr_save_reg; scalar_t__ wptr; } ;
struct radeon_ib {scalar_t__ length_dw; scalar_t__ gpu_addr; } ;
struct radeon_device {struct radeon_ring* ring; } ;

/* Variables and functions */
 scalar_t__ PACKET0 (scalar_t__,int) ; 
 scalar_t__ RADEON_CP_IB_BASE ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,scalar_t__) ; 

void r100_ring_ib_execute(struct radeon_device *rdev, struct radeon_ib *ib)
{
	struct radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];

	if (ring->rptr_save_reg) {
		u32 next_rptr = ring->wptr + 2 + 3;
		radeon_ring_write(ring, PACKET0(ring->rptr_save_reg, 0));
		radeon_ring_write(ring, next_rptr);
	}

	radeon_ring_write(ring, PACKET0(RADEON_CP_IB_BASE, 1));
	radeon_ring_write(ring, ib->gpu_addr);
	radeon_ring_write(ring, ib->length_dw);
}