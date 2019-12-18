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
typedef  int /*<<< orphan*/  drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int /*<<< orphan*/  COMMIT_RING () ; 
 int CP_PACKET3 (int /*<<< orphan*/ ,int) ; 
 int DI_INDEX_SIZE_16_BIT ; 
 int DI_PT_RECTLIST ; 
 int DI_SRC_SEL_AUTO_INDEX ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int /*<<< orphan*/  R600_IT_DRAW_INDEX_AUTO ; 
 int /*<<< orphan*/  R600_IT_INDEX_TYPE ; 
 int /*<<< orphan*/  R600_IT_NUM_INSTANCES ; 
 int /*<<< orphan*/  R600_IT_SET_CONFIG_REG ; 
 int R600_SET_CONFIG_REG_OFFSET ; 
 int R600_VGT_PRIMITIVE_TYPE ; 
 int /*<<< orphan*/  RING_LOCALS ; 

__attribute__((used)) static void
draw_auto(drm_radeon_private_t *dev_priv)
{
	RING_LOCALS;
	DRM_DEBUG("\n");

	BEGIN_RING(10);
	OUT_RING(CP_PACKET3(R600_IT_SET_CONFIG_REG, 1));
	OUT_RING((R600_VGT_PRIMITIVE_TYPE - R600_SET_CONFIG_REG_OFFSET) >> 2);
	OUT_RING(DI_PT_RECTLIST);

	OUT_RING(CP_PACKET3(R600_IT_INDEX_TYPE, 0));
#ifdef __BIG_ENDIAN
	OUT_RING((2 << 2) | DI_INDEX_SIZE_16_BIT);
#else
	OUT_RING(DI_INDEX_SIZE_16_BIT);
#endif

	OUT_RING(CP_PACKET3(R600_IT_NUM_INSTANCES, 0));
	OUT_RING(1);

	OUT_RING(CP_PACKET3(R600_IT_DRAW_INDEX_AUTO, 1));
	OUT_RING(3);
	OUT_RING(DI_SRC_SEL_AUTO_INDEX);

	ADVANCE_RING();
	COMMIT_RING();
}