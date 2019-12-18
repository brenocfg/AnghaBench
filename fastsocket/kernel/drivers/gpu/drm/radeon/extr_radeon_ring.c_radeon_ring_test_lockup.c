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
typedef  int uint32_t ;
struct radeon_ring {int rptr; int ptr_reg_mask; int ptr_reg_shift; int last_rptr; scalar_t__ last_activity; int /*<<< orphan*/  rptr_reg; } ;
struct radeon_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long) ; 
 unsigned long jiffies ; 
 unsigned long jiffies_to_msecs (scalar_t__) ; 
 unsigned long radeon_lockup_timeout ; 
 int /*<<< orphan*/  radeon_ring_lockup_update (struct radeon_ring*) ; 
 int /*<<< orphan*/  time_after (unsigned long,scalar_t__) ; 

bool radeon_ring_test_lockup(struct radeon_device *rdev, struct radeon_ring *ring)
{
	unsigned long cjiffies, elapsed;
	uint32_t rptr;

	cjiffies = jiffies;
	if (!time_after(cjiffies, ring->last_activity)) {
		/* likely a wrap around */
		radeon_ring_lockup_update(ring);
		return false;
	}
	rptr = RREG32(ring->rptr_reg);
	ring->rptr = (rptr & ring->ptr_reg_mask) >> ring->ptr_reg_shift;
	if (ring->rptr != ring->last_rptr) {
		/* CP is still working no lockup */
		radeon_ring_lockup_update(ring);
		return false;
	}
	elapsed = jiffies_to_msecs(cjiffies - ring->last_activity);
	if (radeon_lockup_timeout && elapsed >= radeon_lockup_timeout) {
		dev_err(rdev->dev, "GPU lockup CP stall for more than %lumsec\n", elapsed);
		return true;
	}
	/* give a chance to the GPU ... */
	return false;
}