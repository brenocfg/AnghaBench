#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_radeon_master_private {int dummy; } ;
struct TYPE_6__ {int last_frame_reads; scalar_t__ last_clear_reads; scalar_t__ clears; int boxes; int requested_bufs; scalar_t__ freelist_loops; } ;
struct TYPE_5__ {TYPE_4__ stats; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int RADEON_BOX_DMA_IDLE ; 
 int RADEON_BOX_FLIP ; 
 int RADEON_BOX_TEXTURE_LOAD ; 
 int RADEON_BOX_WAIT_IDLE ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_clear_box (TYPE_1__*,struct drm_radeon_master_private*,int,int,int,int,int,int,int) ; 

__attribute__((used)) static void radeon_cp_performance_boxes(drm_radeon_private_t *dev_priv, struct drm_radeon_master_private *master_priv)
{
	/* Collapse various things into a wait flag -- trying to
	 * guess if userspase slept -- better just to have them tell us.
	 */
	if (dev_priv->stats.last_frame_reads > 1 ||
	    dev_priv->stats.last_clear_reads > dev_priv->stats.clears) {
		dev_priv->stats.boxes |= RADEON_BOX_WAIT_IDLE;
	}

	if (dev_priv->stats.freelist_loops) {
		dev_priv->stats.boxes |= RADEON_BOX_WAIT_IDLE;
	}

	/* Purple box for page flipping
	 */
	if (dev_priv->stats.boxes & RADEON_BOX_FLIP)
		radeon_clear_box(dev_priv, master_priv, 4, 4, 8, 8, 255, 0, 255);

	/* Red box if we have to wait for idle at any point
	 */
	if (dev_priv->stats.boxes & RADEON_BOX_WAIT_IDLE)
		radeon_clear_box(dev_priv, master_priv, 16, 4, 8, 8, 255, 0, 0);

	/* Blue box: lost context?
	 */

	/* Yellow box for texture swaps
	 */
	if (dev_priv->stats.boxes & RADEON_BOX_TEXTURE_LOAD)
		radeon_clear_box(dev_priv, master_priv, 40, 4, 8, 8, 255, 255, 0);

	/* Green box if hardware never idles (as far as we can tell)
	 */
	if (!(dev_priv->stats.boxes & RADEON_BOX_DMA_IDLE))
		radeon_clear_box(dev_priv, master_priv, 64, 4, 8, 8, 0, 255, 0);

	/* Draw bars indicating number of buffers allocated
	 * (not a great measure, easily confused)
	 */
	if (dev_priv->stats.requested_bufs) {
		if (dev_priv->stats.requested_bufs > 100)
			dev_priv->stats.requested_bufs = 100;

		radeon_clear_box(dev_priv, master_priv, 4, 16,
				 dev_priv->stats.requested_bufs, 4,
				 196, 128, 128);
	}

	memset(&dev_priv->stats, 0, sizeof(dev_priv->stats));

}