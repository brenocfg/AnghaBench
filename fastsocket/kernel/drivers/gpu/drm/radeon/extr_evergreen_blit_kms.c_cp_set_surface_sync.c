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
typedef  int u64 ;
typedef  int u32 ;
struct radeon_ring {int dummy; } ;
struct radeon_device {scalar_t__ family; struct radeon_ring* ring; } ;

/* Variables and functions */
 scalar_t__ CHIP_CAYMAN ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_SET_CONFIG_REG ; 
 int PACKET3_SET_CONFIG_REG_START ; 
 int /*<<< orphan*/  PACKET3_SURFACE_SYNC ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 

__attribute__((used)) static void
cp_set_surface_sync(struct radeon_device *rdev,
		    u32 sync_type, u32 size,
		    u64 mc_addr)
{
	struct radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	u32 cp_coher_size;

	if (size == 0xffffffff)
		cp_coher_size = 0xffffffff;
	else
		cp_coher_size = ((size + 255) >> 8);

	if (rdev->family >= CHIP_CAYMAN) {
		/* CP_COHER_CNTL2 has to be set manually when submitting a surface_sync
		 * to the RB directly. For IBs, the CP programs this as part of the
		 * surface_sync packet.
		 */
		radeon_ring_write(ring, PACKET3(PACKET3_SET_CONFIG_REG, 1));
		radeon_ring_write(ring, (0x85e8 - PACKET3_SET_CONFIG_REG_START) >> 2);
		radeon_ring_write(ring, 0); /* CP_COHER_CNTL2 */
	}
	radeon_ring_write(ring, PACKET3(PACKET3_SURFACE_SYNC, 3));
	radeon_ring_write(ring, sync_type);
	radeon_ring_write(ring, cp_coher_size);
	radeon_ring_write(ring, mc_addr >> 8);
	radeon_ring_write(ring, 10); /* poll interval */
}