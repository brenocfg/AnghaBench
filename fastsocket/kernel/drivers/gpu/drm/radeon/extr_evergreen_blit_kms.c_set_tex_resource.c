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
struct radeon_device {struct radeon_ring* ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_1D_TILED_THIN1 ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_SET_RESOURCE ; 
 int /*<<< orphan*/  PACKET3_TC_ACTION_ENA ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int /*<<< orphan*/  SQ_SEL_W ; 
 int /*<<< orphan*/  SQ_SEL_X ; 
 int /*<<< orphan*/  SQ_SEL_Y ; 
 int /*<<< orphan*/  SQ_SEL_Z ; 
 int /*<<< orphan*/  SQ_TEX_DIM_2D ; 
 int /*<<< orphan*/  SQ_TEX_VTX_VALID_TEXTURE ; 
 int S__SQ_CONSTANT_TYPE (int /*<<< orphan*/ ) ; 
 int TEX_ARRAY_MODE (int /*<<< orphan*/ ) ; 
 int TEX_DIM (int /*<<< orphan*/ ) ; 
 int TEX_DST_SEL_W (int /*<<< orphan*/ ) ; 
 int TEX_DST_SEL_X (int /*<<< orphan*/ ) ; 
 int TEX_DST_SEL_Y (int /*<<< orphan*/ ) ; 
 int TEX_DST_SEL_Z (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_set_surface_sync (struct radeon_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 

__attribute__((used)) static void
set_tex_resource(struct radeon_device *rdev,
		 int format, int w, int h, int pitch,
		 u64 gpu_addr, u32 size)
{
	struct radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	u32 sq_tex_resource_word0, sq_tex_resource_word1;
	u32 sq_tex_resource_word4, sq_tex_resource_word7;

	if (h < 1)
		h = 1;

	sq_tex_resource_word0 = TEX_DIM(SQ_TEX_DIM_2D);
	sq_tex_resource_word0 |= ((((pitch >> 3) - 1) << 6) |
				  ((w - 1) << 18));
	sq_tex_resource_word1 = ((h - 1) << 0) |
				TEX_ARRAY_MODE(ARRAY_1D_TILED_THIN1);
	/* xyzw swizzles */
	sq_tex_resource_word4 = TEX_DST_SEL_X(SQ_SEL_X) |
				TEX_DST_SEL_Y(SQ_SEL_Y) |
				TEX_DST_SEL_Z(SQ_SEL_Z) |
				TEX_DST_SEL_W(SQ_SEL_W);

	sq_tex_resource_word7 = format |
		S__SQ_CONSTANT_TYPE(SQ_TEX_VTX_VALID_TEXTURE);

	cp_set_surface_sync(rdev,
			    PACKET3_TC_ACTION_ENA, size, gpu_addr);

	radeon_ring_write(ring, PACKET3(PACKET3_SET_RESOURCE, 8));
	radeon_ring_write(ring, 0);
	radeon_ring_write(ring, sq_tex_resource_word0);
	radeon_ring_write(ring, sq_tex_resource_word1);
	radeon_ring_write(ring, gpu_addr >> 8);
	radeon_ring_write(ring, gpu_addr >> 8);
	radeon_ring_write(ring, sq_tex_resource_word4);
	radeon_ring_write(ring, 0);
	radeon_ring_write(ring, 0);
	radeon_ring_write(ring, sq_tex_resource_word7);
}