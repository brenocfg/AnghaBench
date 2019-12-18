#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_radeon_master_private {TYPE_1__* sarea_priv; } ;
struct drm_master {struct drm_radeon_master_private* driver_priv; } ;
struct drm_device {TYPE_2__* dev_private; } ;
struct TYPE_4__ {int page_flipping; } ;
typedef  TYPE_2__ drm_radeon_private_t ;
struct TYPE_3__ {int pfCurrentPage; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int CP_PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int /*<<< orphan*/  RADEON_CRTC2_OFFSET_CNTL ; 
 int /*<<< orphan*/  RADEON_CRTC_OFFSET_CNTL ; 
 int RADEON_CRTC_OFFSET_FLIP_CNTL ; 
 int RADEON_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADEON_WAIT_UNTIL_3D_IDLE () ; 
 int /*<<< orphan*/  RING_LOCALS ; 

__attribute__((used)) static int radeon_do_init_pageflip(struct drm_device *dev, struct drm_master *master)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	struct drm_radeon_master_private *master_priv = master->driver_priv;
	RING_LOCALS;

	DRM_DEBUG("\n");

	BEGIN_RING(6);
	RADEON_WAIT_UNTIL_3D_IDLE();
	OUT_RING(CP_PACKET0(RADEON_CRTC_OFFSET_CNTL, 0));
	OUT_RING(RADEON_READ(RADEON_CRTC_OFFSET_CNTL) |
		 RADEON_CRTC_OFFSET_FLIP_CNTL);
	OUT_RING(CP_PACKET0(RADEON_CRTC2_OFFSET_CNTL, 0));
	OUT_RING(RADEON_READ(RADEON_CRTC2_OFFSET_CNTL) |
		 RADEON_CRTC_OFFSET_FLIP_CNTL);
	ADVANCE_RING();

	dev_priv->page_flipping = 1;

	if (master_priv->sarea_priv->pfCurrentPage != 1)
		master_priv->sarea_priv->pfCurrentPage = 0;

	return 0;
}