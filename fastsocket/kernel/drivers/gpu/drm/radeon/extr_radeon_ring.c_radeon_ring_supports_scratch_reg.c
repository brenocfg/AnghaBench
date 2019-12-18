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
struct radeon_ring {int idx; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
#define  CAYMAN_RING_TYPE_CP1_INDEX 130 
#define  CAYMAN_RING_TYPE_CP2_INDEX 129 
#define  RADEON_RING_TYPE_GFX_INDEX 128 

bool radeon_ring_supports_scratch_reg(struct radeon_device *rdev,
				      struct radeon_ring *ring)
{
	switch (ring->idx) {
	case RADEON_RING_TYPE_GFX_INDEX:
	case CAYMAN_RING_TYPE_CP1_INDEX:
	case CAYMAN_RING_TYPE_CP2_INDEX:
		return true;
	default:
		return false;
	}
}