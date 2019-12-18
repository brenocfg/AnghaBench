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
struct radeon_ring {scalar_t__ rptr; scalar_t__ wptr; int /*<<< orphan*/  nop; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int radeon_ring_alloc (struct radeon_device*,struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_ring_commit (struct radeon_device*,struct radeon_ring*) ; 
 int /*<<< orphan*/  radeon_ring_free_size (struct radeon_device*,struct radeon_ring*) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int /*<<< orphan*/ ) ; 

void radeon_ring_force_activity(struct radeon_device *rdev, struct radeon_ring *ring)
{
	int r;

	radeon_ring_free_size(rdev, ring);
	if (ring->rptr == ring->wptr) {
		r = radeon_ring_alloc(rdev, ring, 1);
		if (!r) {
			radeon_ring_write(ring, ring->nop);
			radeon_ring_commit(rdev, ring);
		}
	}
}