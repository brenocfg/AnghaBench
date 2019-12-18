#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct drm_i915_master_private {TYPE_4__* sarea_priv; TYPE_8__* sarea; } ;
struct drm_device {TYPE_2__* primary; TYPE_5__* dev_private; } ;
struct TYPE_14__ {scalar_t__ pf_current_page; } ;
typedef  TYPE_4__ drm_i915_sarea_t ;
struct TYPE_13__ {int allow_batchbuffer; scalar_t__ current_page; int /*<<< orphan*/  front_offset; int /*<<< orphan*/  back_offset; int /*<<< orphan*/  cpp; } ;
struct TYPE_15__ {TYPE_3__ dri1; } ;
typedef  TYPE_5__ drm_i915_private_t ;
struct TYPE_16__ {int sarea_priv_offset; scalar_t__ ring_size; int /*<<< orphan*/  front_offset; int /*<<< orphan*/  back_offset; int /*<<< orphan*/  cpp; int /*<<< orphan*/  ring_start; } ;
typedef  TYPE_6__ drm_i915_init_t ;
struct TYPE_18__ {int /*<<< orphan*/ * obj; } ;
struct TYPE_17__ {scalar_t__ handle; } ;
struct TYPE_12__ {TYPE_1__* master; } ;
struct TYPE_11__ {struct drm_i915_master_private* driver_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 TYPE_9__* LP_RING (TYPE_5__*) ; 
 TYPE_8__* drm_getsarea (struct drm_device*) ; 
 int /*<<< orphan*/  i915_dma_cleanup (struct drm_device*) ; 
 int intel_render_ring_init_dri (struct drm_device*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int i915_initialize(struct drm_device * dev, drm_i915_init_t * init)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct drm_i915_master_private *master_priv = dev->primary->master->driver_priv;
	int ret;

	master_priv->sarea = drm_getsarea(dev);
	if (master_priv->sarea) {
		master_priv->sarea_priv = (drm_i915_sarea_t *)
			((u8 *)master_priv->sarea->handle + init->sarea_priv_offset);
	} else {
		DRM_DEBUG_DRIVER("sarea not found assuming DRI2 userspace\n");
	}

	if (init->ring_size != 0) {
		if (LP_RING(dev_priv)->obj != NULL) {
			i915_dma_cleanup(dev);
			DRM_ERROR("Client tried to initialize ringbuffer in "
				  "GEM mode\n");
			return -EINVAL;
		}

		ret = intel_render_ring_init_dri(dev,
						 init->ring_start,
						 init->ring_size);
		if (ret) {
			i915_dma_cleanup(dev);
			return ret;
		}
	}

	dev_priv->dri1.cpp = init->cpp;
	dev_priv->dri1.back_offset = init->back_offset;
	dev_priv->dri1.front_offset = init->front_offset;
	dev_priv->dri1.current_page = 0;
	if (master_priv->sarea_priv)
		master_priv->sarea_priv->pf_current_page = 0;

	/* Allow hardware batchbuffers unless told otherwise.
	 */
	dev_priv->dri1.allow_batchbuffer = 1;

	return 0;
}