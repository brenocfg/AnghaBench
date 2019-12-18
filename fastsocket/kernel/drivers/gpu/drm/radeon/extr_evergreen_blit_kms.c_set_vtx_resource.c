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
 scalar_t__ CHIP_CAICOS ; 
 scalar_t__ CHIP_CEDAR ; 
 scalar_t__ CHIP_PALM ; 
 scalar_t__ CHIP_SUMO ; 
 scalar_t__ CHIP_SUMO2 ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_SET_RESOURCE ; 
 int /*<<< orphan*/  PACKET3_TC_ACTION_ENA ; 
 int /*<<< orphan*/  PACKET3_VC_ACTION_ENA ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int /*<<< orphan*/  SQ_ENDIAN_8IN32 ; 
 int /*<<< orphan*/  SQ_SEL_W ; 
 int /*<<< orphan*/  SQ_SEL_X ; 
 int /*<<< orphan*/  SQ_SEL_Y ; 
 int /*<<< orphan*/  SQ_SEL_Z ; 
 int /*<<< orphan*/  SQ_TEX_VTX_VALID_BUFFER ; 
 int SQ_VTCX_SEL_W (int /*<<< orphan*/ ) ; 
 int SQ_VTCX_SEL_X (int /*<<< orphan*/ ) ; 
 int SQ_VTCX_SEL_Y (int /*<<< orphan*/ ) ; 
 int SQ_VTCX_SEL_Z (int /*<<< orphan*/ ) ; 
 int SQ_VTXC_BASE_ADDR_HI (int) ; 
 int SQ_VTXC_ENDIAN_SWAP (int /*<<< orphan*/ ) ; 
 int SQ_VTXC_STRIDE (int) ; 
 int S__SQ_CONSTANT_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_set_surface_sync (struct radeon_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void
set_vtx_resource(struct radeon_device *rdev, u64 gpu_addr)
{
	struct radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	u32 sq_vtx_constant_word2, sq_vtx_constant_word3;

	/* high addr, stride */
	sq_vtx_constant_word2 = SQ_VTXC_BASE_ADDR_HI(upper_32_bits(gpu_addr) & 0xff) |
		SQ_VTXC_STRIDE(16);
#ifdef __BIG_ENDIAN
	sq_vtx_constant_word2 |= SQ_VTXC_ENDIAN_SWAP(SQ_ENDIAN_8IN32);
#endif
	/* xyzw swizzles */
	sq_vtx_constant_word3 = SQ_VTCX_SEL_X(SQ_SEL_X) |
		SQ_VTCX_SEL_Y(SQ_SEL_Y) |
		SQ_VTCX_SEL_Z(SQ_SEL_Z) |
		SQ_VTCX_SEL_W(SQ_SEL_W);

	radeon_ring_write(ring, PACKET3(PACKET3_SET_RESOURCE, 8));
	radeon_ring_write(ring, 0x580);
	radeon_ring_write(ring, gpu_addr & 0xffffffff);
	radeon_ring_write(ring, 48 - 1); /* size */
	radeon_ring_write(ring, sq_vtx_constant_word2);
	radeon_ring_write(ring, sq_vtx_constant_word3);
	radeon_ring_write(ring, 0);
	radeon_ring_write(ring, 0);
	radeon_ring_write(ring, 0);
	radeon_ring_write(ring, S__SQ_CONSTANT_TYPE(SQ_TEX_VTX_VALID_BUFFER));

	if ((rdev->family == CHIP_CEDAR) ||
	    (rdev->family == CHIP_PALM) ||
	    (rdev->family == CHIP_SUMO) ||
	    (rdev->family == CHIP_SUMO2) ||
	    (rdev->family == CHIP_CAICOS))
		cp_set_surface_sync(rdev,
				    PACKET3_TC_ACTION_ENA, 48, gpu_addr);
	else
		cp_set_surface_sync(rdev,
				    PACKET3_VC_ACTION_ENA, 48, gpu_addr);

}