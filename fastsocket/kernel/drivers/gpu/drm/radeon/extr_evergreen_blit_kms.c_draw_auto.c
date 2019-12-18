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
struct radeon_device {struct radeon_ring* ring; } ;

/* Variables and functions */
 int DI_INDEX_SIZE_16_BIT ; 
 int DI_PT_RECTLIST ; 
 int DI_SRC_SEL_AUTO_INDEX ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_DRAW_INDEX_AUTO ; 
 int /*<<< orphan*/  PACKET3_INDEX_TYPE ; 
 int /*<<< orphan*/  PACKET3_NUM_INSTANCES ; 
 int /*<<< orphan*/  PACKET3_SET_CONFIG_REG ; 
 int PACKET3_SET_CONFIG_REG_START ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int VGT_PRIMITIVE_TYPE ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 

__attribute__((used)) static void
draw_auto(struct radeon_device *rdev)
{
	struct radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	radeon_ring_write(ring, PACKET3(PACKET3_SET_CONFIG_REG, 1));
	radeon_ring_write(ring, (VGT_PRIMITIVE_TYPE - PACKET3_SET_CONFIG_REG_START) >> 2);
	radeon_ring_write(ring, DI_PT_RECTLIST);

	radeon_ring_write(ring, PACKET3(PACKET3_INDEX_TYPE, 0));
	radeon_ring_write(ring,
#ifdef __BIG_ENDIAN
			  (2 << 2) |
#endif
			  DI_INDEX_SIZE_16_BIT);

	radeon_ring_write(ring, PACKET3(PACKET3_NUM_INSTANCES, 0));
	radeon_ring_write(ring, 1);

	radeon_ring_write(ring, PACKET3(PACKET3_DRAW_INDEX_AUTO, 1));
	radeon_ring_write(ring, 3);
	radeon_ring_write(ring, DI_SRC_SEL_AUTO_INDEX);

}