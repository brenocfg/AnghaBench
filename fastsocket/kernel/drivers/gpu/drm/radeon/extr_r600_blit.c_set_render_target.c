#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int CHIP_R600 ; 
 int CHIP_RV770 ; 
 int CP_PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int R600_CB_COLOR0_BASE ; 
 int R600_CB_COLOR0_FRAG ; 
 int R600_CB_COLOR0_INFO ; 
 int R600_CB_COLOR0_MASK ; 
 int R600_CB_COLOR0_SIZE ; 
 int R600_CB_COLOR0_TILE ; 
 int R600_CB_COLOR0_VIEW ; 
 int /*<<< orphan*/  R600_IT_SET_CONTEXT_REG ; 
 int /*<<< orphan*/  R600_IT_SURFACE_BASE_UPDATE ; 
 int R600_SET_CONTEXT_REG_OFFSET ; 
 int RADEON_FAMILY_MASK ; 
 int /*<<< orphan*/  RING_LOCALS ; 

__attribute__((used)) static void
set_render_target(drm_radeon_private_t *dev_priv, int format, int w, int h, u64 gpu_addr)
{
	u32 cb_color_info;
	int pitch, slice;
	RING_LOCALS;
	DRM_DEBUG("\n");

	h = ALIGN(h, 8);
	if (h < 8)
		h = 8;

	cb_color_info = ((format << 2) | (1 << 27));
	pitch = (w / 8) - 1;
	slice = ((w * h) / 64) - 1;

	if (((dev_priv->flags & RADEON_FAMILY_MASK) > CHIP_R600) &&
	    ((dev_priv->flags & RADEON_FAMILY_MASK) < CHIP_RV770)) {
		BEGIN_RING(21 + 2);
		OUT_RING(CP_PACKET3(R600_IT_SET_CONTEXT_REG, 1));
		OUT_RING((R600_CB_COLOR0_BASE - R600_SET_CONTEXT_REG_OFFSET) >> 2);
		OUT_RING(gpu_addr >> 8);
		OUT_RING(CP_PACKET3(R600_IT_SURFACE_BASE_UPDATE, 0));
		OUT_RING(2 << 0);
	} else {
		BEGIN_RING(21);
		OUT_RING(CP_PACKET3(R600_IT_SET_CONTEXT_REG, 1));
		OUT_RING((R600_CB_COLOR0_BASE - R600_SET_CONTEXT_REG_OFFSET) >> 2);
		OUT_RING(gpu_addr >> 8);
	}

	OUT_RING(CP_PACKET3(R600_IT_SET_CONTEXT_REG, 1));
	OUT_RING((R600_CB_COLOR0_SIZE - R600_SET_CONTEXT_REG_OFFSET) >> 2);
	OUT_RING((pitch << 0) | (slice << 10));

	OUT_RING(CP_PACKET3(R600_IT_SET_CONTEXT_REG, 1));
	OUT_RING((R600_CB_COLOR0_VIEW - R600_SET_CONTEXT_REG_OFFSET) >> 2);
	OUT_RING(0);

	OUT_RING(CP_PACKET3(R600_IT_SET_CONTEXT_REG, 1));
	OUT_RING((R600_CB_COLOR0_INFO - R600_SET_CONTEXT_REG_OFFSET) >> 2);
	OUT_RING(cb_color_info);

	OUT_RING(CP_PACKET3(R600_IT_SET_CONTEXT_REG, 1));
	OUT_RING((R600_CB_COLOR0_TILE - R600_SET_CONTEXT_REG_OFFSET) >> 2);
	OUT_RING(0);

	OUT_RING(CP_PACKET3(R600_IT_SET_CONTEXT_REG, 1));
	OUT_RING((R600_CB_COLOR0_FRAG - R600_SET_CONTEXT_REG_OFFSET) >> 2);
	OUT_RING(0);

	OUT_RING(CP_PACKET3(R600_IT_SET_CONTEXT_REG, 1));
	OUT_RING((R600_CB_COLOR0_MASK - R600_SET_CONTEXT_REG_OFFSET) >> 2);
	OUT_RING(0);

	ADVANCE_RING();
}