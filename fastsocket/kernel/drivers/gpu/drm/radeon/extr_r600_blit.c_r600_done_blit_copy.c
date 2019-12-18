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
struct drm_device {int /*<<< orphan*/ * dev_private; } ;
typedef  int /*<<< orphan*/  drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int /*<<< orphan*/  COMMIT_RING () ; 
 int CP_PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int R600_CACHE_FLUSH_AND_INV_EVENT ; 
 int /*<<< orphan*/  R600_IT_EVENT_WRITE ; 
 int /*<<< orphan*/  R600_IT_SET_CONFIG_REG ; 
 int R600_SET_CONFIG_REG_OFFSET ; 
 int R600_WAIT_UNTIL ; 
 int RADEON_WAIT_3D_IDLE ; 
 int RADEON_WAIT_3D_IDLECLEAN ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int /*<<< orphan*/  r600_nomm_put_vb (struct drm_device*) ; 

void
r600_done_blit_copy(struct drm_device *dev)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	RING_LOCALS;
	DRM_DEBUG("\n");

	BEGIN_RING(5);
	OUT_RING(CP_PACKET3(R600_IT_EVENT_WRITE, 0));
	OUT_RING(R600_CACHE_FLUSH_AND_INV_EVENT);
	/* wait for 3D idle clean */
	OUT_RING(CP_PACKET3(R600_IT_SET_CONFIG_REG, 1));
	OUT_RING((R600_WAIT_UNTIL - R600_SET_CONFIG_REG_OFFSET) >> 2);
	OUT_RING(RADEON_WAIT_3D_IDLE | RADEON_WAIT_3D_IDLECLEAN);

	ADVANCE_RING();
	COMMIT_RING();

	r600_nomm_put_vb(dev);
}