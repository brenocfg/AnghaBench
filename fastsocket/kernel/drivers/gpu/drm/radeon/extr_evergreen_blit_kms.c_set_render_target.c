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
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  ARRAY_1D_TILED_THIN1 ; 
 int CB_ARRAY_MODE (int /*<<< orphan*/ ) ; 
 int CB_COLOR0_BASE ; 
 int CB_FORMAT (int) ; 
 int /*<<< orphan*/  CB_SF_EXPORT_NORM ; 
 int CB_SOURCE_FORMAT (int /*<<< orphan*/ ) ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_SET_CONTEXT_REG ; 
 int PACKET3_SET_CONTEXT_REG_START ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 

__attribute__((used)) static void
set_render_target(struct radeon_device *rdev, int format,
		  int w, int h, u64 gpu_addr)
{
	struct radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	u32 cb_color_info;
	int pitch, slice;

	h = ALIGN(h, 8);
	if (h < 8)
		h = 8;

	cb_color_info = CB_FORMAT(format) |
		CB_SOURCE_FORMAT(CB_SF_EXPORT_NORM) |
		CB_ARRAY_MODE(ARRAY_1D_TILED_THIN1);
	pitch = (w / 8) - 1;
	slice = ((w * h) / 64) - 1;

	radeon_ring_write(ring, PACKET3(PACKET3_SET_CONTEXT_REG, 15));
	radeon_ring_write(ring, (CB_COLOR0_BASE - PACKET3_SET_CONTEXT_REG_START) >> 2);
	radeon_ring_write(ring, gpu_addr >> 8);
	radeon_ring_write(ring, pitch);
	radeon_ring_write(ring, slice);
	radeon_ring_write(ring, 0);
	radeon_ring_write(ring, cb_color_info);
	radeon_ring_write(ring, 0);
	radeon_ring_write(ring, (w - 1) | ((h - 1) << 16));
	radeon_ring_write(ring, 0);
	radeon_ring_write(ring, 0);
	radeon_ring_write(ring, 0);
	radeon_ring_write(ring, 0);
	radeon_ring_write(ring, 0);
	radeon_ring_write(ring, 0);
	radeon_ring_write(ring, 0);
	radeon_ring_write(ring, 0);
}