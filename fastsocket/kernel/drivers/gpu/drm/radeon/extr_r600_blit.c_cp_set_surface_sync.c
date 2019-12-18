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
typedef  int /*<<< orphan*/  drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int CP_PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int /*<<< orphan*/  R600_IT_SURFACE_SYNC ; 
 int /*<<< orphan*/  RING_LOCALS ; 

__attribute__((used)) static void
cp_set_surface_sync(drm_radeon_private_t *dev_priv,
		    u32 sync_type, u32 size, u64 mc_addr)
{
	u32 cp_coher_size;
	RING_LOCALS;
	DRM_DEBUG("\n");

	if (size == 0xffffffff)
		cp_coher_size = 0xffffffff;
	else
		cp_coher_size = ((size + 255) >> 8);

	BEGIN_RING(5);
	OUT_RING(CP_PACKET3(R600_IT_SURFACE_SYNC, 3));
	OUT_RING(sync_type);
	OUT_RING(cp_coher_size);
	OUT_RING((mc_addr >> 8));
	OUT_RING(10); /* poll interval */
	ADVANCE_RING();
}