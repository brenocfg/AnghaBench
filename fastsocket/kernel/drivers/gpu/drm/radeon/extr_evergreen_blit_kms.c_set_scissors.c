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
struct radeon_ring {int dummy; } ;
struct radeon_device {scalar_t__ family; struct radeon_ring* ring; } ;

/* Variables and functions */
 scalar_t__ CHIP_CAYMAN ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_SET_CONTEXT_REG ; 
 int PACKET3_SET_CONTEXT_REG_START ; 
 int PA_SC_GENERIC_SCISSOR_TL ; 
 int PA_SC_SCREEN_SCISSOR_TL ; 
 int PA_SC_WINDOW_SCISSOR_TL ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 

__attribute__((used)) static void
set_scissors(struct radeon_device *rdev, int x1, int y1,
	     int x2, int y2)
{
	struct radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	/* workaround some hw bugs */
	if (x2 == 0)
		x1 = 1;
	if (y2 == 0)
		y1 = 1;
	if (rdev->family >= CHIP_CAYMAN) {
		if ((x2 == 1) && (y2 == 1))
			x2 = 2;
	}

	radeon_ring_write(ring, PACKET3(PACKET3_SET_CONTEXT_REG, 2));
	radeon_ring_write(ring, (PA_SC_SCREEN_SCISSOR_TL - PACKET3_SET_CONTEXT_REG_START) >> 2);
	radeon_ring_write(ring, (x1 << 0) | (y1 << 16));
	radeon_ring_write(ring, (x2 << 0) | (y2 << 16));

	radeon_ring_write(ring, PACKET3(PACKET3_SET_CONTEXT_REG, 2));
	radeon_ring_write(ring, (PA_SC_GENERIC_SCISSOR_TL - PACKET3_SET_CONTEXT_REG_START) >> 2);
	radeon_ring_write(ring, (x1 << 0) | (y1 << 16) | (1 << 31));
	radeon_ring_write(ring, (x2 << 0) | (y2 << 16));

	radeon_ring_write(ring, PACKET3(PACKET3_SET_CONTEXT_REG, 2));
	radeon_ring_write(ring, (PA_SC_WINDOW_SCISSOR_TL - PACKET3_SET_CONTEXT_REG_START) >> 2);
	radeon_ring_write(ring, (x1 << 0) | (y1 << 16) | (1 << 31));
	radeon_ring_write(ring, (x2 << 0) | (y2 << 16));
}