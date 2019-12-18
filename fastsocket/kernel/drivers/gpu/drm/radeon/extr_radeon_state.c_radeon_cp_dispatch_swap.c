#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_radeon_master_private {TYPE_1__* sarea_priv; } ;
struct drm_master {struct drm_radeon_master_private* driver_priv; } ;
struct drm_device {TYPE_2__* dev_private; } ;
struct drm_clip_rect {int x1; int y1; int x2; int y2; } ;
struct TYPE_4__ {int nbox; scalar_t__ pfCurrentPage; int /*<<< orphan*/  last_frame; struct drm_clip_rect* boxes; } ;
typedef  TYPE_1__ drm_radeon_sarea_t ;
struct TYPE_5__ {int color_fmt; int back_pitch_offset; int front_pitch_offset; scalar_t__ do_boxes; } ;
typedef  TYPE_2__ drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int CP_PACKET0 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int /*<<< orphan*/  RADEON_DP_GUI_MASTER_CNTL ; 
 int RADEON_DP_SRC_SOURCE_MEMORY ; 
 int /*<<< orphan*/  RADEON_FRAME_AGE (int /*<<< orphan*/ ) ; 
 int RADEON_GMC_BRUSH_NONE ; 
 int RADEON_GMC_CLR_CMP_CNTL_DIS ; 
 int RADEON_GMC_DST_PITCH_OFFSET_CNTL ; 
 int RADEON_GMC_SRC_DATATYPE_COLOR ; 
 int RADEON_GMC_SRC_PITCH_OFFSET_CNTL ; 
 int RADEON_GMC_WR_MSK_DIS ; 
 int RADEON_ROP3_S ; 
 int /*<<< orphan*/  RADEON_SRC_PITCH_OFFSET ; 
 int /*<<< orphan*/  RADEON_SRC_X_Y ; 
 int /*<<< orphan*/  RADEON_WAIT_UNTIL_2D_IDLE () ; 
 int /*<<< orphan*/  RADEON_WAIT_UNTIL_3D_IDLE () ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int /*<<< orphan*/  radeon_cp_performance_boxes (TYPE_2__*,struct drm_radeon_master_private*) ; 

__attribute__((used)) static void radeon_cp_dispatch_swap(struct drm_device *dev, struct drm_master *master)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	struct drm_radeon_master_private *master_priv = master->driver_priv;
	drm_radeon_sarea_t *sarea_priv = master_priv->sarea_priv;
	int nbox = sarea_priv->nbox;
	struct drm_clip_rect *pbox = sarea_priv->boxes;
	int i;
	RING_LOCALS;
	DRM_DEBUG("\n");

	/* Do some trivial performance monitoring...
	 */
	if (dev_priv->do_boxes)
		radeon_cp_performance_boxes(dev_priv, master_priv);

	/* Wait for the 3D stream to idle before dispatching the bitblt.
	 * This will prevent data corruption between the two streams.
	 */
	BEGIN_RING(2);

	RADEON_WAIT_UNTIL_3D_IDLE();

	ADVANCE_RING();

	for (i = 0; i < nbox; i++) {
		int x = pbox[i].x1;
		int y = pbox[i].y1;
		int w = pbox[i].x2 - x;
		int h = pbox[i].y2 - y;

		DRM_DEBUG("%d,%d-%d,%d\n", x, y, w, h);

		BEGIN_RING(9);

		OUT_RING(CP_PACKET0(RADEON_DP_GUI_MASTER_CNTL, 0));
		OUT_RING(RADEON_GMC_SRC_PITCH_OFFSET_CNTL |
			 RADEON_GMC_DST_PITCH_OFFSET_CNTL |
			 RADEON_GMC_BRUSH_NONE |
			 (dev_priv->color_fmt << 8) |
			 RADEON_GMC_SRC_DATATYPE_COLOR |
			 RADEON_ROP3_S |
			 RADEON_DP_SRC_SOURCE_MEMORY |
			 RADEON_GMC_CLR_CMP_CNTL_DIS | RADEON_GMC_WR_MSK_DIS);

		/* Make this work even if front & back are flipped:
		 */
		OUT_RING(CP_PACKET0(RADEON_SRC_PITCH_OFFSET, 1));
		if (sarea_priv->pfCurrentPage == 0) {
			OUT_RING(dev_priv->back_pitch_offset);
			OUT_RING(dev_priv->front_pitch_offset);
		} else {
			OUT_RING(dev_priv->front_pitch_offset);
			OUT_RING(dev_priv->back_pitch_offset);
		}

		OUT_RING(CP_PACKET0(RADEON_SRC_X_Y, 2));
		OUT_RING((x << 16) | y);
		OUT_RING((x << 16) | y);
		OUT_RING((w << 16) | h);

		ADVANCE_RING();
	}

	/* Increment the frame counter.  The client-side 3D driver must
	 * throttle the framerate by waiting for this value before
	 * performing the swapbuffer ioctl.
	 */
	sarea_priv->last_frame++;

	BEGIN_RING(4);

	RADEON_FRAME_AGE(sarea_priv->last_frame);
	RADEON_WAIT_UNTIL_2D_IDLE();

	ADVANCE_RING();
}