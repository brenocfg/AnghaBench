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
struct radeon_ring {int wptr; int align_mask; int ptr_reg_shift; int ptr_reg_mask; int /*<<< orphan*/  wptr_reg; int /*<<< orphan*/  nop; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MEMORYBARRIER () ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int /*<<< orphan*/ ) ; 

void radeon_ring_commit(struct radeon_device *rdev, struct radeon_ring *ring)
{
	/* We pad to match fetch size */
	while (ring->wptr & ring->align_mask) {
		radeon_ring_write(ring, ring->nop);
	}
	DRM_MEMORYBARRIER();
	WREG32(ring->wptr_reg, (ring->wptr << ring->ptr_reg_shift) & ring->ptr_reg_mask);
	(void)RREG32(ring->wptr_reg);
}