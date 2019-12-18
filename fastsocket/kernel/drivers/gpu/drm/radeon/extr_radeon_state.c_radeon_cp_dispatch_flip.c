#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int y; int x; } ;
struct drm_sarea {TYPE_3__ frame; } ;
struct drm_radeon_master_private {TYPE_4__* sarea_priv; TYPE_1__* sarea; } ;
struct drm_master {struct drm_radeon_master_private* driver_priv; } ;
struct drm_device {TYPE_5__* dev_private; } ;
struct TYPE_8__ {int /*<<< orphan*/  boxes; } ;
struct TYPE_11__ {int front_offset; int back_offset; int front_pitch; int color_fmt; TYPE_2__ stats; scalar_t__ do_boxes; } ;
typedef  TYPE_5__ drm_radeon_private_t ;
struct TYPE_10__ {int pfCurrentPage; int crtc2_base; int /*<<< orphan*/  last_frame; } ;
struct TYPE_7__ {scalar_t__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 int /*<<< orphan*/  OUT_RING_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RADEON_BOX_FLIP ; 
 int /*<<< orphan*/  RADEON_CRTC2_OFFSET ; 
 int /*<<< orphan*/  RADEON_CRTC_OFFSET ; 
 int /*<<< orphan*/  RADEON_FRAME_AGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADEON_WAIT_UNTIL_3D_IDLE () ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int /*<<< orphan*/  radeon_cp_performance_boxes (TYPE_5__*,struct drm_radeon_master_private*) ; 

void radeon_cp_dispatch_flip(struct drm_device *dev, struct drm_master *master)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	struct drm_radeon_master_private *master_priv = master->driver_priv;
	struct drm_sarea *sarea = (struct drm_sarea *)master_priv->sarea->handle;
	int offset = (master_priv->sarea_priv->pfCurrentPage == 1)
	    ? dev_priv->front_offset : dev_priv->back_offset;
	RING_LOCALS;
	DRM_DEBUG("pfCurrentPage=%d\n",
		  master_priv->sarea_priv->pfCurrentPage);

	/* Do some trivial performance monitoring...
	 */
	if (dev_priv->do_boxes) {
		dev_priv->stats.boxes |= RADEON_BOX_FLIP;
		radeon_cp_performance_boxes(dev_priv, master_priv);
	}

	/* Update the frame offsets for both CRTCs
	 */
	BEGIN_RING(6);

	RADEON_WAIT_UNTIL_3D_IDLE();
	OUT_RING_REG(RADEON_CRTC_OFFSET,
		     ((sarea->frame.y * dev_priv->front_pitch +
		       sarea->frame.x * (dev_priv->color_fmt - 2)) & ~7)
		     + offset);
	OUT_RING_REG(RADEON_CRTC2_OFFSET, master_priv->sarea_priv->crtc2_base
		     + offset);

	ADVANCE_RING();

	/* Increment the frame counter.  The client-side 3D driver must
	 * throttle the framerate by waiting for this value before
	 * performing the swapbuffer ioctl.
	 */
	master_priv->sarea_priv->last_frame++;
	master_priv->sarea_priv->pfCurrentPage =
		1 - master_priv->sarea_priv->pfCurrentPage;

	BEGIN_RING(2);

	RADEON_FRAME_AGE(master_priv->sarea_priv->last_frame);

	ADVANCE_RING();
}