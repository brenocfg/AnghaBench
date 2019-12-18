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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RADEON_ISYNC_ANY2D_IDLE3D ; 
 int RADEON_ISYNC_ANY3D_IDLE2D ; 
 int /*<<< orphan*/  RADEON_ISYNC_CNTL ; 
 int RADEON_ISYNC_CPSCRATCH_IDLEGUI ; 
 int RADEON_ISYNC_WAIT_IDLEGUI ; 
 int radeon_ring_lock (struct radeon_device*,struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_ring_unlock_commit (struct radeon_device*,struct radeon_ring*) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 

void r100_ring_start(struct radeon_device *rdev, struct radeon_ring *ring)
{
	int r;

	r = radeon_ring_lock(rdev, ring, 2);
	if (r) {
		return;
	}
	radeon_ring_write(ring, PACKET0(RADEON_ISYNC_CNTL, 0));
	radeon_ring_write(ring,
			  RADEON_ISYNC_ANY2D_IDLE3D |
			  RADEON_ISYNC_ANY3D_IDLE2D |
			  RADEON_ISYNC_WAIT_IDLEGUI |
			  RADEON_ISYNC_CPSCRATCH_IDLEGUI);
	radeon_ring_unlock_commit(rdev, ring);
}