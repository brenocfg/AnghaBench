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
struct radeon_ring {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  resync_scratch; } ;
struct TYPE_4__ {TYPE_1__ r300; } ;
struct radeon_device {TYPE_2__ config; struct radeon_ring* ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R300_RB3D_DC_FINISH ; 
 int /*<<< orphan*/  R300_RB3D_DSTCACHE_CTLSTAT ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int /*<<< orphan*/  radeon_ring_lock (struct radeon_device*,struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_ring_unlock_commit (struct radeon_device*,struct radeon_ring*) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_scratch_free (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r420_cp_errata_fini(struct radeon_device *rdev)
{
	struct radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];

	/* Catch the RESYNC we dispatched all the way back,
	 * at the very beginning of the CP init.
	 */
	radeon_ring_lock(rdev, ring, 8);
	radeon_ring_write(ring, PACKET0(R300_RB3D_DSTCACHE_CTLSTAT, 0));
	radeon_ring_write(ring, R300_RB3D_DC_FINISH);
	radeon_ring_unlock_commit(rdev, ring);
	radeon_scratch_free(rdev, rdev->config.r300.resync_scratch);
}