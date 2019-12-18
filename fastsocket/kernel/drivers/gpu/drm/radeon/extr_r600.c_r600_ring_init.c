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
typedef  int u32 ;
struct radeon_ring {unsigned int ring_size; int align_mask; scalar_t__ rptr_save_reg; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int drm_order (unsigned int) ; 
 scalar_t__ radeon_ring_supports_scratch_reg (struct radeon_device*,struct radeon_ring*) ; 
 int radeon_scratch_get (struct radeon_device*,scalar_t__*) ; 

void r600_ring_init(struct radeon_device *rdev, struct radeon_ring *ring, unsigned ring_size)
{
	u32 rb_bufsz;
	int r;

	/* Align ring size */
	rb_bufsz = drm_order(ring_size / 8);
	ring_size = (1 << (rb_bufsz + 1)) * 4;
	ring->ring_size = ring_size;
	ring->align_mask = 16 - 1;

	if (radeon_ring_supports_scratch_reg(rdev, ring)) {
		r = radeon_scratch_get(rdev, &ring->rptr_save_reg);
		if (r) {
			DRM_ERROR("failed to get scratch reg for rptr save (%d).\n", r);
			ring->rptr_save_reg = 0;
		}
	}
}