#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u64 ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int CHIP_RS780 ; 
 int CHIP_RS880 ; 
 int CHIP_RV610 ; 
 int CHIP_RV620 ; 
 int CHIP_RV710 ; 
 int CP_PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int /*<<< orphan*/  R600_IT_SET_RESOURCE ; 
 int R600_SQ_TEX_VTX_VALID_BUFFER ; 
 int /*<<< orphan*/  R600_TC_ACTION_ENA ; 
 int /*<<< orphan*/  R600_VC_ACTION_ENA ; 
 int RADEON_FAMILY_MASK ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int /*<<< orphan*/  cp_set_surface_sync (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
set_vtx_resource(drm_radeon_private_t *dev_priv, u64 gpu_addr)
{
	uint32_t sq_vtx_constant_word2;
	RING_LOCALS;
	DRM_DEBUG("\n");

	sq_vtx_constant_word2 = (((gpu_addr >> 32) & 0xff) | (16 << 8));
#ifdef __BIG_ENDIAN
	sq_vtx_constant_word2 |= (2 << 30);
#endif

	BEGIN_RING(9);
	OUT_RING(CP_PACKET3(R600_IT_SET_RESOURCE, 7));
	OUT_RING(0x460);
	OUT_RING(gpu_addr & 0xffffffff);
	OUT_RING(48 - 1);
	OUT_RING(sq_vtx_constant_word2);
	OUT_RING(1 << 0);
	OUT_RING(0);
	OUT_RING(0);
	OUT_RING(R600_SQ_TEX_VTX_VALID_BUFFER << 30);
	ADVANCE_RING();

	if (((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RV610) ||
	    ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RV620) ||
	    ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS780) ||
	    ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS880) ||
	    ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RV710))
		cp_set_surface_sync(dev_priv,
				    R600_TC_ACTION_ENA, 48, gpu_addr);
	else
		cp_set_surface_sync(dev_priv,
				    R600_VC_ACTION_ENA, 48, gpu_addr);
}